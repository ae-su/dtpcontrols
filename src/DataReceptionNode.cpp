/**
 * @file DataReceptionNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <exception>

//#include "logging/logging.hpp"
//#include "NodeNameBuilder.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/AllNodeNames.hpp"

using namespace AllNodeNames;

UHAL_REGISTER_DERIVED_NODE(DataReceptionNode)

//NodeNameBuilder* nnb;

DataReceptionNode::DataReceptionNode(const uhal::Node& node) : DTP(node){}

DataReceptionNode::~DataReceptionNode(){}

void DataReceptionNode::EnableDataReception(bool dispatch) {
  try {    
    getNode(Stitch(csr, ctrl, en)).write(0x1);
  } catch (...) {
    std::cout << "Error enabling Data Reception block." << "\n";
  }
  if(dispatch) {getClient().dispatch();}
}

void DataReceptionNode::ResetInputWordCounter(bool dispatch) {
  try {
    getNode(Stitch(csr, ctrl, rst_inctr)).write(0x1);
  } catch (...) {
    std::cout << "Error resetting input word count." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
}

void DataReceptionNode::ResetOutputWordCounter(bool dispatch) {
  try {
    getNode(Stitch(csr, ctrl, rst_outctr)).write(0x1);
  } catch (...) {
    std::cout << "Error resetting output word counter." << "\n";
  }
}

void DataReceptionNode::ErrorReset(bool dispatch) {
  try {
    getNode(Stitch(csr, ctrl, err_rst)).write(0x1);
  } catch (...) {
    std::cout << "Error writing error reset." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
}

uhal::ValWord<uint32_t> DataReceptionNode::DualPortRamWriteFlag(bool dispatch) {
  uhal::ValWord<uint32_t> lDPRWF;  
  try {
    lDPRWF = getNode(Stitch(stat, dpr_wen)).read();
  } catch (...) {
    std::cout << "Error accessing Dual Port RAM write busy flag." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lDPRWF;
  }

uhal::ValWord<uint32_t> DataReceptionNode::StickyErrorBit(bool dispatch) {
  uhal::ValWord<uint32_t> lSEB;  
  try {
    lSEB =  getNode(Stitch(csr, err)).read();
  } catch (...) {
    std::cout << "Error accessing Sticky Error Bit." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lSEB;
}

uhal::ValWord<uint32_t> DataReceptionNode::BackPressureBit(bool dispatch) {
  uhal::ValWord<uint32_t> lBPB;  
  try {
    lBPB = getNode(Stitch(csr, bp)).read();
  } catch (...) {
    std::cout << "Error accessing Back Pressure Bit." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lBPB;
}

uhal::ValWord<uint32_t> DataReceptionNode::OutOfSync(bool dispatch) {
  uhal::ValWord<uint32_t> lOOS;  
  try {
    lOOS = getNode(Stitch(csr, oos)).read();
  } catch (...) {
    std::cout << "Error accessing Out of Sync Bit." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lOOS;
}

uhal::ValWord<uint32_t> DataReceptionNode::RxWordCount(bool dispatch) {
  uhal::ValWord<uint32_t> lRXWC;  
  try {
    lRXWC = getNode(Stitch(rcvd_wrd_cnt)).read();
  } catch (...) {
    std::cout << "Error accessing Received Word Count register." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lRXWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::SentWordCount(bool dispatch) {
  uhal::ValWord<uint32_t> lSWC;
  try {
    lSWC =  getNode(Stitch(sent_wrd_cnt)).read();
  } catch (...) {
    std::cout << "Error accessing Sent Word Count register." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lSWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::SentPacketCount(bool dispatch) {
  uhal::ValWord<uint32_t> lSPC;
  try {
    lSPC = getNode(Stitch(sent_pkt_cnt)).read();
  } catch (...) {
    std::cout << "Error accessing Sent Packet Count register." << "\n";
  }
  if(dispatch) {getClient().dispatch();}  
  return lSPC;
}
