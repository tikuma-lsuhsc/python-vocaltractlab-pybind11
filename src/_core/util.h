#include <span>
#include <array>
#include <pybind11/stl.h>

#define as_std_span(cls, var) [](cls &self) { return std::span(self.var); }

template <typename T, std::size_t SIZE>
std::span<T, SIZE> as_std_array(T *a)
{
  std::array<T, SIZE> out;
  std::copy_n(a, SIZE, out.begin());
  return out;
}
