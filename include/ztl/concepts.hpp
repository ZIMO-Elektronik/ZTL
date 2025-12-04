// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Concepts
///
/// \file   ztl/concepts.hpp
/// \author Vincent Hamp
/// \date   21/02/2025

#pragma once

#include <concepts>
#include <ranges>
#include "meta.hpp"
#include "utility.hpp"

namespace ztl {

template<typename T>
concept chrono_duration = is_chrono_duration_v<T>;

template<class R, class T>
concept container_compatible_range =
  std::ranges::input_range<R> &&
  std::convertible_to<std::ranges::range_reference_t<R>, T>;

} // namespace ztl
