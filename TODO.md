# TODO
- Rename moving_average to... something?
  - And change moving_average implementation to actual "[SMA](https://tttapa.github.io/Pages/Mathematics/Systems-and-Control-Theory/Digital-filters/Simple%20Moving%20Average/C++Implementation.html)"
- Rename spline functions to pchip and ppval?
- Get rid of pointless "typename" stuff
- circular_array isn't constinit friendly... (guess because the elements are not zero-initialized?)
- implicit/explicit_wrapper move ctor/assign should use std::moveable
- index_sequence2mask -> consteval (currently cant be because of bug)
  https://gcc.gnu.org/bugzilla/show_bug.cgi?id=103443
- circular_array operator<=>