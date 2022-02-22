/**
 * @file DTPPodNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPPodNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(DTPPodNode)
    

    DTPPodNode::DTPPodNode(const uhal::Node& node) :uhal::Node(node),
      m_n_links(5)
    {
    }

    DTPPodNode::~DTPPodNode() {}

    const ControlNode& DTPPodNode::get_control_node() const {
      return getNode<ControlNode>("ctrl");
    }

    const FlowMasterNode& DTPPodNode::get_flowmaster_node() const {
      return getNode<FlowMasterNode>("flowmaster");
    }
    
    const LinkProcessorNode& DTPPodNode::get_link_processor_node(uint32_t i) const {
      if (i < m_n_links) {
	std::string name("linkproc");
	name += std::to_string(i);
	return getNode<LinkProcessorNode>(name);
      }
      else {
	//throw
      }
    }

    const CentralRouterInterfaceNode& DTPPodNode::get_crif_node() const {
      return getNode<CentralRouterInterfaceNode>("cr_if");
    }
    

    void DTPPodNode::reset() {
    
      auto lCtrlNode = get_control_node();
      lCtrlNode.SoftReset(true);
      lCtrlNode.MasterReset(true);
      
      for (uint i=0; i!=m_n_links; ++i) {	
	auto lDataReceptionNode = get_link_processor_node(i).get_data_router_node().get_data_reception_node();
	lDataReceptionNode.ResetInputWordCounter(true);
	lDataReceptionNode.ResetOutputWordCounter(true);
	lDataReceptionNode.ErrorReset(true);
      }

    }
    
  } // namespace dtpcontrols
} // namespace dunedaq
