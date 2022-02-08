/**
 * @file StreamProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

//#include "logging/Logging.hpp"

#include "dtpcontrols/StreamProcessorNode.hpp"
#include "dtpcontrols/MonProbeNode.hpp"
#include <cstdint>

UHAL_REGISTER_DERIVED_NODE(StreamProcessorNode)

//NodeNameBuilder* nnb;

StreamProcessorNode::StreamProcessorNode(const uhal::Node& node) : DTPNode(node){}

StreamProcessorNode::~StreamProcessorNode(){}

void StreamProcessorNode::DropEmpty(bool dispatch) {
  getNode("csr.ctrl.drop_empty").write(0x1);
  if(dispatch) {getClient().dispatch();}
}

void StreamProcessorNode::CapCounters(bool dispatch) {
  getNode("csr.ctrl.cap_ctrs").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

void StreamProcessorNode::SetThreshold(uint16_t threshold, bool dispatch) {
  if (threshold > 0 && threshold < 0x7fff){ // from hfButler; set in firmware JS thinks
  getNode("csr.hitfinder.threshold").write(threshold);
  if(dispatch) {getClient().dispatch();}
  }
  else {} //placeholder for ERS error
}

void StreamProcessorNode::MaskChannel00To31(uint32_t mask00to31, bool dispatch) {
  getNode("csr.mask.ch-00-31").write(mask00to31);
  if(dispatch) {getClient().dispatch();}  
}

void StreamProcessorNode::MaskChannel32To63(uint32_t mask32to63, bool dispatch) {
  getNode("csr.mask.ch-32-63").write(mask32to63);
  if(dispatch) {getClient().dispatch();}
}

void StreamProcessorNode::MaskChannels(uint64_t maskAll, bool dispatch) {
  MaskChannel00To31(maskAll, dispatch);
  MaskChannel32To63(maskAll<<32, dispatch);
}
