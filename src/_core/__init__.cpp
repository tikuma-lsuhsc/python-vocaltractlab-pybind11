#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace vocaltractlab
{

    extern void initAnatomyParams(py::module &);
    extern void initSpeaker(py::module &);

    PYBIND11_MODULE(_core, m)
    {
        initAnatomyParams(m);
        initSpeaker(m);
    }
}