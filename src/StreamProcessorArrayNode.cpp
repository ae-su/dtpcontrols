/**
 * @file StreamProcessorArrayNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

//#include "logging/Logging.hpp"

#include "dtpcontrols/StreamProcessorArrayNode.hpp"
#include "dtpcontrols/MonProbeNode.hpp"
#include <cstdint>

UHAL_REGISTER_DERIVED_NODE(StreamProcessorArrayNode)

StreamProcessorArrayNode::StreamProcessorArrayNode(const uhal::Node& node) : DTPNode(node){}

StreamProcessorArrayNode::~StreamProcessorArrayNode(){}

void StreamProcessorArrayNode::CapCounters(const bool dispatch) {
  getNode("csr.ctrl.cap_ctrs").write(0x1);
  if(dispatch) {getClient().dispatch();}
}

void StreamProcessorArrayNode::StreamSelect(const uint32_t pipe, const bool dispatch) {
  getNode("csr.ctrl.stream_sel").write(pipe);
  if(dispatch) {getClient().dispatch();}  
}

const uhal::Node &StreamProcessorArrayNode::GetStreamProcessorNode(void) {
  return getNode<StreamProcessorNode>("stream_proc");
}

