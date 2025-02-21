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

#include "math.hpp"

namespace ztl {

/// Equals MATLABs own "ppform" coefficients
/// s(x) = a0 + a1*(x-xl) + a2*(x-xl)^2 + a3*(x-xl)^3
///      = a0 + (x-xl)*[a1 + (x-xl)*[a2 + (x-xl)*a3]]
///
/// \tparam std::floating_point Type
template<std::floating_point T>
struct spline {
  T a3{};
  T a2{};
  T a1{};
};

/// Make splines
///
/// \tparam std::floating_point Type
/// \tparam I                   Size of x and y
/// \param  x                   Input x
/// \param  y                   Input y
/// \return Array of splines
template<std::floating_point T, size_t I>
requires(I >= 3uz)
constexpr std::array<spline<T>, I - 1uz>
make_hermite_splines(std::array<T, I> const& x, std::array<T, I> const& y) {
  std::array<spline<T>, I - 1uz> splines{};
  std::array<T, I - 1uz> h{};
  std::array<T, I> del{};
  std::array<T, I> s{};

  for (auto i{0uz}; i < I - 1u; ++i) {
    h[i] = x[i + 1uz] - x[i];
    del[i] = (y[i + 1uz] - y[i]) / h[i];
  }

  // Find slopes at interior points
  for (auto i{0uz}; i < I - 1u; ++i) {
    if ((sign(del[i + 1uz]) * sign(del[i])) <= 0) continue;
    auto const hs{h[i + 1uz] + h[i]};
    auto const dmax{std::max(std::abs(del[i]), std::abs(del[i + 1uz]))};
    auto const dmin{std::min(std::abs(del[i]), std::abs(del[i + 1uz]))};
    s[i + 1uz] =
      dmin / (((h[i] + hs) / (3u * hs)) * (del[i] / dmax) +
              ((hs + h[i + 1uz]) / (3u * hs)) * (del[i + 1uz] / dmax));
  }

  // Find slopes at end points
  s[0uz] =
    ((2u * h[0uz] + h[1uz]) * del[0uz] - h[0uz] * del[1uz]) / (h[0uz] + h[1uz]);
  if (sign(s[0uz]) != sign(del[0uz])) s[0uz] = 0;
  else if ((sign(del[0uz]) != sign(del[1uz])) &&
           (std::abs(s[0uz]) > std::abs(3u * del[0uz])))
    s[0uz] = 3u * del[0uz];

  s[I - 1uz] = ((2u * h[I - 2uz] + h[I - 3uz]) * del[I - 2uz] -
                h[I - 2uz] * del[I - 3uz]) /
               (h[I - 2uz] + h[I - 3uz]);
  if (sign(s[I - 1uz]) != sign(del[I - 2uz])) s[I - 1uz] = 0;
  else if ((sign(del[I - 2uz]) != sign(del[I - 3uz])) &&
           (std::abs(s[I - 1uz]) > std::abs(3u * del[I - 2uz])))
    s[I - 1uz] = 3u * del[I - 2uz];

  for (auto i{0uz}; i < I - 1u; ++i) {
    auto const dzzdx{(del[i] - s[i]) / h[i]};
    auto const dzdxdx{(s[i + 1uz] - del[i]) / h[i]};
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
requires(I >= 3uz)
constexpr std::array<T, J>
eval_hermite_splines(std::array<T, I> const& x,
                     std::array<T, I> const& y,
                     std::array<T, J> const& sx,
                     std::array<spline<T>, I - 1u> const& splines) {
  std::array<T, J> sy{};
  size_t count{};

  for (auto i{0uz}; i < I - 1u; ++i) {
    if (i + 1u >= I) break;
    while (sx[count] <= x[i + 1uz]) {
      auto const del{sx[count] - x[i]};
      sy[count++] = y[i] + splines[i].a1 * del + splines[i].a2 * del * del +
                    splines[i].a3 * del * del * del;
      if (count >= J) break;
    }
  }

  return sy;
}

} // namespace ztl
