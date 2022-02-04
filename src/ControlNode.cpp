/**
 * @file ControlNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <exception>

//#include "logging/logging.hpp"

#include "dtpcontrols/ControlNode.hpp"


UHAL_REGISTER_DERIVED_NODE(ControlNode)

//NodeNameBuilder* nnb;

ControlNode::ControlNode(const uhal::Node& node) : DTPNode(node){}

ControlNode::~ControlNode(){}

void ControlNode::Nuke(bool dispatch) {
  try {    
    getNode("csr.ctrl.nuke").write(0x1);
  } catch (...) {
    std::cout << "Error nuking control block." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void ControlNode::SoftReset(bool dispatch) {
  try {
    getNode("csr.ctrl.soft_rst").write(0x1);
  } catch (...) {
    std::cout << "Error soft resetting control block." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void ControlNode::MasterReset(bool dispatch) {
  try {
    getNode("csr.ctrl.mst_rst").write(0x1);
  } catch (...) {
    std::cout << "Error issuing master." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
  
}
