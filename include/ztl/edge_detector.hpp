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
  explicit constexpr EdgeDetector(bool value) : _value{value} {}

  [[nodiscard]] constexpr Polarity operator()(bool value) {
    if (value == _value) return None;
    return (_value = value) ? Rising : Falling;
  }

private:
  bool _value{false};
};

}  // namespace ztl