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
//#include "dtpcontrols/InfoNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
//#include "dtpcontrols/OutputSinkNode.hpp"
//#include "dtpcontrols/WibulatorNode.hpp"
//#include "dtpcontrols/LinkProcessorNode.hpp"

// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers
#include <chrono>
#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {
    /**
     * @brief      Example of uhal::Node derived class.
     */
    class DTPPodNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(DTPPodNode)

      public:
      explicit DTPPodNode(const uhal::Node& node);
      virtual ~DTPPodNode();

      void reset();

    private:

      //InfoNode m_info_node;
      ControlNode m_ctrl_node;
      FlowMasterNode m_flowmaster_node;
      CentralRouterInterfaceNode m_crif_node;
      //      OutputSinkNode m_outsink_node;

      //      std::vector<WibulatorNode> m_wibtor_nodes;
      //      std::vector<LinkProcessorNode> m_link_nodes;
      

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_
