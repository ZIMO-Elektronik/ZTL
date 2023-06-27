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

  EXPECT_NEAR(splines[0uz].a3, -0.0135123724732291, error);
  EXPECT_NEAR(splines[0uz].a2, 3.39496150555846, error);
  EXPECT_NEAR(splines[0uz].a1, 156.700412448444, error);
  EXPECT_NEAR(splines[1uz].a3, -0.0130934097525015, error);
  EXPECT_NEAR(splines[1uz].a2, 4.21963848806522, error);
  EXPECT_NEAR(splines[1uz].a1, 423.573743110072, error);

  EXPECT_NEAR(sy[0uz], 512, error);
  EXPECT_NEAR(sy[8uz], 1975.96250123700, error);
  EXPECT_NEAR(sy[16uz], 3832.97006694772, error);
  EXPECT_NEAR(sy[24uz], 6041.51268889441, error);
  EXPECT_NEAR(sy[32uz], 8560.08035883930, error);
  EXPECT_NEAR(sy[40uz], 11347.1630685446, error);
  EXPECT_NEAR(sy[48uz], 14361.2508097727, error);
  EXPECT_NEAR(sy[56uz], 17560.8335742856, error);
  EXPECT_NEAR(sy[64uz], 20907.7802881884, error);
  EXPECT_NEAR(sy[72uz], 24624.4093098144, error);
  EXPECT_NEAR(sy[80uz], 28835.9012338080, error);
  EXPECT_NEAR(sy[88uz], 33502.0331054097, error);
  EXPECT_NEAR(sy[96uz], 38582.5819698598, error);
  EXPECT_NEAR(sy[104uz], 44037.3248723984, error);
  EXPECT_NEAR(sy[112uz], 49826.0388582661, error);
  EXPECT_NEAR(sy[120uz], 55908.5009727030, error);
  EXPECT_NEAR(sy[127uz], 61440, error);
}
