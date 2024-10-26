#pragma once

#include <array>
#include <pybind11/stl.h>
#include <span>

#include "arrayview.h"

#define as_std_span(cls, var_cls, var) \
	[](cls &self) { return std::span<var_cls>(self.var); }

#define as_numpy_array(cls, var_cls, var, size)                                 \
	[](cls &self) {                                                             \
	}

#define getitem_1d(cls, var, size)                                           \
	[](const cls &self, long i) {                                            \
		if (i < 0) i += size;                                                \
		if (i < 0 || i >= size) throw py::index_error("Index out of range"); \
		return &self.var[i];                                                 \
	}

#define setitem_1d(cls, var, size)                                           \
	[](const cls &self, long i, const cls &val) {                            \
		if (i < 0) i += size;                                                \
		if (i < 0 || i >= size) throw py::index_error("Index out of range"); \
		self.var[i] = val;                                                   \
	}

// template <typename T, std::size_t SIZE>
// std::span<T, SIZE> as_std_array(T *a)
// {
//   std::array<T, SIZE> out;
//   std::copy_n(a, SIZE, out.begin());
//   return out;
// }
