// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Spline functions
///
/// https://shiftedbits.org/spline-interpolation/
///
/// \file   ztl/spline.hpp
/// \author Vincent Hamp
/// \date   26/05/2017

#pragma once

#include <array>
#include "math.hpp"

namespace ztl {

/// Equals MATLABs own "ppform" coefficients
/// s(x) = a0 + a1*(x-xl) + a2*(x-xl)^2 + a3*(x-xl)^3
///      = a0 + (x-xl)*[a1 + (x-xl)*[a2 + (x-xl)*a3]]
///
/// \tparam std::floating_point Type
template<std::floating_point T>
struct spline {
  T a3{}, a2{}, a1{};
};

/// Make splines
///
/// \tparam std::floating_point Type
/// \tparam I                   Size of x and y
/// \param  x                   Input x
/// \param  y                   Input y
/// \return Array of splines
template<std::floating_point T, size_t I>
requires(I >= 3u)
constexpr std::array<spline<T>, I - 1u> make_hermite_splines(
  std::array<T, I> const& x, std::array<T, I> const& y) {
  std::array<spline<T>, I - 1u> splines{};
  std::array<T, I - 1u> h{};
  std::array<T, I> del{};
  std::array<T, I> s{};

  for (auto i{0u}; i < I - 1u; ++i) {
    h[i] = x[i + 1u] - x[i];
    del[i] = (y[i + 1u] - y[i]) / h[i];
  }

  // Find slopes at interior points
  for (auto i{0u}; i < I - 1u; ++i) {
    if ((sign(del[i + 1u]) * sign(del[i])) <= 0) continue;
    auto const hs{h[i + 1u] + h[i]};
    auto const dmax{std::max(std::abs(del[i]), std::abs(del[i + 1u]))};
    auto const dmin{std::min(std::abs(del[i]), std::abs(del[i + 1u]))};
    s[i + 1u] = dmin / (((h[i] + hs) / (3u * hs)) * (del[i] / dmax) +
                        ((hs + h[i + 1u]) / (3u * hs)) * (del[i + 1u] / dmax));
  }

  // Find slopes at end points
  s[0u] = ((2u * h[0u] + h[1u]) * del[0u] - h[0u] * del[1u]) / (h[0u] + h[1u]);
  if (sign(s[0u]) != sign(del[0u])) s[0u] = 0;
  else if ((sign(del[0u]) != sign(del[1u])) &&
           (std::abs(s[0u]) > std::abs(3u * del[0u])))
    s[0u] = 3u * del[0u];

  s[I - 1u] =
    ((2u * h[I - 2u] + h[I - 3u]) * del[I - 2u] - h[I - 2u] * del[I - 3u]) /
    (h[I - 2u] + h[I - 3u]);
  if (sign(s[I - 1u]) != sign(del[I - 2u])) s[I - 1u] = 0;
  else if ((sign(del[I - 2u]) != sign(del[I - 3u])) &&
           (std::abs(s[I - 1u]) > std::abs(3u * del[I - 2u])))
    s[I - 1u] = 3u * del[I - 2u];

  for (auto i{0u}; i < I - 1u; ++i) {
    auto const dzzdx{(del[i] - s[i]) / h[i]};
    auto const dzdxdx{(s[i + 1u] - del[i]) / h[i]};
    splines[i].a1 = s[i];
    splines[i].a2 = 2u * dzzdx - dzdxdx;
    splines[i].a3 = (dzdxdx - dzzdx) / h[i];
  }

  return splines;
}

/// Evaluate splines
///
/// \tparam std::floating_point Type
/// \tparam I                   Size of x and y
/// \tparam J                   Size of interpolated x and y
/// \param  x                   Input x
/// \param  y                   Input y
/// \param  sx                  Interpolated x
/// \param  splines             Splines
/// \return Interpolated y
template<std::floating_point T, size_t I, size_t J>
requires(I >= 3u)
constexpr std::array<T, J> eval_hermite_splines(
  std::array<T, I> const& x,
  std::array<T, I> const& y,
  std::array<T, J> const& sx,
  std::array<spline<T>, I - 1u> const& splines) {
  std::array<T, J> sy{};
  size_t count{};

  for (auto i{0u}; i < I - 1u; ++i) {
    if (i + 1u >= I) break;
    while (sx[count] <= x[i + 1u]) {
      auto const del{sx[count] - x[i]};
      sy[count++] = y[i] + splines[i].a1 * del + splines[i].a2 * del * del +
                    splines[i].a3 * del * del * del;
      if (count >= J) break;
    }
  }

  return sy;
}

}  // namespace ztl
