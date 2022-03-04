#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/StreamProcessorNode.hpp"
#include "dtpcontrols/StreamProcessorArrayNode.hpp"
#include "dtpcontrols/DPRNode.hpp"

#include "dtpcontrols/ControlNode.hpp"
#include <cstdlib>
#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;
int main(int argc, char const* argv[]) {

  if (argc != 3){
    std::cout << "wrong number of arguments." << std::endl;
    exit(EXIT_FAILURE);
  }

  uhal::setLogLevelTo(uhal::Debug());
  const std::string lConnectionFile = "file://" + std::string(argv[1]);
  const std::string lDevice = std::string(argv[2]);
  uhal::ConnectionManager cm(lConnectionFile,{"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(lDevice);

  // firmware information extract
  /*
  auto lFWInfoNode = flx.getNode<DTPNode>("info");
  DTPNode dtpNode(lFWInfoNode);
  auto lFirmwareInfo = dtpNode.GetFirmwareConfigInfo(); */
  
  auto infoNodes = flx.getNode("info.config").getNodes(); // info.id.config 
  std::map<std::string, uhal::ValWord<uint32_t>> lFirmwareInfo;
  for (const auto& infoNode : infoNodes) {
    lFirmwareInfo.insert({infoNode, flx.getNode("info.config."+infoNode).read()});
  }
  flx.getClient().dispatch();
  std::cout << "FIRMWARE INFO EXTRACTED" <<std::endl;
  
  //hfButler.py flx-0-p2-hf init ### reset and initialise ####
  
  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.soft_reset(true);
  lCtrlNode.master_reset(true);
  std::cout << "INIT SEQUENCE DONE hfButler.py flx-0-p2-hf init" <<std::endl;
  
  //hfButler.py flx-0-p2-hf cr-if --on --drop-empty ### enables cr-if and empty packet suppresion ###

  auto lCRIFNode = flx.getNode<CentralRouterInterfaceNode>("cr_if");
  lCRIFNode.enable_central_router_interface(true);
  lCRIFNode.drop_empty(true);
  std::cout << "DONE hfButler.py flx-0-p2-hf cr-if --on --drop-empty" <<std::endl;
  
  //hfButler.py flx-0-p2-hf flowmaster --src-sel gbt --sink-sel hits ### sets data router input to GBT source and sink to hitfinder output ###

  auto lFlowMasterNode = flx.getNode<FlowMasterNode>("flowmaster");
  lFlowMasterNode.source_select("gbt", true);
  lFlowMasterNode.sink_select("hits", true);
  std::cout << "DONE hfButler.py flx-0-p2-hf flowmaster --src-sel gbt --sink-sel hits" <<std::endl;  

  //hfButler.py flx-0-p2-hf link hitfinder -t 20 ### hitfinder threshold to 20 ###

  std::vector<std::string> links {"linkproc0.", "linkproc1.", "linkproc2.",
      "linkproc3.", "linkproc4."};
  uint32_t threshold = 20;
  for (auto& lnk : links) {
    //auto lDRlinkproc0 = flx.getNode<DataReceptionNode>("linkproc0.drtr.dr");
    auto streamProcArrayNode = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    auto streamProcNode = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    for (uint32_t i=0; i<=lFirmwareInfo["n_port"]; i++){
      streamProcNode.set_threshold(threshold, true);
      streamProcArrayNode.stream_select(i, true);
    }
    flx.getClient().dispatch();
  }
  std::cout << "DONE hfButler.py flx-0-p2-hf link hitfinder -t 20" <<std::endl;
  
  // hfButler.py flx-0-p2-hf link mask enable -c 1-63 ### this setting masks all but one wire per pipeline ###
  uint32_t channel_start{1};
  uint32_t channel_finsih{63};
  uint64_t mask_word;
  for (auto& lnk : links) {
    auto streamProcNode = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    auto streamProcArrayNode = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    mask_word = 0x0;
    std::cout << lnk << std::endl;
    for (uint32_t j=channel_start; j<=channel_finsih; j++){
      mask_word |= (1<<j);
    }
    for (uint32_t i=0; i<lFirmwareInfo["n_port"]; i++){
      streamProcArrayNode.stream_select(i, true);
      streamProcNode.set_mask_channel_00to31(mask_word, true, MASK_ENABLE);
      streamProcNode.set_mask_channel_32to63(mask_word>>32, true, MASK_ENABLE);
      std::cout << i <<std::endl;      
    }
    flx.getClient().dispatch();
  }
  std::cout << "DONE hfButler.py flx-0-p2-hf link mask enable -c 1-63" <<std::endl;
  
  // hfButler.py flx-0-p2-hf link config --dr-on --dpr-mux passthrough --drop-empty ### enable data router ###
  // passthrough mux_in 1, mux_out 1
  uint32_t mux_in{1};
  uint32_t mux_out{1};
  for (auto& lnk : links) {
    auto dprNode = flx.getNode<DPRNode>(lnk+"drtr.dpr");
    dprNode.set_mux_in(mux_in, true);
    dprNode.set_mux_out(mux_out, true);
    auto drNode = flx.getNode<DataReceptionNode>(lnk+"drtr.dr");
    drNode.enable_data_reception(true);
    auto streamProcArrayNode = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    auto streamProcNode = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    std::cout << lFirmwareInfo["n_port"] << std::endl;
    for (uint32_t i=0; i<lFirmwareInfo["n_port"]; i++){
      streamProcArrayNode.stream_select(i, true);
      streamProcNode.drop_empty(true);
      std::cout << i << std::endl;
    }
    flx.getClient().dispatch();
  }
  std::cout << "DONE hfButler.py flx-0-p2-hf link config --dr-on --dpr-mux passthrough --drop-empty" <<std::endl;  
  return 0;
}
