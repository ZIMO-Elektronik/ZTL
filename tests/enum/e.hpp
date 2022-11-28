#pragma once

#include <ztl/enum.hpp>

enum class E { A = 1 << 0, B = 1 << 1, C = 1 << 2, D = 1 << 3, E = -42 };

ZTL_MAKE_ENUM_CLASS_FLAGS(E)