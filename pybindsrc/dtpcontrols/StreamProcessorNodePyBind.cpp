/**
 * @file StreamProcessorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_stream_processor_node(py::module& m){ 

    m.doc() = "c++ implementation of dtpcontrols StreamProcessor python modules"; // optional module docstring

    py::class_<dtpcontrols::StreamProcessorNode, uhal::Node>(m, "StreamProcessorNode")
      .def(py::init<const uhal::Node &>())
      .def("SetThreshold", &dtpcontrols::StreamProcessorNode::SetThreshold,
	   py::arg("threshold"), py::arg("dispatch") = true)
      .def("SetMaskChannel00To31",
	   &dtpcontrols::StreamProcessorNode::SetMaskChannel00To31,
	   py::arg("mask00to31"), py::arg("dispatch") = true,
	   py::arg("mask_en_dsbl") = true)
      .def("DropEmpty", &dtpcontrols::StreamProcessorNode::DropEmpty, py::arg("dispatch")=true)
      .def("SetMaskChannel32To63",
	   &dtpcontrols::StreamProcessorNode::SetMaskChannel32To63,
	   py::arg("mask32to63"), py::arg("dispatch")=true,
	   py::arg("mask_en_dsbl")=true);

}

} // namespace python
} // namespace timing
} // namespace dunedaq
