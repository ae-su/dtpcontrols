/**
 * @file RouterNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/RouterNode.hpp"

#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/DPRNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(RouterNode)

RouterNode::RouterNode(const uhal::Node& node) : uhal::Node(node) {}

RouterNode::~RouterNode() {}

} // namespace dtpcontrols
} // namespace dunedaq
