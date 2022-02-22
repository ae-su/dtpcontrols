
#include "dtpcontrols/LinkProcessorNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(LinkProcessorNode)

    LinkProcessorNode::LinkProcessorNode(const uhal::Node& node) : uhal::Node(node) { }

    LinkProcessorNode::~LinkProcessorNode() {}

    const DataRouterNode& LinkProcessorNode::get_data_router_node() const {
      return getNode<DataRouterNode>("drtr"); 
    }

    const StreamProcessorArrayNode& LinkProcessorNode::get_stream_proc_array_node() const {
      return getNode<StreamProcessorArrayNode>("stream_procs"); 
    }

  }

}
