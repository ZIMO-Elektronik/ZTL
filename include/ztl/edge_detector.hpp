// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Edge detector
///
/// \file   ztl/edge_detector.hpp
/// \author Samuel Sillaber
/// \date   28/07/2021

#pragma once

namespace ztl {

/// Detect rising and falling edges
struct EdgeDetector {
  enum Polarity { None, Rising, Falling };

  constexpr EdgeDetector() = default;
  explicit constexpr EdgeDetector(bool value) : value_{value} {}

  [[nodiscard]] constexpr Polarity operator()(bool value) {
    if (value == value_) return None;
    return (value_ = value) ? Rising : Falling;
  }

private:
  bool value_{false};
};

}  // namespace ztl