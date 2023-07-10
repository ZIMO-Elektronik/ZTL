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
#include <cstddef>
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
  template<bool Const>
  struct iterator_ {
    friend iterator_<true>;

    // Types
    using value_type = std::conditional_t<Const, T const, T>;
    using size_type = smallest_unsigned_t<I + 1uz>;
    using difference_type = ptrdiff_t;
    using reference = std::conditional_t<Const, T const&, T&>;
    using pointer = std::conditional_t<Const, T const*, T*>;
    using iterator_category = std::random_access_iterator_tag;
    using circular_array_pointer =
      std::conditional_t<Const, circular_array const*, circular_array*>;

    // Construct/copy/destroy
    constexpr iterator_() = default;
    constexpr iterator_(circular_array_pointer ptr, size_type i)
      : _ptr{ptr}, _i{i} {}
    constexpr iterator_(iterator_ const&) = default;
    constexpr iterator_(iterator_<false> const& rhs) requires Const
      : _ptr{rhs._ptr}, _i{rhs._i} {}
    constexpr iterator_& operator=(iterator_ const&) = default;
    constexpr iterator_& operator=(iterator_ const& rhs) requires Const
    {
      _ptr = rhs._ptr;
      _i = rhs._i;
      return *this;
    }

    constexpr reference operator[](size_type i) const {
      return _ptr->_data[(_i + i) % (I + 1uz)];
    }

    constexpr iterator_& operator++() {
      _i = static_cast<size_type>((_i + 1zu) % (I + 1zu));
      return *this;
    }

    constexpr iterator_ operator++(int) {
      iterator_ retval{*this};
      _i = static_cast<size_type>((_i + 1uz) % (I + 1uz));
      return retval;
    }

    constexpr iterator_& operator--() {
      if constexpr (std::has_single_bit(I + 1uz))
        _i = static_cast<size_type>((_i - 1uz) % (I + 1uz));
      else _i = static_cast<size_type>(_i ? _i - 1uz : I);
      return *this;
    }

    constexpr iterator_ operator--(int) {
      iterator_ retval{*this};
      if constexpr (std::has_single_bit(I + 1uz))
        _i = static_cast<size_type>((_i - 1uz) % (I + 1uz));
      else _i = static_cast<size_type>(_i ? _i - 1uz : I);
      return retval;
    }

    constexpr iterator_ operator+(difference_type n) const {
      return iterator_{_ptr, static_cast<size_type>((_i + n) % (I + 1uz))};
    }

    constexpr iterator_& operator+=(difference_type n) {
      _i = static_cast<size_type>((_i + n) % (I + 1uz));
      return *this;
    }

    constexpr difference_type operator-(iterator_ const& rhs) const {
      if (auto const diff{static_cast<difference_type>(_i - rhs._i)};
          _ptr->_rd <= _ptr->_wr)
        return diff;
      else {
        if (diff < 0) return diff + static_cast<difference_type>(I + 1uz);
        else if (diff > 0) return diff - static_cast<difference_type>(I + 1uz);
        else return 0;
      }
    }

    constexpr iterator_ operator-(difference_type n) const {
      if constexpr (std::has_single_bit(I + 1uz))
        return iterator_{_ptr, static_cast<size_type>((_i - n) % (I + 1uz))};
      else
        return iterator_{
          _ptr, static_cast<size_type>(_i < n ? I + 1uz + _i - n : _i - n)};
    }

    constexpr iterator_& operator-=(difference_type n) {
      if constexpr (std::has_single_bit(I + 1uz))
        _i = static_cast<size_type>((_i - n) % (I + 1uz));
      else _i = static_cast<size_type>(_i < n ? I + 1uz + _i - n : _i - n);
      return *this;
    }

    constexpr reference operator*() const { return _ptr->_data[_i]; }

    constexpr pointer operator->() const { return &_ptr->_data[_i]; }

    constexpr bool operator==(iterator_ const& rhs) const {
      return _i == rhs._i;
    }

    constexpr bool operator!=(iterator_ const& rhs) const {
      return !(*this == rhs);
    }

    constexpr bool operator<(iterator_ const& rhs) const {
      return _ptr->_rd <= _ptr->_wr ? _i < rhs._i : _i > rhs._i;
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
    circular_array_pointer _ptr{nullptr};
    size_type _i{};
  };

  // Types
  using value_type = T;
  using size_type = smallest_unsigned_t<I + 1uz>;
  using difference_type = ptrdiff_t;
  using reference = T&;
  using const_reference = T const&;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using iterator = iterator_<false>;
  using const_iterator = iterator_<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Construct/copy/destroy
  constexpr circular_array() = default;

  template<std::convertible_to<T>... Us>
  constexpr circular_array(Us&&... us) requires(sizeof...(Us) < I + 1uz)
    : _data{static_cast<T>(us)...}, _wr{sizeof...(Us)} {}

  // Iterators
  constexpr iterator begin() { return iterator{this, _rd}; }
  constexpr const_iterator begin() const { return const_iterator{this, _rd}; }
  constexpr iterator end() { return iterator{this, _wr}; }
  constexpr const_iterator end() const { return const_iterator{this, _wr}; }
  constexpr reverse_iterator rbegin() { return reverse_iterator{end()}; }
  constexpr const_reverse_iterator rbegin() const {
    return const_reverse_iterator{end()};
  }
  constexpr reverse_iterator rend() { return reverse_iterator{begin()}; }
  constexpr const_reverse_iterator rend() const {
    return const_reverse_iterator{begin()};
  }

  constexpr const_iterator cbegin() const { return begin(); }
  constexpr const_iterator cend() const { return end(); }
  constexpr const_reverse_iterator crbegin() const { return rbegin(); }
  constexpr const_reverse_iterator crend() const { return rend(); }

  // Capacity
  constexpr bool empty() const { return _rd == _wr; }
  constexpr bool full() const { return _rd == (_wr + 1uz) % (I + 1uz); }
  constexpr size_type size() const {
    if (_rd <= _wr) return static_cast<size_type>(_wr - _rd);
    else return static_cast<size_type>(I + 1uz - _rd + _wr);
  }
  constexpr size_type max_size() const { return I; }
  constexpr size_type capacity() const { return I; }

  // Element access
  constexpr reference operator[](size_type i) {
    return _data[(_rd + i) % (I + 1uz)];
  }
  constexpr const_reference operator[](size_type i) const {
    return _data[(_rd + i) % (I + 1uz)];
  }
  constexpr reference at(size_type i) {
    return _data.at((_rd + i) % (I + 1uz));
  }
  constexpr const_reference at(size_type i) const {
    return at((_rd + i) % (I + 1uz));
  }
  constexpr reference front() { return _data[_rd]; }
  constexpr const_reference front() const { return _data[_rd]; }
  constexpr reference back() {
    assert(!empty());
    if constexpr (std::has_single_bit(I + 1uz))
      return _data[(_wr - 1uz) % (I + 1uz)];
    else return _wr ? _data[_wr - 1uz] : _data[I];
  }
  constexpr const_reference back() const {
    assert(!empty());
    if constexpr (std::has_single_bit(I + 1uz))
      return _data[(_wr - 1uz) % (I + 1uz)];
    else return _wr ? _data[_wr - 1uz] : _data[I];
  }

  // Data access
  constexpr pointer data() { return std::data(_data); }
  constexpr const_pointer data() const { return std::data(_data); }

  // Modifiers
  constexpr void push_front() {
    assert(!full());
    if constexpr (std::has_single_bit(I + 1uz)) _rd = (_rd - 1) % (I + 1uz);
    else _rd = _rd ? _rd - 1 : I;
  }
  constexpr void push_front(value_type const& element) {
    assert(!full());
    if constexpr (std::has_single_bit(I + 1uz))
      _rd = static_cast<size_type>((_rd - 1uz) % (I + 1uz));
    else _rd = static_cast<size_type>(_rd ? _rd - 1uz : I);
    _data[_rd] = element;
  }
  constexpr void push_front(value_type&& element) {
    assert(!full());
    if constexpr (std::has_single_bit(I + 1uz))
      _rd = static_cast<size_type>((_rd - 1uz) % (I + 1uz));
    else _rd = static_cast<size_type>(_rd ? _rd - 1uz : I);
    _data[_rd] = std::move(element);
  }
  constexpr void pop_front() {
    assert(!empty());
    _rd = static_cast<size_type>((_rd + 1uz) % (I + 1uz));
  }
  constexpr void push_back() {
    assert(!full());
    _wr = static_cast<size_type>((_wr + 1uz) % (I + 1uz));
  }
  constexpr void push_back(value_type const& element) {
    assert(!full());
    _data[_wr] = element;
    _wr = static_cast<size_type>((_wr + 1uz) % (I + 1uz));
  }
  constexpr void push_back(value_type&& element) {
    assert(!full());
    _data[_wr] = std::move(element);
    _wr = static_cast<size_type>((_wr + 1uz) % (I + 1uz));
  }
  constexpr void pop_back() {
    assert(!empty());
    if constexpr (std::has_single_bit(I + 1uz))
      _wr = static_cast<size_type>((_wr - 1uz) % (I + 1uz));
    else _wr = static_cast<size_type>(_wr ? _wr - 1uz : I);
  }
  constexpr void clear() { _rd = _wr = 0u; }

  friend constexpr auto operator<=>(circular_array const& lhs,
                                    circular_array const& rhs) = default;

private:
  std::array<T, I + 1uz> _data;
  size_type _rd{};
  size_type _wr{};
};

template<typename T, typename... Ts>
circular_array(T&&, Ts&&...) -> circular_array<T, sizeof...(Ts) + 1uz>;

// Iterators
template<typename T, size_t I>
constexpr auto begin(circular_array<T, I>& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto begin(circular_array<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto end(circular_array<T, I>& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto end(circular_array<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto rbegin(circular_array<T, I>& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto rbegin(circular_array<T, I> const& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto rend(circular_array<T, I>& c) -> decltype(c.rend()) {
  return c.rend();
}
template<typename T, size_t I>
constexpr auto rend(circular_array<T, I> const& c) -> decltype(c.rend()) {
  return c.rend();
}

template<typename T, size_t I>
constexpr auto cbegin(circular_array<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto cend(circular_array<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto crbegin(circular_array<T, I> const& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto crend(circular_array<T, I> const& c) -> decltype(c.rend()) {
  return c.rend();
}

// Capacity
template<typename T, size_t I>
[[nodiscard]] constexpr auto empty(circular_array<T, I> const& c)
  -> decltype(c.empty()) {
  return c.empty();
}
template<typename T, size_t I>
[[nodiscard]] constexpr auto full(circular_array<T, I> const& c)
  -> decltype(c.full()) {
  return c.full();
}
template<typename T, size_t I>
constexpr auto size(circular_array<T, I> const& c) -> decltype(c.size()) {
  return c.size();
}
template<typename T, size_t I>
constexpr auto ssize(circular_array<T, I> const& c)
  -> std::common_type_t<std::ptrdiff_t,
                        std::make_signed_t<decltype(c.size())>> {
  using R =
    std::common_type_t<ptrdiff_t, std::make_signed_t<decltype(c.size())>>;
  return static_cast<R>(c.size());
}

}  // namespace ztl
