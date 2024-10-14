#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace vocaltractlab
{

    extern void initAnatomyParams(py::module &);
    extern void initSpeaker(py::module &);
    extern void initGlottis(py::module &);
    extern void initGeometricGlottis(py::module &);
    extern void initTriangularGlottis(py::module &m);
    extern void initTwoMassModel(py::module &m);
    extern void initGlottisFactory(py::module &m);
    extern void initGeometry(py::module &m);

    PYBIND11_MODULE(_core, m)
    {
        initAnatomyParams(m);
        initSpeaker(m);
        initGlottis(m);
        initGeometricGlottis(m);
        initTriangularGlottis(m);
        initTwoMassModel(m);
        initGlottisFactory(m);
        initGeometry(m);
    }
}