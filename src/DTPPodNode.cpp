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
    
    //-----------------------------------------------------------------------------
    DTPPodNode::DTPPodNode(const uhal::Node& node) :uhal::Node(node),
      m_ctrl_node(node.getNode<ControlNode>("ctrl")),
      m_flowmaster_node(node.getNode<FlowMasterNode>("flowmaster")),
      m_crif_node(node.getNode<CentralRouterInterfaceNode>("cr_if"))
    {

    }
    //-----------------------------------------------------------------------------
    
    //-----------------------------------------------------------------------------
    DTPPodNode::~DTPPodNode() {}
    //-----------------------------------------------------------------------------
    
    //-----------------------------------------------------------------------------
    void DTPPodNode::reset() {
      
      m_ctrl_node.SoftReset(true);
      m_ctrl_node.MasterReset(true);
      
      /*      for (auto it; it=m_links.start(); it!=m_links.end() ){
	it->ResetInputWordCounter(true);
	it->ResetOutputWordCounter(true);
	it->ErrorReset(true);
	}*/
     
    }
    
  } // namespace dtpcontrols
} // namespace dunedaq
