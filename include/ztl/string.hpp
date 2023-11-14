// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// String
///
/// \file   ztl/string.hpp
/// \author Vincent Hamp
/// \date   10/05/2017

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include "utility.hpp"

namespace ztl {

/// Interprets an integer value in a byte string pointed to by str
///
/// \param  str Pointer to the null-terminated byte string to be interpreted
/// \return Integer value corresponding to the contents of str
constexpr int32_t atoi(char const* str) {
  while (*str == ' ') ++str;

  int32_t retval{0};
  int32_t sign{1};

  switch (*str) {
    case '-':
      ++str;
      sign = -1;
      break;

    case '+': ++str; break;
  }

  while (auto const c{*str++}) {
    if (c < '0' || c > '9') return retval;
    retval = retval * 10 + c - '0';
  }

  if (retval < 0) return 0;

  return retval * sign;
}

/// Copies the character string pointed to by src, including the null
/// terminator, to the character array whose first element is pointed to by
/// dest.
///
/// \param  dest  Pointer to the character array to write to
/// \param  src   Pointer to the null-terminated byte string to copy from
/// \return Pointer to the character array to write to
constexpr char* strcpy(char* dest, char const* src) {
  size_t count{};
  while (src[count]) {
    dest[count] = src[count];
    ++count;
  }
  dest[count] = src[count];
  return dest;
}

/// Copies at most count characters of the byte string pointed to by src
/// (including the terminating null character) to character array pointed to by
/// dest.
///
/// \param  dest  Pointer to the character array to copy to
/// \param  src   Pointer to the byte string to copy from
/// \param  count Maximum number of characters to copy
/// \return Pointer to the character array to copy to
constexpr char* strncpy(char* dest, char const* src, size_t count) {
  for (auto i{0uz}; i < count; ++i)
    if (src[i]) dest[i] = src[i];
    else {
      while (i < count) dest[i++] = '\0';
      break;
    }
  return dest;
}

/// Length of the null-terminated string str
///
/// \param  str Pointer to the null-terminated byte strings to compare
/// \return Length of the C string str
constexpr size_t strlen(char const* str) {
  size_t retval{};
  while (str[retval]) ++retval;
  return retval;
}

/// Compares two null-terminated byte strings lexicographically
///
/// \param  lhs Pointer to the null-terminated byte strings to compare
/// \param  rhs Pointer to the null-terminated byte strings to compare
/// \return <0  Negative value if lhs appears before rhs in lexicographical
///             order.
/// \return 0   Zero if lhs and rhs compare equal.
/// \return >0  Positive value if lhs appears after rhs in lexicographical
///             order.
constexpr int32_t strcmp(char const* lhs, char const* rhs) {
  size_t min{std::min(strlen(lhs), strlen(rhs))};
  size_t retval{};
  for (; retval < min; ++retval) {
    if (!lhs[retval] || !rhs[retval]) break;
    if (lhs[retval] != rhs[retval])
      return static_cast<uint8_t>(lhs[retval]) -
             static_cast<uint8_t>(rhs[retval]);
  }
  return 0;
}

/// Finds the first occurrence of the character ch in the byte string pointed to
/// by str.
///
/// \param  str Pointer to the null-terminated byte string to be analyzed
/// \param  ch  Character to search for
/// \return Pointer to the found character in str, or a null pointer if no such
///         character is found.
constexpr char const* strchr(char const* str, int ch) {
  while (*str != ch)
    if (!*str++) return nullptr;
  return str;
}

/// Finds the first occurrence of the byte string needle in the byte string
/// pointed to by haystack.
///
/// \param  haystack
/// \param  needle
/// \return Pointer to the first character of the found substring in haystack,
///         or a null pointer if no such character is found. If needle points to
///         an empty string, haystack is returned.
constexpr char const* strstr(char const* haystack, char const* needle) {
  char const* a{haystack};
  char const* b{needle};
  for (;;)
    if (!*b) return haystack;
    else if (!*a) return nullptr;
    else if (*a++ != *b++) {
      a = ++haystack;
      b = needle;
    }
}

/// Printf format to print int8 as binary
#define INT8_TO_BINARY_FORMAT "0b%c%c%c%c'%c%c%c%c"

/// Convert int8 to chars
#define INT8_TO_BINARY(int8)                                                   \
  (int8 & 0x80 ? '1' : '0'), (int8 & 0x40 ? '1' : '0'),                        \
    (int8 & 0x20 ? '1' : '0'), (int8 & 0x10 ? '1' : '0'),                      \
    (int8 & 0x08 ? '1' : '0'), (int8 & 0x04 ? '1' : '0'),                      \
    (int8 & 0x02 ? '1' : '0'), (int8 & 0x01 ? '1' : '0')

/// Printf format to print uint8 as binary
#define UINT8_TO_BINARY_FORMAT INT8_TO_BINARY_FORMAT

/// Convert uint8 to chars
#define UINT8_TO_BINARY INT8_TO_BINARY

/// Printf format to print char as binary
#define CHAR_TO_BINARY_FORMAT INT8_TO_BINARY_FORMAT

/// Convert char to chars
#define CHAR_TO_BINARY INT8_TO_BINARY

/// Printf format to print int16 as binary
#define INT16_TO_BINARY_FORMAT "0b%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c"

/// Convert int16 to chars
#define INT16_TO_BINARY(int16)                                                 \
  (int16 & 0x00008000 ? '1' : '0'), (int16 & 0x00004000 ? '1' : '0'),          \
    (int16 & 0x00002000 ? '1' : '0'), (int16 & 0x00001000 ? '1' : '0'),        \
    (int16 & 0x00000800 ? '1' : '0'), (int16 & 0x00000400 ? '1' : '0'),        \
    (int16 & 0x00000200 ? '1' : '0'), (int16 & 0x00000100 ? '1' : '0'),        \
    (int16 & 0x00000080 ? '1' : '0'), (int16 & 0x00000040 ? '1' : '0'),        \
    (int16 & 0x00000020 ? '1' : '0'), (int16 & 0x00000010 ? '1' : '0'),        \
    (int16 & 0x00000008 ? '1' : '0'), (int16 & 0x00000004 ? '1' : '0'),        \
    (int16 & 0x00000002 ? '1' : '0'), (int16 & 0x00000001 ? '1' : '0')

/// Printf format to print uint16 as binary
#define UINT16_TO_BINARY_FORMAT INT16_TO_BINARY_FORMAT

/// Convert uint16 to chars
#define UINT16_TO_BINARY INT16_TO_BINARY

/// Printf format to print int32 as binary
#define INT32_TO_BINARY_FORMAT                                                 \
  "0b%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c"

/// Convert int32 to chars
#define INT32_TO_BINARY(int32)                                                 \
  (int32 & 0x80000000 ? '1' : '0'), (int32 & 0x40000000 ? '1' : '0'),          \
    (int32 & 0x20000000 ? '1' : '0'), (int32 & 0x10000000 ? '1' : '0'),        \
    (int32 & 0x08000000 ? '1' : '0'), (int32 & 0x04000000 ? '1' : '0'),        \
    (int32 & 0x02000000 ? '1' : '0'), (int32 & 0x01000000 ? '1' : '0'),        \
    (int32 & 0x00800000 ? '1' : '0'), (int32 & 0x00400000 ? '1' : '0'),        \
    (int32 & 0x00200000 ? '1' : '0'), (int32 & 0x00100000 ? '1' : '0'),        \
    (int32 & 0x00080000 ? '1' : '0'), (int32 & 0x00040000 ? '1' : '0'),        \
    (int32 & 0x00020000 ? '1' : '0'), (int32 & 0x00010000 ? '1' : '0'),        \
    (int32 & 0x00008000 ? '1' : '0'), (int32 & 0x00004000 ? '1' : '0'),        \
    (int32 & 0x00002000 ? '1' : '0'), (int32 & 0x00001000 ? '1' : '0'),        \
    (int32 & 0x00000800 ? '1' : '0'), (int32 & 0x00000400 ? '1' : '0'),        \
    (int32 & 0x00000200 ? '1' : '0'), (int32 & 0x00000100 ? '1' : '0'),        \
    (int32 & 0x00000080 ? '1' : '0'), (int32 & 0x00000040 ? '1' : '0'),        \
    (int32 & 0x00000020 ? '1' : '0'), (int32 & 0x00000010 ? '1' : '0'),        \
    (int32 & 0x00000008 ? '1' : '0'), (int32 & 0x00000004 ? '1' : '0'),        \
    (int32 & 0x00000002 ? '1' : '0'), (int32 & 0x00000001 ? '1' : '0')

/// Printf format to print uint32 as binary
#define UINT32_TO_BINARY_FORMAT INT32_TO_BINARY_FORMAT

/// Convert uint32 to chars
#define UINT32_TO_BINARY INT32_TO_BINARY

/// Printf format to print sizet as binary
#define SIZET_TO_BINARY_FORMAT INT32_TO_BINARY_FORMAT

/// Convert sizet to chars
#define SIZET_TO_BINARY INT32_TO_BINARY

/// Printf format to print ptrdiff as binary
#define PTRDIFF_TO_BINARY_FORMAT INT32_TO_BINARY_FORMAT

/// Convert ptrdiff to chars
#define PTRDIFF_TO_BINARY INT32_TO_BINARY

/// Printf format to print int64 as binary
#define INT64_TO_BINARY_FORMAT                                                 \
  "0b%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'" \
  "%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c'%c%c%c%c"

/// Convert int64 to chars
#define INT64_TO_BINARY(int64)                                                 \
  INT32_TO_BINARY(int64 >> 32), INT32_TO_BINARY(int64)

/// Printf format to print uint64 as binary
#define UINT64_TO_BINARY_FORMAT INT64_TO_BINARY_FORMAT

/// Convert uint64 to chars
#define UINT64_TO_BINARY INT64_TO_BINARY

}  // namespace ztl
