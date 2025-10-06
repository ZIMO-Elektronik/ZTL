// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Static list
///
/// \file   ztl/static_list.hpp
/// \author Vincent Hamp
/// \date   09/02/2017

#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace ztl {

namespace detail {

/// Base containing next and previous pointers for node class
struct link {
  link* next{nullptr};
  link* prev{nullptr};
};

} // namespace detail

/// node implementation
///
/// \tparam T Type of element
template<typename T>
struct node : detail::link {
  constexpr node() = default;
  constexpr node(T element) : _element{element} {}
  T _element;
};

/// static_list implements a doubly linked list. In contrast to the std version
/// only externally created nodes can be hooked in. The private static link
/// instance acts as end node. Care must be taken not to dereference that node,
/// since it contains no actual element. Since the class is entirely static,
/// every new list must contain a unique type as template parameter.
///
/// \tparam T Type of element
template<typename T>
struct static_list {
  struct iterator {
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr iterator() = default;
    constexpr iterator(detail::link* link) : _link{link} {}

    iterator& operator++() {
      _link = _link->next;
      return *this;
    }

    iterator operator++(int) {
      iterator const tmp{*this};
      _link = _link->next;
      return tmp;
    }

    iterator& operator--() {
      _link = _link->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator const tmp{*this};
      _link = _link->prev;
      return tmp;
    }

    bool operator==(iterator const& rhs) const { return _link == rhs._link; }
    bool operator!=(iterator const& rhs) const { return !(*this == rhs); }

    reference operator*() const {
      return static_cast<node<value_type>*>(_link)->_element;
    }
    pointer operator->() const {
      return &static_cast<node<value_type>*>(_link)->_element;
    }

    detail::link* _link{nullptr};
  };

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using size_type = size_t;

  // Iterators
  static iterator begin() { return iterator{_tail.next}; }
  static iterator end() { return iterator{&_tail}; }

  // Capacity
  static bool empty() { return begin() == end(); }
  static size_type size() {
    return static_cast<size_type>(
      std::count_if(begin(), end(), [](T) { return true; }));
  }

  // Element access
  static reference front() { return *begin(); }
  static reference back() { return *iterator{_tail.prev}; }

  // Modifiers
  static void push_front(node<value_type>& node) { insert(begin(), node); }
  static void pop_front() { erase(begin()); }
  static void push_back(node<value_type>& node) { insert(end(), node); }
  static void pop_back() { erase(iterator{_tail.prev}); }
  static iterator insert(iterator pos, node<value_type>& node) {
    node.prev = pos._link->prev;
    node.next = pos._link;
    pos._link->prev = pos._link->prev->next = &node;
    return iterator{&node};
  }
  static iterator erase(iterator pos) {
    auto const tmp{pos._link->next};
    pos._link->prev->next = pos._link->next;
    pos._link->next->prev = pos._link->prev;
    pos._link->next = pos._link->prev = nullptr;
    return iterator{tmp};
  }
  static void clear() {
    iterator first{begin()};
    iterator const last{end()};
    while (first != last) {
      iterator next = first;
      ++next;
      erase(first);
      first = next;
    }
  }
  template<typename F>
  static void remove_if(F&& f) {
    iterator first{begin()};
    iterator const last{end()};
    while (first != last) {
      iterator next = first;
      ++next;
      if (f(*first)) erase(first);
      first = next;
    }
  }

private:
  static detail::link _tail;
};

template<typename T>
detail::link static_list<T>::_tail{&_tail, &_tail};

} // namespace ztl
