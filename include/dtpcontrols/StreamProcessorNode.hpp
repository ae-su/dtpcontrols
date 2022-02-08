/**
 * @file StreamProcessorNode.hpp
 *
 * StreamProcessorNode is a class derived from 
 * Its purpose is to control and read status of the stream-
 * processor firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_

#include <cstdint>
#define MASK_ENABLE 1
#define MASK_DISABLE 0

#include "dtpcontrols/DTPNode.hpp"

class StreamProcessorNode : public DTPNode{

  UHAL_DERIVEDNODE(StreamProcessorNode)
  
public:
  explicit StreamProcessorNode(const uhal::Node& );
  virtual ~StreamProcessorNode();

  void DropEmpty(bool);
  void MaskChannels(uint64_t, bool); //TODO check bitshift, endble/diable
  void MaskChannel00To31(uint32_t, bool); //TODO enable/disable
  void MaskChannel32To63(uint32_t, bool); //TODO enable/disable  
  void CapCounters(bool);
  void SetThreshold(uint16_t, bool);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_
