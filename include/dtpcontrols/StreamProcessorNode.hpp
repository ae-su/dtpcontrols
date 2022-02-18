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

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class StreamProcessorNode : public uhal::Node {

  UHAL_DERIVEDNODE(StreamProcessorNode)
  
public:
  explicit StreamProcessorNode(const uhal::Node& );
  virtual ~StreamProcessorNode();

  void DropEmpty(const bool);
  void SetMaskChannels(const uint64_t, const bool, const bool);
  void SetMaskChannel00To31(const uint32_t, const bool, const bool);
  void SetMaskChannel32To63(const uint32_t, const bool,const bool);
  void CapCounters(const bool);
  void SetThreshold(const uint16_t, const bool);
  const uhal::ValWord<uint32_t> GetMaskChannel00To31(const bool);
  const uhal::ValWord<uint32_t> GetMaskChannel32To63(const bool);
<<<<<<< HEAD
  
=======
  const uhal::Node& GetMonProbeNode(const std::string&);

>>>>>>> 928243730bf340623a47b65f426a8e74ba90d05e
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_
