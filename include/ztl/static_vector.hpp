// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Static vector
///
/// \file   ztl/static_vector.hpp
/// \author Vincent Hamp
/// \date   10/07/2023

#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include "limits.hpp"

namespace ztl {

template<typename T, size_t I>
struct static_vector {
  // Types
  using value_type = T;
  using size_type = ztl::smallest_unsigned_t<I>;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using iterator = std::array<value_type, I>::iterator;
  using const_iterator = std::array<value_type, I>::const_iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Construct/copy/destroy
  constexpr static_vector() = default;
  template<std::convertible_to<T>... Ts>
  constexpr static_vector(Ts&&... ts) requires(sizeof...(Ts) <= I)
    : _data{static_cast<T>(ts)...}, _size{sizeof...(Ts)} {}

  // Iterators
  constexpr iterator begin() { return std::begin(_data); }
  constexpr const_iterator begin() const { return std::begin(_data); }
  constexpr iterator end() { return std::begin(_data) + size(); }
  constexpr const_iterator end() const { return std::begin(_data) + size(); }
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
  constexpr bool empty() const { return size() == 0uz; }
  constexpr bool full() const { return size() == I; }
  constexpr size_type size() const { return _size; }
  constexpr size_type max_size() const { return I; }
  constexpr size_type capacity() const { return I; }
  constexpr void resize(size_type count) {
    assert(count <= I);
    _size = count;
  }
  constexpr void resize(size_type count, value_type const& value) {
    resize(count);
    std::fill_n(begin(), count, value);
  }

  // Element access
  constexpr reference operator[](size_type i) { return _data[i]; }
  constexpr const_reference operator[](size_type i) const { return _data[i]; }
  constexpr reference at(size_type i) { return _data.at(i); }
  constexpr const_reference at(size_type i) const { return at(i); }
  constexpr reference front() { return _data[0uz]; }
  constexpr const_reference front() const { return _data[0uz]; }
  constexpr reference back() { return _data[_size - 1uz]; }
  constexpr const_reference back() const { return _data[_size - 1uz]; }

  // Data access
  constexpr pointer data() { return std::data(_data); }
  constexpr const_pointer data() const { return std::data(_data); }

  // Modifiers
  constexpr void push_back(value_type const& value) {
    assert(!full());
    _data[_size++] = value;
  }
  constexpr void push_back(value_type&& value) {
    assert(!full());
    _data[_size++] = std::move(value);
  }
  constexpr void pop_back() {
    assert(!empty());
    --_size;
  }
  constexpr void clear() { resize(0uz); }

  // Non-member functions
  friend constexpr auto operator<=>(static_vector const& lhs,
                                    static_vector const& rhs) = default;

private:
  std::array<value_type, I> _data{};
  ztl::smallest_unsigned_t<I> _size{};
};

template<typename T, typename... Ts>
static_vector(T&&, Ts&&...) -> static_vector<T, sizeof...(Ts) + 1uz>;

// Iterators
template<typename T, size_t I>
constexpr auto begin(static_vector<T, I>& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto begin(static_vector<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto end(static_vector<T, I>& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto end(static_vector<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto rbegin(static_vector<T, I>& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto rbegin(static_vector<T, I> const& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto rend(static_vector<T, I>& c) -> decltype(c.rend()) {
  return c.rend();
}
template<typename T, size_t I>
constexpr auto rend(static_vector<T, I> const& c) -> decltype(c.rend()) {
  return c.rend();
}

template<typename T, size_t I>
constexpr auto cbegin(static_vector<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto cend(static_vector<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto crbegin(static_vector<T, I> const& c) -> decltype(c.rbegin()) {
  return c.rbegin();
}
template<typename T, size_t I>
constexpr auto crend(static_vector<T, I> const& c) -> decltype(c.rend()) {
  return c.rend();
}

// Capacity
template<typename T, size_t I>
[[nodiscard]] constexpr auto empty(static_vector<T, I> const& c)
  -> decltype(c.empty()) {
  return c.empty();
}
template<typename T, size_t I>
[[nodiscard]] constexpr auto full(static_vector<T, I> const& c)
  -> decltype(c.full()) {
  return c.full();
}
template<typename T, size_t I>
constexpr auto size(static_vector<T, I> const& c) -> decltype(c.size()) {
  return c.size();
}
template<typename T, size_t I>
constexpr auto ssize(static_vector<T, I> const& c)
  -> std::common_type_t<std::ptrdiff_t,
                        std::make_signed_t<decltype(c.size())>> {
  using R =
    std::common_type_t<ptrdiff_t, std::make_signed_t<decltype(c.size())>>;
  return static_cast<R>(c.size());
}

}  // namespace ztl
