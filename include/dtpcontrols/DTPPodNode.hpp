/**
 * @file DTPPodNode.hpp
 *
 * Top level DTP Pod
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

// dtpcontrols Headers
#include "dtpcontrols/InfoNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/OutputSinkNode.hpp"
#include "dtpcontrols/WibulatorNode.hpp"
#include "dtpcontrols/LinkProcessorNode.hpp"
#include "dtpcontrols/MonProbeNodeInfo.hpp"


// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers
#include <chrono>
#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {

    class DTPPodNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(DTPPodNode)

      public:

      explicit DTPPodNode(const uhal::Node& node);
      virtual ~DTPPodNode();

      // set firmware build config information
      void set_n_links(uint32_t n_links);
      void set_n_port(uint32_t n_port);
      void set_n_mux(uint32_t n_mux);
      void set_wibtors_width(uint32_t wibtors_width);
      void set_outsink_width(uint32_t outsink_width);
      void set_wibtors_en(uint32_t wibtors_en);
      void set_outsink_en(uint32_t outsink_en);      

      // get nodes
      const InfoNode& get_info_node() const;
      const ControlNode& get_control_node() const;
      const FlowMasterNode& get_flowmaster_node() const;
      const WibulatorNode& get_wibulator_node(uint i) const;
      const LinkProcessorNode& get_link_processor_node(uint i) const;
      const CentralRouterInterfaceNode& get_crif_node() const;
      const OutputSinkNode& get_output_sink_node() const;

      // reset everything
      void reset() const;

      // reset counters
      void reset_counters() const;

      // set input to wibulator
      void set_source_int() const;

      // set input to external data
      void set_source_ext() const;

      // set sink (spy) to hits
      void set_sink_hits() const;

      // set crif to drop empty packets
      void set_crif_drop_empty() const;

      // setup a link processor
      void setup_processors() const;

      // set all thresholds
      void set_threshold_all(int threshold) const;

      // reset all masks
      void reset_masks() const;

      // set masks for all channels in one link/pipe
      void set_channel_mask(int link, int pipe, uint64_t mask) const;

      // mask one channel
      void mask_channel(int link, int pipe, int channel) const;

      // enable CRIF
      void enable_crif() const;

      // disable CRIF
      void disable_crif() const;

      // get mon probe info
      std::vector<MonProbeNodeInfo> get_mon_probe_info(int link, int pipe) const;

    private:
      
      // firware config info this build contains
      std::map<std::string, uint32_t> m_dtp_fw_info;
      uint32_t m_n_links = 0;
      uint32_t m_n_port = 0;
      uint32_t m_n_mux = 0;
      uint32_t m_wibtors_width = 0;
      uint32_t m_outsink_width = 0;
      uint32_t m_wibtors_en = false;
      uint32_t m_outsink_en = false;      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_
