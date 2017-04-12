#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <kms++/kms++.h>

namespace py = pybind11;

using namespace kms;
using namespace std;

void init_pykmstest(py::module &m);
void init_pykmsbase(py::module &m);
void init_pyvid(py::module &m);

#if HAS_LIBDRM_OMAP
void init_pykmsomap(py::module &m);
#endif

PYBIND11_PLUGIN(pykms) {
	py::module m("pykms", "kms bindings");

	init_pykmsbase(m);

	m.def("__ob_unpack_helper", [](uint64_t v) {
		// AtomicReq::commit or Crtc::page_flip added a ref, so we can use borrowed = false
		return py::object((PyObject*)v, false);
	});

	init_pykmstest(m);

	init_pyvid(m);

#if HAS_LIBDRM_OMAP
	init_pykmsomap(m);
#endif
	return m.ptr();
}