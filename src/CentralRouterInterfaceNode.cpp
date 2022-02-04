/**
 * @file CentralRouterInterfaceNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/CentralRouterInterfaceNode.hpp"

UHAL_REGISTER_DERIVED_NODE(CentralRouterInterfaceNode)

CentralRouterInterfaceNode::CentralRouterInterfaceNode(const uhal::Node &node)
    : DTPNode(node) {}

CentralRouterInterfaceNode::~CentralRouterInterfaceNode() {}

void CentralRouterInterfaceNode::EnableRouterInterface(bool dispatch) {
  try {    
    getNode("csr.ctrl.en").write(0x1);
  } catch (...) {
    std::cout << "Error enabling central router interface." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void CentralRouterInterfaceNode::DropEmpty(bool dispatch) {
  try {    
    getNode("csr.ctrl.drop_empty").write(0x1);
  } catch (...) {
    std::cout << "Error setting drop empty." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

