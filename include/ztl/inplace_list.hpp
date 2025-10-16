// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Inplace list
///
/// \file   ztl/inplace_list.hpp
/// \author Jonas Gahlert
/// \date   25/09/2025

#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <ranges>
#include "concepts.hpp"
#include "inplace_vector.hpp"
#include "limits.hpp"
#include "static_list.hpp"

namespace ztl {

/// inplace_list implements a doubly linked list. In contrast to `std::list`, no
/// allocation is made when inserting a new node. Instead, a fixed-size memory
/// is provided internally.
///
/// To mark the end-element, a dummy-link is constructed. This link (returned by
/// e.g. `end()`) must not be dereferenced
///
/// \tparam T Type of element
/// \tparam I Size
template<typename T, size_t I>
struct inplace_list {
  template<bool Const>
  struct _iterator {
    friend inplace_list<T, I>;

    // Types
    using value_type = T;
    using pointer = std::conditional_t<Const, value_type const*, value_type*>;
    using reference = std::conditional_t<Const, value_type const&, value_type&>;
    using size_type = smallest_unsigned_t<I>;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using link_pointer =
      std::conditional_t<Const, detail::link const*, detail::link*>;
    using node_pointer =
      std::conditional_t<Const, node<value_type> const*, node<value_type>*>;

    // Construct/copy/destroy
    constexpr _iterator() = default;
    constexpr _iterator(link_pointer link) : _link{link} {}

    constexpr _iterator& operator++() {
      _link = _link->next;
      return *this;
    }
    constexpr _iterator operator++(int) {
      _iterator const tmp{*this};
      _link = _link->next;
      return tmp;
    }
    constexpr _iterator& operator--() {
      _link = _link->prev;
      return *this;
    }
    constexpr _iterator operator--(int) {
      _iterator const tmp{*this};
      _link = _link->prev;
      return tmp;
    }

    constexpr bool operator==(_iterator const& rhs) const {
      return _link == rhs._link;
    }
    constexpr bool operator!=(_iterator const& rhs) const {
      return !(*this == rhs);
    }

    constexpr reference operator*() const {
      return static_cast<node_pointer>(_link)->_element;
    }
    constexpr pointer operator->() const {
      return &static_cast<node_pointer>(_link)->_element;
    }

  private:
    link_pointer _link{nullptr};
  };

  // Types
  using value_type = T;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = T&;
  using const_reference = value_type const&;
  using size_type = smallest_unsigned_t<I>;
  using iterator = _iterator<false>;
  using const_iterator = _iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Construct/copy/destroy
  constexpr inplace_list() = default;
  template<std::convertible_to<T>... Ts>
  constexpr inplace_list(Ts&&... ts) requires(sizeof...(Ts) <= I)
  {
    (push_back(static_cast<T>(ts)), ...);
  }
  constexpr inplace_list(inplace_list const& lhs)
    : _storage{lhs._storage}, _free{lhs._free} {
    if (lhs.empty()) return;

    // Recalculate links
    auto it{lhs.begin()};
    for (; it != lhs.end(); it++) {
      auto const i{
        static_cast<size_type>((std::bit_cast<size_t>((it._link)) -
                                std::bit_cast<size_t>(lhs._storage.data())) /
                               sizeof(node<T>))};
      _storage[i].next = (it._link->next == lhs.end()._link)
                           ? &_tail
                           : &_storage[static_cast<size_type>(
                               (std::bit_cast<size_t>(it._link->next) -
                                std::bit_cast<size_t>(lhs._storage.data())) /
                               sizeof(node<T>))];
      _storage[i].next->prev = &_storage[i];
    }
    // Recalculate begin
    _tail.next = &_storage[static_cast<size_type>(
      (std::bit_cast<size_t>(lhs.begin()) -
       std::bit_cast<size_t>(lhs._storage.data())) /
      sizeof(node<T>))];
  }

  // Capacity
  constexpr size_type size() const {
    return static_cast<size_type>(I - _free.size());
  }
  constexpr size_type max_size() const { return I; }
  constexpr size_type capacity() const { return I; }
  constexpr bool empty() const { return _free.full(); }
  constexpr bool full() const { return _free.empty(); }

  // Element access
  constexpr reference front() { return *begin(); }
  constexpr const_reference front() const { return front(); }
  constexpr reference back() { return *iterator{_tail.prev}; }
  constexpr const_reference back() const { return back(); }
  constexpr reference at(size_type i) {
    assert(i < size());
    auto it{begin()};
    while (i-- != 0) { it--; }
    return *it;
  }
  constexpr const_reference at(size_type i) const { return at(); }

  // Modifiers
  constexpr reference push_front(T const& t) { return *insert(begin(), t); }
  constexpr void pop_front() { erase(begin()); }

  constexpr reference push_back(T const& t) { return *insert(end(), t); }
  constexpr void pop_back() { erase(iterator{_tail.prev}); }

  template<class... Args>
  constexpr reference emplace_front(Args&&... args) {
    return *emplace(begin(), args...);
  }
  template<class... Args>
  constexpr reference emplace_back(Args&&... args) {
    return *emplace(end(), args...);
  }
  template<class... Args>
  constexpr pointer try_emplace_front(Args&&... args) {
    if (full()) return nullptr;
    return &unchecked_emplace_front(args...);
  }
  template<class... Args>
  constexpr pointer try_emplace_back(Args&&... args) {
    if (full()) return nullptr;
    return &unchecked_emplace_back(args...);
  }
  template<class... Args>
  constexpr reference unchecked_emplace_front(Args&&... args) {
    return *emplace(begin(), args...);
  }
  template<class... Args>
  constexpr reference unchecked_emplace_back(Args&&... args) {
    return *emplace(end(), args...);
  }
  template<class... Args>
  constexpr iterator emplace(iterator pos, Args&&... args) {
    assert(!full());
    auto const index{_free.back()};
    _free.pop_back();
    new (&_storage[index]) node<value_type>(args...);
    _storage[index].prev = pos._link->prev;
    _storage[index].next = pos._link;
    pos._link->prev = pos._link->prev->next = &_storage[index];
    return iterator{&_storage[index]};
  }
  template<container_compatible_range<T> R>
  constexpr void prepend_range(R&& r) {
    return insert_range(begin(), r);
  }
  template<container_compatible_range<T> R>
  constexpr void append_range(R&& r) {
    return insert_range(end(), r);
  }
  template<container_compatible_range<T> R>
  constexpr void insert_range(iterator pos, R&& r) {
    auto first{r.begin()};
    auto const end{r.end()};
    while (first != end) emplace(pos, *first++);
  }
  constexpr iterator insert(iterator pos, T const& t) {
    assert(!full());
    auto const index{_free.back()};
    _free.pop_back();
    _storage[index] = node<T>{t};
    _storage[index].prev = pos._link->prev;
    _storage[index].next = pos._link;
    pos._link->prev = pos._link->prev->next = &_storage[index];
    return iterator{&_storage[index]};
  }

  constexpr iterator erase(iterator pos) {
    assert(!empty());
    auto const tmp{pos._link->next};
    pos._link->prev->next = pos._link->next;
    pos._link->next->prev = pos._link->prev;
    pos._link->next = pos._link->prev = nullptr;
    _free.push_back(
      static_cast<size_type>((std::bit_cast<size_t>(pos._link) -
                              std::bit_cast<size_t>(_storage.data())) /
                             sizeof(node<T>)));
    return iterator{tmp};
  }
  constexpr iterator move(iterator elem, iterator pos) {
    if (elem == pos) return elem;

    elem._link->prev->next = elem._link->next;
    elem._link->next->prev = elem._link->prev;
    elem._link->prev = pos._link->prev;
    elem._link->next = pos._link;
    pos._link->prev = pos._link->prev->next = elem._link;
    return elem;
  }
  constexpr void clear() {
    iterator first{begin()};
    iterator const last{end()};
    while (first != last) {
      iterator next = first;
      ++next;
      erase(first);
      first = next;
    }
  }

  // Operations
  template<typename F>
  constexpr void remove_if(F&& f) {
    iterator first{begin()};
    iterator const last{end()};
    while (first != last) {
      iterator next = first;
      ++next;
      if (f(*first)) erase(first);
      first = next;
    }
  }
  constexpr void unique() {
    iterator first{begin()};
    iterator const last{end()};
    while (first != last) {
      iterator next = first;
      ++next;
      if (*first == *next) erase(next);
      else ++first;
    }
  }

  // Iterators
  constexpr iterator begin() { return {_tail.next}; }
  constexpr const_iterator begin() const { return {_tail.next}; }
  constexpr iterator end() { return {&_tail}; }
  constexpr const_iterator end() const { return {&_tail}; }

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

  // Non-member functions
  friend constexpr auto operator==(inplace_list const& lhs,
                                   inplace_list const& rhs) {
    return std::size(lhs) == std::size(rhs) && std::ranges::equal(lhs, rhs);
  }
  friend constexpr auto operator<=>(inplace_list const& lhs,
                                    inplace_list const& rhs) {
    return std::lexicographical_compare_three_way(std::cbegin(lhs),
                                                  std::cend(lhs),
                                                  std::cbegin(rhs),
                                                  std::cend(rhs),
                                                  std::compare_three_way{});
  }

private:
  detail::link _tail{&_tail, &_tail};

  std::array<node<value_type>, I> _storage{};
  ztl::inplace_vector<size_type, I> _free{std::invoke(
    []<size_type... Is>(std::integer_sequence<size_type, Is...>) {
      return ztl::inplace_vector<size_type, I>{Is...};
    },
    std::make_integer_sequence<size_type, I>{})};
};

template<typename T, typename... Ts>
inplace_list(T&&, Ts&&...) -> inplace_list<T, sizeof...(Ts) + 1uz>;

// Iterators
template<typename T, size_t I>
constexpr auto begin(inplace_list<T, I>& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto begin(inplace_list<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto end(inplace_list<T, I>& c) -> decltype(c.end()) {
  return c.end();
}
template<typename T, size_t I>
constexpr auto end(inplace_list<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}

template<typename T, size_t I>
constexpr auto cbegin(inplace_list<T, I> const& c) -> decltype(c.begin()) {
  return c.begin();
}
template<typename T, size_t I>
constexpr auto cend(inplace_list<T, I> const& c) -> decltype(c.end()) {
  return c.end();
}

// Capacity
template<typename T, size_t I>
[[nodiscard]] constexpr auto empty(inplace_list<T, I> const& c)
  -> decltype(c.empty()) {
  return c.empty();
}
template<typename T, size_t I>
[[nodiscard]] constexpr auto full(inplace_list<T, I> const& c)
  -> decltype(c.full()) {
  return c.full();
}
template<typename T, size_t I>
constexpr auto size(inplace_list<T, I> const& c) -> decltype(c.size()) {
  return c.size();
}
template<typename T, size_t I>
constexpr auto ssize(inplace_list<T, I> const& c)
  -> std::common_type_t<std::ptrdiff_t,
                        std::make_signed_t<decltype(c.size())>> {
  using R =
    std::common_type_t<ptrdiff_t, std::make_signed_t<decltype(c.size())>>;
  return static_cast<R>(c.size());
}

} // namespace ztl
