# Changelog

## 0.19.0
- Rename `EdgeDetector` to `edge_detector`
- Add missing `<cassert>`
- Update to CMakeModules 0.3.0

## 0.18.0
- Update to CMakeModules 0.2.0

## 0.17.0
- Add inplace_vector
- Rename `circular_array` to `inplace_deque` and change behavior of
  - Modifiers may cause UB
  - Element access if empty causes UB
  - Remove ssize method
  - Add resize method
- Remove array header

## 0.16.2
- Remove `is_enum_class`
- Remove `msb_position`
- Remove `u_type`

## 0.16.1
- Remove `delegate`

## 0.16.0
- Add `fixed_string`, `strcpy` and `strncpy`
- Remove `cstring`

## 0.15.0
- Add `make_linspace`

## 0.14.0
- Add `tuple_index` type trait
- [Semantic versioning](https://semver.org)
- Remove `is_within_word_size_bit` and `is_within_word_size_bit_half`

## 0.13
- Rename `integer_sequence2mask` to `index_sequence2mask`
- Remove _c aliases for `std::integral_constant`
- `make_mask` no longer accepts signed integers
- Remove `masked_index_sequence_for` and `masked_inverted_index_sequence_for`

## 0.12
- Add `strstr`
- Remove dead weight from meta and type_traits
- Catch division through zero in lerp in case x1 and x2 are equal

## 0.11
- Remove CMake exports

## 0.10
- Add `edge_detector`

## 0.9
- Add copy and move assignment from value_type to `implicit_wrapper`
- Bugfix assignment of `moving_average`
- Rename macro `MAKE_ENUM_CLASS_FLAGS` to `ZTL_MAKE_ENUM_CLASS_FLAGS`

## 0.8
- Split ZTL and moved device specific headers to STM32 library

## 0.7
- Splines can only take floating point values
- Add `*_digit` functions

## 0.6
- Bugfix missing return for Exti callback method

## 0.5
- Add DAC peripheral

## 0.4
- Exti uses single callback method with template parameter

## 0.3
- Add `directional_latch`
- `reverse_iterator` of `circular_array` was all wrong

## 0.2
- Clear all error flags before unlocking flash

## 0.1
- Bugfix swtim