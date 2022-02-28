/**
 * @file DataReceptionNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataReceptionNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_data_reception_node(py::module& m){ 

    m.doc() = "c++ implementation of dtpcontrols DataReception python modules"; // optional module docstring

     py::class_<dtpcontrols::DataReceptionNode, uhal::Node>(m, "DataReceptionNode")
       .def(py::init<const uhal::Node&>())
       .def("EnableDataReception", &dtpcontrols::DataReceptionNode::EnableDataReception)
       .def("EnableDataReception", &dtpcontrols::DataReceptionNode::ResetInputWordCounter)
       .def("EnableDataReception", &dtpcontrols::DataReceptionNode::ResetOutputWordCounter);
}

} // namespace python
} // namespace timing
} // namespace dunedaq
