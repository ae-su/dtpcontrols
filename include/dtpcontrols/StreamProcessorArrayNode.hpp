/**
 * @file StreamProcessorArrayNode.hpp
 *
 * StreamProcessorArrayNode is a class derived from 
 * Its purpose is to control and read status of the stream-
 * processor firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORARRAYNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORARRAYNODE_HPP_

#include "dtpcontrols/DTPNode.hpp"
#include "dtpcontrols/StreamProcessorNode.hpp"
#include <cstdint>
#include <uhal/Node.hpp>

class StreamProcessorArrayNode : public DTPNode{

  UHAL_DERIVEDNODE(StreamProcessorArrayNode)
  
public:
  explicit StreamProcessorArrayNode(const uhal::Node& );
  virtual ~StreamProcessorArrayNode();

  void CapCounters(const bool);
  void StreamSelect(const uint32_t, const bool);
  const uhal::Node& GetStreamProcessorNode(void);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORARRAYNODE_HPP_
