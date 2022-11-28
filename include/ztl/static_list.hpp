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

}  // namespace detail

/// node implementation
///
/// \tparam T Type of element
template<typename T>
struct node : detail::link {
  constexpr node() = default;
  constexpr node(T element) : element_{element} {}
  T element_;
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
    using node_ = node<value_type>;

    constexpr iterator() = default;
    constexpr iterator(detail::link* link) : link_{link} {}

    iterator& operator++() {
      link_ = link_->next;
      return *this;
    }

    iterator operator++(int) {
      iterator const tmp{*this};
      link_ = link_->next;
      return tmp;
    }

    iterator& operator--() {
      link_ = link_->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator const tmp{*this};
      link_ = link_->prev;
      return tmp;
    }

    bool operator==(iterator const& rhs) const { return link_ == rhs.link_; }
    bool operator!=(iterator const& rhs) const { return !(*this == rhs); }

    reference operator*() const { return static_cast<node_*>(link_)->element_; }
    pointer operator->() const { return &static_cast<node_*>(link_)->element_; }

    detail::link* link_{nullptr};
  };

  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using size_type = size_t;
  using node_ = node<value_type>;

  /// Returns the number of elements in the container
  ///
  /// \return Number of elements in the container
  static size_type size() {
    return static_cast<size_type>(
      std::count_if(begin(), end(), [](T) { return true; }));
  }

  /// Checks if the container has no elements
  ///
  /// \return true  Container is empty
  /// \return false Container is not empty
  static bool empty() { return begin() == end(); }

  /// Access the first element
  ///
  /// \return reference Reference to the first element
  static reference front() { return *begin(); }

  /// Access the last element
  ///
  /// \return reference Reference to the last element
  static reference back() { return *iterator{tail_.prev}; }

  /// Prepends the given element value to the beginning of the container
  ///
  /// \param  node  Node to add
  static void push_front(node_& node) { insert(begin(), node); }

  /// Removes the first element of the container
  static void pop_front() { erase(begin()); }

  /// Appends the given element value to the end of the container
  ///
  /// \param  node  Node to add
  static void push_back(node_& node) { insert(end(), node); }

  /// Removes the last element of the container
  static void pop_back() { erase(iterator{tail_.prev}); }

  /// Inserts elements at the specified location in the container
  ///
  /// \param  pos   Iterator into the list
  /// \param  node  Node to be inserted
  /// \return Iterator that points to the inserted node
  static iterator insert(iterator pos, node_& node) {
    node.prev = pos.link_->prev;
    node.next = pos.link_;
    pos.link_->prev = pos.link_->prev->next = &node;
    return iterator{&node};
  }

  /// Erases the specified elements from the container
  ///
  /// \param  pos Iterator pointing at the node to be erased
  /// \return Iterator pointing to the next element (or end())
  static iterator erase(iterator pos) {
    auto const tmp{pos.link_->next};
    pos.link_->prev->next = pos.link_->next;
    pos.link_->next->prev = pos.link_->prev;
    pos.link_->next = pos.link_->prev = nullptr;
    return iterator{tmp};
  }

  /// Erases all elements from the container
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

  /// Remove all nodes satisfying a predicate
  ///
  /// Removes every node in the list for which the predicate returns true.
  /// Remaining nodes stay in list order.
  ///
  /// \tparam F Type of unary predicate
  /// \param  f Unary predicate callable object
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

  static iterator begin() { return iterator{tail_.next}; }

  static iterator end() { return iterator{&tail_}; }

private:
  static detail::link tail_;
};

template<typename T>
detail::link static_list<T>::tail_{&tail_, &tail_};

}  // namespace ztl
