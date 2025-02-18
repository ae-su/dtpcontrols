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

#include "dtpcontrols/MonProbeNode.hpp"

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    class StreamProcessorNode : public uhal::Node {

      UHAL_DERIVEDNODE(StreamProcessorNode)
  
      public:
      explicit StreamProcessorNode(const uhal::Node& node);
      virtual ~StreamProcessorNode();

      const MonProbeNode& get_mon_probe_node(uint32_t i) const;

      int get_n_probes() const;

      // set stream to drop empty packets
      void drop_empty(bool dispatch=true) const;

      // set the TP threshold (all 64 channels)
      void set_threshold(const uint32_t threshold, bool dispatch=true) const;

      // get the channel mask (all 64 channels)
      uint64_t get_channel_mask() const;

      // set the mask for all channels (all 64 channels)
      void set_channel_mask(uint64_t mask, bool dispatch=true) const;

      // mask one channel
      void mask_channel(int channel) const;


      // remove these methods, which are redundant
      void set_mask_channels(const uint64_t msb00to31_lsb31to64,
			     bool dispatch=true, bool mask_en_dsbl=true) const;
      void set_mask_channel_00to31(const uint32_t mask00to31,
				   bool dispatch=true, bool mask_en_dsbl=true) const;
      void set_mask_channel_32to63(const uint32_t mask32to63,
				   bool dispatch=true, bool mask_en_dsbl=true) const;

      const uhal::ValWord<uint32_t> get_mask_channel_00to31(bool dispatch=true) const;
      const uhal::ValWord<uint32_t> get_mask_channel_32to63(bool dispatch=true) const;
      // end of redundant methods

    private:
      uint32_t m_n_mon_probes;

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_
