/**
 * @file MonProbeNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

//#include "logging/Logging.hpp"

#include "dtpcontrols/MonProbeNode.hpp"

UHAL_REGISTER_DERIVED_NODE(MonProbeNode)

//NodeNameBuilder* nnb;

MonProbeNode::MonProbeNode(const uhal::Node& node) : DTPNode(node){}

MonProbeNode::~MonProbeNode(){}

uhal::ValWord<uint32_t> MonProbeNode::Ready(bool dispatch) {
  uhal::ValWord<uint32_t> lReady;  
  lReady = getNode("ready").read();
  if(dispatch) {getClient().dispatch();}  
  return lReady;
  }

uhal::ValWord<uint32_t> MonProbeNode::Valid(bool dispatch) {
  uhal::ValWord<uint32_t> lValid;  
  lValid =  getNode("valid").read();
  if(dispatch) {getClient().dispatch();}  
  return lValid;
}

uhal::ValWord<uint32_t> MonProbeNode::User(bool dispatch) {
  uhal::ValWord<uint32_t> lUser;  
  lUser = getNode("user").read();
  if(dispatch) {getClient().dispatch();}  
  return lUser;
}

uhal::ValWord<uint32_t> MonProbeNode::Last(bool dispatch) {
  uhal::ValWord<uint32_t> lLast;  
  lLast = getNode("last").read();
  if(dispatch) {getClient().dispatch();}  
  return lLast;
}

uhal::ValWord<uint32_t> MonProbeNode::LastError(bool dispatch) {
  uhal::ValWord<uint32_t> lLastError;  
  lLastError = getNode("last_err").read();
  if(dispatch) {getClient().dispatch();}  
  return lLastError;
}

uhal::ValWord<uint32_t> MonProbeNode::PacketCount(bool dispatch) {
  uhal::ValWord<uint32_t> lPacketCount;
  lPacketCount =  getNode("pkt_ctr").read();
  if(dispatch) {getClient().dispatch();}  
  return lPacketCount;
}

uhal::ValWord<uint32_t> MonProbeNode::AXIError(bool dispatch) {
  uhal::ValWord<uint32_t> lAXIError;
  lAXIError = getNode("axi_err").read();
  if(dispatch) {getClient().dispatch();}  
  return lAXIError;
}
