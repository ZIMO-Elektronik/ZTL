# ZTL

[![build](https://github.com/ZIMO-Elektronik/ZTL/actions/workflows/build.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ZTL/actions/workflows/build.yml) [![tests](https://github.com/ZIMO-Elektronik/ZTL/actions/workflows/tests.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ZTL/actions/workflows/tests.yml) [![license](https://img.shields.io/github/license/ZIMO-Elektronik/ZTL)](https://github.com/ZIMO-Elektronik/ZTL/raw/master/LICENSE)

<img src="data/images/logo.png" width="20%" align="right"/>

ZTL is an acronym for ZIMO template library, a conglomerate of utilities specifically for embedded systems. It currently contains the following headers:
- `bits.hpp`  
  Various constexpr functions for bitmasking things

- `compilation_time.hpp`  
  Compiletime stamps from \_\_DATE\_\_ and \_\_TIME\_\_ macros
  
- `counted_latch.hpp`  
  Latches it's value after it hasn't changed for at least I times

- `delayed_latch.hpp`  
  Latches it's value after is hasn't changed for at least I ticks

- `cstring.hpp`  
  Stack allocated container for string

- `directional_latch.hpp`  
  Latches it's value after it hasn't changed direction for at least I times

- `edge_detector.hpp`  
  Detects rising and falling edges

- `enum.hpp`  
  Operator overloads for enum classes enabled by specializing a struct

- `explicit_wrapper.hpp`  
  Value wrapper without any implicit conversions

- `fail.hpp`  
  Delays a static_assert failure till instantiation (and can therefor be used in constexpr context)

- `fixed_string.hpp`  
  Constexpr string class with user-defined literal

- `implicit_wrapper.hpp`  
  Like explicit_wrapper, but allows implicit conversions back to its underlying type

- `inplace_deque.hpp`  
  Stack allocated double-ended queue which push- and pop functions for front and back

- `inplace_list.hpp`
  Stack allocated double-linked list with random insert / erase and push- / pop functions for front and back

- `inplace_vector.hpp`  
  Incomplete implementation of `std::inplace_vector` proposal [P0843r6](https://isocpp.org/files/papers/P0843R8.html)

- `limits.hpp`  
  Minimal representation of signed- or unsigned integral types within given interval

- `math.hpp`  
  Constexpr versions of various algorithms

- `meta.hpp`  
  Minimal set of useful constexpr algorithms

- `moving_average.hpp`  
  Moving average class with specified window size

- `overload.hpp`  
  Creates overload set by inheriting from passed lambdas or functors

- `spline.hpp`  
  Hermite spline implementation

- `static_list.hpp`  
  Doubly linked list which manages externally created nodes

- `string.hpp`  
  Constexpr implementations of atoi, strcmp, strlen

- `system_error.hpp`  
  Basically `std::error_code` without enforcing inheritance of `std::error_category`

- `type_traits.hpp`  
  Many non-standard additions to `<type_traits>`

- `units.hpp`  
  User-defined literals for some physical units (e.g. Hz or ms)
  
- `utility.hpp`  
  Variable templates and operator overloads for `std::integral_constant` and `make_index_sequence_from_to`