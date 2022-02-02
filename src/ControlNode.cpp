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
#include "dtpcontrols/AllNodeNames.hpp"

using namespace AllNodeNames;

UHAL_REGISTER_DERIVED_NODE(ControlNode)

//NodeNameBuilder* nnb;

ControlNode::ControlNode(const uhal::Node& node) : DTP(node){}

ControlNode::~ControlNode(){}

void ControlNode::Nuke(bool dispatch) {
  try {    
    getNode(Stitch(csr, ctrl, nuke)).write(0x1);
  } catch (...) {
    std::cout << "Error enabling Data Reception block." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void ControlNode::SoftReset(bool dispatch) {
  try {
    getNode(Stitch(csr, ctrl, soft_rst)).write(0x1);
  } catch (...) {
    std::cout << "Error resetting input word count." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void ControlNode::MasterReset(bool dispatch) {
  try {
    getNode(Stitch(csr, ctrl, mst_rst)).write(0x1);
  } catch (...) {
    std::cout << "Error resetting input word count." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
  
}
