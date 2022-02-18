/**
 * @file DataReceptionNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataReceptionNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(DataReceptionNode)

DataReceptionNode::DataReceptionNode(const uhal::Node& node) : uhal::Node(node) {}
  
DataReceptionNode::~DataReceptionNode(){}
  
void DataReceptionNode::EnableDataReception(bool dispatch) {
  getNode("csr.ctrl.en").write(0x1);
  if(dispatch) {getClient().dispatch();}
}

void DataReceptionNode::ResetInputWordCounter(bool dispatch) {
  getNode("csr.ctrl.rst_inctr").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

void DataReceptionNode::ResetOutputWordCounter(bool dispatch) {
  getNode("csr.ctrl.rst_outctr").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

void DataReceptionNode::ErrorReset(bool dispatch) {
  getNode("csr.ctrl.err_rst").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

uhal::ValWord<uint32_t> DataReceptionNode::DualPortRamWriteFlag(bool dispatch) {
  uhal::ValWord<uint32_t> lDPRWF;  
  lDPRWF = getNode("stat.dpr_wen").read();
  if(dispatch) {getClient().dispatch();}  
  return lDPRWF;
  }

uhal::ValWord<uint32_t> DataReceptionNode::StickyErrorBit(bool dispatch) {
  uhal::ValWord<uint32_t> lSEB;  
  lSEB =  getNode("stat.err").read();
  if(dispatch) {getClient().dispatch();}  
  return lSEB;
}

uhal::ValWord<uint32_t> DataReceptionNode::BackPressureBit(bool dispatch) {
  uhal::ValWord<uint32_t> lBPB;  
  lBPB = getNode("stat.bp").read();
  if(dispatch) {getClient().dispatch();}  
  return lBPB;
}

uhal::ValWord<uint32_t> DataReceptionNode::OutOfSync(bool dispatch) {
  uhal::ValWord<uint32_t> lOOS;  
  lOOS = getNode("stat.oos").read();
  if(dispatch) {getClient().dispatch();}  
  return lOOS;
}

uhal::ValWord<uint32_t> DataReceptionNode::RxWordCount(bool dispatch) {
  uhal::ValWord<uint32_t> lRXWC;  
  lRXWC = getNode("rcvd_wrd_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lRXWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::SentWordCount(bool dispatch) {
  uhal::ValWord<uint32_t> lSWC;
  lSWC =  getNode("sent_wrd_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lSWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::SentPacketCount(bool dispatch) {
  uhal::ValWord<uint32_t> lSPC;
  lSPC = getNode("sent_pkt_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lSPC;
}

} // namespace dtpcontrols
} // namespace dunedaq
