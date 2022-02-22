/**
 * @file OutputSinkNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/OutputSinkNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(OutputSinkNode)

//-----------------------------------------------------------------------------
OutputSinkNode::OutputSinkNode(const uhal::Node& node)
  : uhal::Node(node)
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
OutputSinkNode::~OutputSinkNode() {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

} // namespace dtpcontrols
} // namespace dunedaq
