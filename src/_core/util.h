#include <array>
#include <pybind11/stl.h>
#include <span>

#define as_std_span(cls, var) [](cls &self) { return std::span(self.var); }
#define as_std_span_sz(cls, var, size) \
	[](cls &self) { return std::span(self.var, size); }
#define as_std_vector_ref(cls, var_cls, var, size)                                \
	[](cls &self) {                                                           \
		return std::vector<std::reference_wrapper<var_cls>>(self.var,         \
		                                                    self.var + size); \
	}
#define as_py_array(cls, var, size)                                            \
	[](cls &self) {                                                            \
		return py::array(py::dtype("object"), size, self.var, py::cast(self)); \
	}

#define getitem_1d(cls, var, size)                                           \
	[](const cls &self, long i) {                                            \
		if (i < 0) i += size;                                                \
		if (i < 0 || i >= size) throw py::index_error("Index out of range"); \
		return &self.var[i];                                                 \
	}

// template <typename T, std::size_t SIZE>
// std::span<T, SIZE> as_std_array(T *a)
// {
//   std::array<T, SIZE> out;
//   std::copy_n(a, SIZE, out.begin());
//   return out;
// }
