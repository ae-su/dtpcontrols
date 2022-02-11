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
  std::map<std::string, uint32_t> src_map{{"gbt", 0}, {"wibtor", 1}};
  if (Exists(source, src_map)) {
    getNode("csr.ctrl.en").write(src_map[source]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown source. Please check."<<std::endl;
}

void FlowMasterNode::SourceSelect(const uint32_t &source, const bool dispatch) {
  const std::vector<uint32_t> src_num{0, 1};
  if (Exists(source, src_num)) {
    getNode("csr.ctrl.en").write(src_num[source]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown source. Please check."<<std::endl;
}

void FlowMasterNode::SinkSelect(const std::string& sink, bool dispatch) {
  std::map<std::string, uint32_t> sink_src{{"hits", 0}, {"link0", 1},
						{"link1", 1}, {"link2", 1},
						{"link3", 1}, {"link4", 1}};
  std::map<std::string, uint32_t> sink_link{{"hits", 0}, {"link0", 0},
						{"link1", 1}, {"link2", 2},
						{"link3", 3}, {"link4", 4}};
  if (Exists(sink, sink_src)) {
    getNode("csr.ctrl.sink_src").write(sink_src[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink source. Please check."<<std::endl;

  if (Exists(sink, sink_link)) {
    getNode("csr.ctrl.").write(sink_link[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink link. Please check."<<std::endl;
}

void FlowMasterNode::SinkSelect(const uint32_t& sink, bool dispatch) {
  std::vector<uint32_t> sink_src{0, 1};
  std::vector<std::uint32_t> sink_link{0, 1, 2, 3, 4};
  if (Exists(sink, sink_src)) {
    getNode("csr.ctrl.sink_src").write(sink_src[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink source. Please check."<<std::endl;

  if (Exists(sink, sink_link)) {
    getNode("csr.ctrl.").write(sink_link[sink]);
    if(dispatch) {getClient().dispatch();}
  }
  else std::cout<<"Unknown sink link. Please check."<<std::endl;
}


bool FlowMasterNode::Exists(const std::string &s,
            std::map<std::string, uint32_t> &map) {
  return   map.find(s) != map.end()?1:0;
}

bool FlowMasterNode::Exists(const uint32_t &s,
            const std::vector<uint32_t> &mux_values) {
  return   std::find(mux_values.begin(), mux_values.end(), s) != mux_values.end()?1:0;
}

