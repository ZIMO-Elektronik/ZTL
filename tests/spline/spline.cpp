#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/array.hpp>
#include <ztl/spline.hpp>

// Interpolate x, y to sx, sy
TEST(spline, spline) {
  constexpr std::array x{1.0, 64.0, 128.0};
  constexpr std::array y{512.0, 20480.0, 61440.0};
  constexpr std::array<double, 128u> sx{ztl::make_array<double>(
    [](size_t i) { return i + 1; }, std::make_index_sequence<128u>{})};

  constexpr auto splines{ztl::make_hermite_splines(x, y)};
  constexpr auto sy{ztl::eval_hermite_splines(x, y, sx, splines)};

  constexpr auto error{0.0000001};

  EXPECT_NEAR(splines[0u].a3, -0.0135123724732291, error);
  EXPECT_NEAR(splines[0u].a2, 3.39496150555846, error);
  EXPECT_NEAR(splines[0u].a1, 156.700412448444, error);
  EXPECT_NEAR(splines[1u].a3, -0.0130934097525015, error);
  EXPECT_NEAR(splines[1u].a2, 4.21963848806522, error);
  EXPECT_NEAR(splines[1u].a1, 423.573743110072, error);

  EXPECT_NEAR(sy[0u], 512, error);
  EXPECT_NEAR(sy[8u], 1975.96250123700, error);
  EXPECT_NEAR(sy[16u], 3832.97006694772, error);
  EXPECT_NEAR(sy[24u], 6041.51268889441, error);
  EXPECT_NEAR(sy[32u], 8560.08035883930, error);
  EXPECT_NEAR(sy[40u], 11347.1630685446, error);
  EXPECT_NEAR(sy[48u], 14361.2508097727, error);
  EXPECT_NEAR(sy[56u], 17560.8335742856, error);
  EXPECT_NEAR(sy[64u], 20907.7802881884, error);
  EXPECT_NEAR(sy[72u], 24624.4093098144, error);
  EXPECT_NEAR(sy[80u], 28835.9012338080, error);
  EXPECT_NEAR(sy[88u], 33502.0331054097, error);
  EXPECT_NEAR(sy[96u], 38582.5819698598, error);
  EXPECT_NEAR(sy[104u], 44037.3248723984, error);
  EXPECT_NEAR(sy[112u], 49826.0388582661, error);
  EXPECT_NEAR(sy[120u], 55908.5009727030, error);
  EXPECT_NEAR(sy[127u], 61440, error);
}
