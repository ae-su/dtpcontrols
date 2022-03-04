/**
 * @file CentralRouterInterfaceNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/CentralRouterInterfaceNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_central_router_interface_node(py::module& m){ 

    m.doc() = "c++ implementation of dtpcontrols CentralRouterInterface python modules"; // optional module docstring

     py::class_<dtpcontrols::CentralRouterInterfaceNode, uhal::Node>(m, "CentralRouterInterfaceNode")
       .def(py::init<const uhal::Node&>())
       .def("enable_central_router_interface", &dtpcontrols::CentralRouterInterfaceNode::enable_central_router_interface,
	    py::arg("dispatch") = true)
       .def("drop_empty", &dtpcontrols::CentralRouterInterfaceNode::drop_empty, py::arg("dispatch") = true);
}

} // namespace python
} // namespace timing
} // namespace dunedaq
