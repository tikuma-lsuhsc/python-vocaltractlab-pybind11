#pragma once

#include <span>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <fmt/core.h>

namespace py = pybind11;
using namespace py::literals;

template <typename T, std::size_t Extent = std::dynamic_extent>
void initArrayView(py::module &m, const std::string type_name) {

	py::class_<std::span<T, Extent>>(m, (type_name + "ArrayView").c_str())
	        /// Bare bones interface
	        .def("__getitem__",
	             [](const std::span<T> &s, size_t i) -> T & {
		             if (i >= s.size()) { throw py::index_error(); }
		             return s[i];
	             })
	        .def("__setitem__",
	             [](std::span<T> &s, size_t i, T v) {
		             if (i >= s.size()) { throw py::index_error(); }
		             s[i] = v;
	             })
	        .def("__len__", &std::span<T>::size)
	        /// Optional sequence protocol operations
	        .def(
	                "__iter__",
	                [](const std::span<T> &s) {
		                return py::make_iterator(s.begin(), s.end());
	                },
	                py::keep_alive<0, 1>()
	                /* Essential: keep object alive while iterator exists */)
	        /// Slicing protocol (optional)
	        .def("__getitem__",
	             [](const std::span<T> &s, const py::slice &slice) -> std::span<T> {
		             size_t start = 0, stop = 0, step = 0, slicelength = 0;
		             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength)) {
			             throw py::index_error();
		             }

		             return s.subspan(start, slicelength);
	             })
	        .def("__setitem__",
	             [](std::span<T> &s, const py::slice &slice,
	                const std::vector<T> &value) {
		             size_t start = 0, stop = 0, step = 0, slicelength = 0;
		             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength)) {
			             throw py::index_error();
		             }

		             if (slicelength != value.size()) {
			             throw std::runtime_error("Left and right hand size of slice "
			                                      "assignment have different sizes!");
		             }

		             for (size_t i = 0; i < slicelength; ++i) {
			             s[start] = value[i];
			             start += step;
		             }
	             })
	        .def("__setitem__",
	             [](std::span<T> &s, const py::slice &slice, const T &value) {
		             size_t start = 0, stop = 0, step = 0, slicelength = 0;
		             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength)) {
			             throw py::index_error();
		             }

		             for (size_t i = 0; i < slicelength; ++i) {
			             s[start] = value;
			             start += step;
		             }
	             })
	        /// Comparisons
	        // .def(py::self == py::self)
	        // .def(py::self != py::self)
	        // Could also define py::self + py::self for concatenation, etc.
	        ;
}


#define PYBIND11_MAKE_ARRAY_VIEW(m, type) initArrayView<type>(m, "#type")

template <typename T, std::size_t Extent_Rows = std::dynamic_extent,
          std::size_t Extent_Cols = std::dynamic_extent>
void init2DArrayView(py::module &m, const std::string type_name) {

	py::class_<std::span<std::span<T, Extent_Cols>, Extent_Rows>>(
	        m, (type_name + "2DArrayView").c_str())
	        /// Bare bones interface
	        .def("__getitem__",
	             [](const std::span<std::span<T>> &s, size_t i, size_t j) -> T & {
		             if (i >= s.size() || j > s[0].size()) { throw py::index_error(); }
		             return s[i][j];
	             })
	        .def("__setitem__",
	             [](std::span<std::span<T>> &s, size_t i, size_t j, T v) {
		             if (i >= s.size() || j > s[0].size()) { throw py::index_error(); }
		             s[i][j] = v;
	             })
	        .def("__len__", &std::span<std::span<T>>::size)
	        /// Optional sequence protocol operations
	        .def(
	                "__iter__",
	                [](const std::span<std::span<T>> &s) {
		                return py::make_iterator(s.begin(), s.end());
	                },
	                py::keep_alive<0, 1>()
	                /* Essential: keep object alive while iterator exists */)
	        /// Slicing protocol (optional)
	        .def("__getitem__",
	             [](const std::span<std::span<T>> &s, const py::slice &row_slice,
	                const py::slice &col_slice) -> std::span<std::span<T>> {
		             size_t row_start = 0, row_stop = 0, row_step = 0,
		                    row_slicelength = 0;
		             size_t col_start = 0, col_stop = 0, col_step = 0,
		                    col_slicelength = 0;
		             if (!row_slice.compute(s.size(), &row_start, &row_stop, &row_step,
		                                    &row_slicelength) ||
		                 !col_slice.compute(s.size(), &col_start, &col_stop, &col_step,
		                                    &col_slicelength)) {
			             throw py::index_error();
		             }

		             return s.subspan(start, slicelength);
	             })
	        .def("__setitem__",
	             [](std::span<std::span<T>> &s, const py::slice &row_slice,
	                const py::slice &col_slice, const std::vector<T> &value) {
		             size_t start = 0, stop = 0, step = 0, slicelength = 0;
		             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength)) {
			             throw py::error_already_set();
		             }

		             if (slicelength != value.size()) {
			             throw std::runtime_error("Left and right hand size of slice "
			                                      "assignment have different sizes!");
		             }

		             for (size_t i = 0; i < slicelength; ++i) {
			             s[start] = value[i];
			             start += step;
		             }
	             })
	        .def("__setitem__",
	             [](std::span<std::span<T>> &s, const py::slice &slice,
	                const T &value) {
		             size_t start = 0, stop = 0, step = 0, slicelength = 0;
		             if (!slice.compute(s.size(), &start, &stop, &step, &slicelength)) {
			             throw py::error_already_set();
		             }

		             for (size_t i = 0; i < slicelength; ++i) {
			             s[start] = value;
			             start += step;
		             }
	             })
	        /// Comparisons
	        // .def(py::self == py::self)
	        // .def(py::self != py::self)
	        // Could also define py::self + py::self for concatenation, etc.
	        ;
}


#define PYBIND11_MAKE_2D_ARRAY_VIEW(m, type) initArrayView<type>(m, "#type")
