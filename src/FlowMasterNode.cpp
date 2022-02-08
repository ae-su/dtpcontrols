/**
 * @file FlowMasterNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

//#include <cstdint>
#include <stdint.h>
#include <map>

//#include "logging/Logging.hpp"

#include "dtpcontrols/FlowMasterNode.hpp"

UHAL_REGISTER_DERIVED_NODE(FlowMasterNode)

//NodeNameBuilder* nnb;

FlowMasterNode::FlowMasterNode(const uhal::Node& node) : DTPNode(node){}

FlowMasterNode::~FlowMasterNode(){}

void FlowMasterNode::SourceSelect(const std::string& source, const bool dispatch) {
  std::map<std::string, std::uint16_t> src_map{{"gbt", 0}, {"wibtor", 1}};
  auto exists = src_map.find(source);
  if (exists != src_map.end()) {
    getNode("csr.ctrl.en").write(src_map[source]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown source. Please check."<<std::endl;
}

void FlowMasterNode::SinkSelect(const std::string& sink, bool dispatch) {
  std::map<std::string, std::uint16_t> sink_src{{"hits", 0}, {"link0", 1},
						{"link1", 1}, {"link2", 1},
						{"link3", 1}, {"link4", 1}};
  std::map<std::string, std::uint16_t> sink_link{{"hits", 0}, {"link0", 0},
						{"link1", 1}, {"link2", 2},
						{"link3", 3}, {"link4", 4}};
  auto exist_ss = sink_src.find(sink);
  if (exist_ss != sink_src.end()) {
    getNode("csr.ctrl.sink_src").write(sink_src[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink source. Please check."<<std::endl;

  auto exists_sl = sink_link.find(sink);
  if (exists_sl != sink_link.end()) {
    getNode("csr.ctrl.").write(sink_link[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink link. Please check."<<std::endl;
}

