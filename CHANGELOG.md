# Changelog

##
- Add inplace_vector
- Rename circular_array to inplace_deque and change behavior of
  - Modifiers may cause UB
  - Element access if empty causes UB
  - Remove ssize method
  - Add resize method
- Remove array header

## 0.16.2
- Remove is_enum_class
- Remove msb_position
- Remove u_type

## 0.16.1
- Remove delegate

## 0.16.0
- Add fixed_string, strcpy and strncpy
- Remove cstring

## 0.15.0
- Added make_linspace

## 0.14.0
- Added tuple_index type trait
- [Semantic versioning](https://semver.org)
- Removed is_within_word_size_bit and is_within_word_size_bit_half

## 0.13
- integer_sequence2mask became index_sequence2mask
- Removed _c aliases for std::integral_constant
- make_mask no longer accepts signed integers
- Removed masked_index_sequence_for and masked_inverted_index_sequence_for

## 0.12
- Added strstr function
- Removed dead weight from meta and type_traits
- Catch division through zero in lerp in case x1 and x2 are equal

## 0.11
- Removed CMake exports

## 0.10
- Added EdgeDetector

## 0.9
- Added copy and move assignment from value_type to implicit wrapper
- Bugfix assignment of moving_average
- Renamed macro MAKE_ENUM_CLASS_FLAGS to ZTL_MAKE_ENUM_CLASS_FLAGS

## 0.8
- Split ZTL and moved device specific headers to STM32 library

## 0.7
- Splines can only take floating point values
- Added *_digit functions

## 0.6
- Bugfix missing return for Exti callback method

## 0.5
- Added DAC peripheral

## 0.4
- Exti uses single callback method with template parameter

## 0.3
- Added directional_latch
- reverse_iterator of circular_array was all wrong

## 0.2
- Clear all error flags before unlocking flash

## 0.1
- Bugfix swtim