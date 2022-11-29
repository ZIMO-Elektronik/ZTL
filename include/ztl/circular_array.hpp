// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Circular array
///
/// \file   ztl/circular_array.hpp
/// \author Vincent Hamp
/// \date   12/11/2016

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <type_traits>
#include "limits.hpp"

namespace ztl {

/// circular_array implements a ring array which holds I elements of type T.
/// Push and pop can be used to add and remove elements from the front and back
/// the same way. An equal read and write index signals, that the array is
/// empty. If the array is full, the indices differ by one. This leads to the
/// limitation that the array needs I + 1 elements of storage. There is a slight
/// performance benefit of using sizes where I + 1 equals a power of 2 because
/// of the use of modulo math.
///
/// \tparam T Type of element
/// \tparam I Size of container
template<typename T, size_t I>
struct circular_array {
  using index_type = smallest_unsigned_t<I + 1uz>;

  template<bool Const>
  struct iterator_ {
    using value_type = std::conditional_t<Const, T const, T>;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using reference = std::conditional_t<Const, T const&, T&>;
    using pointer = std::conditional_t<Const, T const*, T*>;
    using iterator_category = std::random_access_iterator_tag;
    using circular_array_pointer =
      std::conditional_t<Const, circular_array const*, circular_array*>;

    friend iterator_<true>;

    constexpr iterator_() = default;

    constexpr iterator_(circular_array_pointer ptr, index_type i)
      : ptr_{ptr}, i_{i} {}

    constexpr iterator_(iterator_ const&) = default;

    constexpr iterator_(iterator_<false> const& rhs) requires Const
      : ptr_{rhs.ptr_},
        i_{rhs.i_} {}

    constexpr iterator_& operator=(iterator_ const&) = default;

    constexpr iterator_& operator=(iterator_ const& rhs) requires Const {
      ptr_ = rhs.ptr_;
      i_ = rhs.i_;
      return *this;
    }

    constexpr reference operator[](size_type i) const {
      return ptr_->elems_[(i_ + i) % (I + 1uz)];
    }

    constexpr iterator_& operator++() {
      i_ = static_cast<index_type>((i_ + 1zu) % (I + 1zu));
      return *this;
    }

    constexpr iterator_ operator++(int) {
      iterator_ retval{*this};
      i_ = static_cast<index_type>((i_ + 1uz) % (I + 1uz));
      return retval;
    }

    constexpr iterator_& operator--() {
      if constexpr (std::has_single_bit(I + 1uz))
        i_ = static_cast<index_type>((i_ - 1uz) % (I + 1uz));
      else i_ = static_cast<index_type>(i_ ? i_ - 1uz : I);
      return *this;
    }

    constexpr iterator_ operator--(int) {
      iterator_ retval{*this};
      if constexpr (std::has_single_bit(I + 1uz))
        i_ = static_cast<index_type>((i_ - 1uz) % (I + 1uz));
      else i_ = static_cast<index_type>(i_ ? i_ - 1uz : I);
      return retval;
    }

    constexpr iterator_ operator+(difference_type n) const {
      return iterator_{ptr_, static_cast<index_type>((i_ + n) % (I + 1uz))};
    }

    constexpr iterator_& operator+=(difference_type n) {
      i_ = static_cast<index_type>((i_ + n) % (I + 1uz));
      return *this;
    }

    constexpr difference_type operator-(iterator_ const& rhs) const {
      if (auto const diff{static_cast<difference_type>(i_ - rhs.i_)};
          ptr_->rd_ <= ptr_->wr_)
        return diff;
      else {
        if (diff < 0) return diff + static_cast<difference_type>(I + 1uz);
        else if (diff > 0) return diff - static_cast<difference_type>(I + 1uz);
        else return 0;
      }
    }

    constexpr iterator_ operator-(difference_type n) const {
      if constexpr (std::has_single_bit(I + 1uz))
        return iterator_{ptr_, static_cast<index_type>((i_ - n) % (I + 1uz))};
      else
        return iterator_{
          ptr_, static_cast<index_type>(i_ < n ? I + 1uz + i_ - n : i_ - n)};
    }

    constexpr iterator_& operator-=(difference_type n) {
      if constexpr (std::has_single_bit(I + 1uz))
        i_ = static_cast<index_type>((i_ - n) % (I + 1uz));
      else i_ = static_cast<index_type>(i_ < n ? I + 1uz + i_ - n : i_ - n);
      return *this;
    }

    constexpr reference operator*() const { return ptr_->elems_[i_]; }

    constexpr pointer operator->() const { return &ptr_->elems_[i_]; }

    constexpr bool operator==(iterator_ const& rhs) const {
      return i_ == rhs.i_;
    }

    constexpr bool operator!=(iterator_ const& rhs) const {
      return !(*this == rhs);
    }

    constexpr bool operator<(iterator_ const& rhs) const {
      return ptr_->rd_ <= ptr_->wr_ ? i_ < rhs.i_ : i_ > rhs.i_;
    }

    constexpr bool operator>(iterator_ const& rhs) const { return rhs < *this; }

    constexpr bool operator<=(iterator_ const& rhs) const {
      return !(*this > rhs);
    }

    constexpr bool operator>=(iterator_ const& rhs) const {
      return !(*this < rhs);
    }

    friend constexpr iterator_ operator+(difference_type lhs,
                                         iterator_ const& rhs) {
      return rhs + lhs;
    }

    friend constexpr iterator_ operator-(difference_type lhs,
                                         iterator_ const& rhs) {
      return rhs + lhs;
    }

  private:
    circular_array_pointer ptr_{nullptr};
    index_type i_{};
  };

  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = T const&;
  using iterator = iterator_<false>;
  using const_iterator = iterator_<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  constexpr circular_array() = default;

  template<std::convertible_to<T>... Us>
  constexpr circular_array(Us&&... us) requires(sizeof...(Us) < I + 1uz)
    : elems_{static_cast<T>(us)...}, wr_{sizeof...(Us)} {}

  constexpr reference operator[](size_type i) {
    return elems_[(rd_ + i) % (I + 1uz)];
  }

  constexpr const_reference operator[](size_type i) const {
    return elems_[(rd_ + i) % (I + 1uz)];
  }

  /// Checks whether the container is empty
  ///
  /// \return true  Buffer is empty
  /// \return false Buffer is not empty
  constexpr bool empty() const { return rd_ == wr_; }

  /// Checks whether the container is full
  ///
  /// \return true  Buffer is full
  /// \return false Buffer is not full
  constexpr bool full() const { return rd_ == (wr_ + 1uz) % (I + 1uz); }

  /// Returns the number of elements
  ///
  /// \return Number of elements
  constexpr size_type size() const {
    if (rd_ <= wr_) return static_cast<size_type>(wr_ - rd_);
    else return static_cast<size_type>(I + 1uz - rd_ + wr_);
  }

  /// Returns the number of elements
  ///
  /// \return Number of elements
  constexpr auto ssize() const {
    using R = std::common_type_t<std::ptrdiff_t, std::make_signed_t<size_type>>;
    return static_cast<R>(size());
  }

  /// Returns the maximum possible number of elements
  ///
  /// \return Maximum possible number of elements
  constexpr size_type max_size() const { return I; }

  /// Returns the maximum possible number of elements
  ///
  /// \return Maximum possible number of elements
  constexpr size_type capacity() const { return I; }

  /// Removes all elements from the container
  constexpr void clear() { rd_ = wr_ = 0u; }

  /// Access the first element
  ///
  /// \return reference Reference to the first element
  constexpr reference front() { return elems_[rd_]; }

  /// Access the first element
  ///
  /// \return const_reference Constant reference to the first element
  constexpr const_reference front() const { return elems_[rd_]; }

  /// Access the last element
  ///
  /// \return reference Reference to the last element
  constexpr reference back() {
    if (empty()) return elems_[wr_];
    if constexpr (std::has_single_bit(I + 1uz))
      return elems_[(wr_ - 1uz) % (I + 1uz)];
    else return wr_ ? elems_[wr_ - 1uz] : elems_[I];
  }

  /// Access the last element
  ///
  /// \return const_reference Constant reference to the last element
  constexpr const_reference back() const {
    if (empty()) return elems_[wr_];
    if constexpr (std::has_single_bit(I + 1uz))
      return elems_[(wr_ - 1uz) % (I + 1uz)];
    else return wr_ ? elems_[wr_ - 1uz] : elems_[I];
  }

  /// Adds an element to the front
  constexpr void push_front() {
    if (full()) return;
    if constexpr (std::has_single_bit(I + 1uz)) rd_ = (rd_ - 1) % (I + 1uz);
    else rd_ = rd_ ? rd_ - 1 : I;
  }

  /// Adds an element to the front
  ///
  /// \param  element Element to add
  constexpr void push_front(value_type const& element) {
    if (full()) return;
    if constexpr (std::has_single_bit(I + 1uz))
      rd_ = static_cast<index_type>((rd_ - 1uz) % (I + 1uz));
    else rd_ = static_cast<index_type>(rd_ ? rd_ - 1uz : I);
    elems_[rd_] = element;
  }

  /// Adds an element to the front
  ///
  /// \param  element Element to add
  constexpr void push_front(value_type&& element) {
    if (full()) return;
    if constexpr (std::has_single_bit(I + 1uz))
      rd_ = static_cast<index_type>((rd_ - 1uz) % (I + 1uz));
    else rd_ = static_cast<index_type>(rd_ ? rd_ - 1uz : I);
    elems_[rd_] = std::move(element);
  }

  /// Adds an element to the end
  constexpr void push_back() {
    if (full()) return;
    wr_ = static_cast<index_type>((wr_ + 1uz) % (I + 1uz));
  }

  /// Adds an element to the end
  ///
  /// \param  element Element to add
  constexpr void push_back(value_type const& element) {
    if (full()) return;
    elems_[wr_] = element;
    wr_ = static_cast<index_type>((wr_ + 1uz) % (I + 1uz));
  }

  /// Adds an element to the end
  ///
  /// \param  element Element to add
  constexpr void push_back(value_type&& element) {
    if (full()) return;
    elems_[wr_] = std::move(element);
    wr_ = static_cast<index_type>((wr_ + 1uz) % (I + 1uz));
  }

  /// Delete first element
  constexpr void pop_front() {
    if (empty()) return;
    rd_ = static_cast<index_type>((rd_ + 1uz) % (I + 1uz));
  }

  /// Delete last element
  constexpr void pop_back() {
    if (empty()) return;
    if constexpr (std::has_single_bit(I + 1uz))
      wr_ = static_cast<index_type>((wr_ - 1uz) % (I + 1uz));
    else wr_ = static_cast<index_type>(wr_ ? wr_ - 1uz : I);
  }

  constexpr iterator begin() { return iterator{this, rd_}; }
  constexpr const_iterator begin() const { return const_iterator{this, rd_}; }
  constexpr const_iterator cbegin() const { return begin(); }

  constexpr iterator end() { return iterator{this, wr_}; }
  constexpr const_iterator end() const { return const_iterator{this, wr_}; }
  constexpr const_iterator cend() const { return end(); }

  constexpr reverse_iterator rbegin() { return reverse_iterator{end()}; }
  constexpr const_reverse_iterator rbegin() const {
    return const_reverse_iterator{end()};
  }
  constexpr const_reverse_iterator crbegin() const { return rbegin(); }

  constexpr reverse_iterator rend() { return reverse_iterator{begin()}; }
  constexpr const_reverse_iterator rend() const {
    return const_reverse_iterator{begin()};
  }
  constexpr const_reverse_iterator crend() const { return rend(); }

  friend constexpr bool operator==(circular_array const& lhs,
                                   circular_array const& rhs) {
    return std::ranges::equal(lhs, rhs);
  }

private:
  std::array<T, I + 1uz> elems_;
  index_type rd_{};
  index_type wr_{};
};

template<typename T, typename... Ts>
circular_array(T&&, Ts&&...) -> circular_array<T, 1uz + sizeof...(Ts)>;

template<typename T, size_t I>
[[nodiscard]] constexpr auto empty(circular_array<T, I> const& c) {
  return std::empty(c);
}

template<typename T, size_t I>
constexpr auto size(circular_array<T, I> const& c) {
  return std::size(c);
}

template<typename T, size_t I>
constexpr auto ssize(circular_array<T, I> const& c) {
  using R = std::common_type_t<std::ptrdiff_t,
                               std::make_signed_t<decltype(std::size(c))>>;
  return static_cast<R>(std::size(c));
}

template<typename T, size_t I>
constexpr auto begin(circular_array<T, I>& c) {
  return std::begin(c);
}

template<typename T, size_t I>
constexpr auto begin(circular_array<T, I> const& c) {
  return std::begin(c);
}

template<typename T, size_t I>
constexpr auto cbegin(circular_array<T, I> const& c) {
  return std::begin(c);
}

template<typename T, size_t I>
constexpr auto end(circular_array<T, I>& c) {
  return std::end(c);
}

template<typename T, size_t I>
constexpr auto end(circular_array<T, I> const& c) {
  return std::end(c);
}

template<typename T, size_t I>
constexpr auto cend(circular_array<T, I> const& c) {
  return std::end(c);
}

template<typename T, size_t I>
constexpr auto rbegin(circular_array<T, I>& c) {
  return std::rbegin(c);
}

template<typename T, size_t I>
constexpr auto rbegin(circular_array<T, I> const& c) {
  return std::rbegin(c);
}

template<typename T, size_t I>
constexpr auto crbegin(circular_array<T, I> const& c) {
  return std::rbegin(c);
}

template<typename T, size_t I>
constexpr auto rend(circular_array<T, I>& c) {
  return std::rend(c);
}

template<typename T, size_t I>
constexpr auto rend(circular_array<T, I> const& c) {
  return std::rend(c);
}

template<typename T, size_t I>
constexpr auto crend(circular_array<T, I> const& c) {
  return std::rend(c);
}

}  // namespace ztl
