
#include "uhal/log/log.hpp"
#include "dtpcontrols/DTPNode.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/StreamProcessorNode.hpp"
#include "dtpcontrols/StreamProcessorArrayNode.hpp"
#include "dtpcontrols/DPRNode.hpp"
//#include "DummyComponent.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include <iostream>

using namespace uhal;

int main(int argc, char const* argv[]) {

  uhal::setLogLevelTo(uhal::Debug());
  const std::string lConnectionFile = "file://" + std::string(argv[1]);
  const std::string lDevice = "U-SIMUDP-JS";
  uhal::ConnectionManager cm(lConnectionFile); //, {"ipbusflx-2.0"})
  uhal::HwInterface flx = cm.getDevice(lDevice);

  // firmware information extract
  DTPNode dtpNode;
  auto lFirmwareInfo = dtpNode.GetFirmwareConfigInfo(flx);

  //hfButler.py flx-0-p2-hf init ### reset and initialise ####
  
  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.SoftReset(DISPATCH_TRUE);
  lCtrlNode.MasterReset(DISPATCH_FALSE);

  //hfButler.py flx-0-p2-hf cr-if --on --drop-empty ### enables cr-if and empty packet suppresion ###

  auto lCRIFNode = flx.getNode<CentralRouterInterfaceNode>("cr_if");
  lCRIFNode.EnableRouterInterface(DISPATCH_FALSE);
  lCRIFNode.DropEmpty(DISPATCH_FALSE);

  //hfButler.py flx-0-p2-hf flowmaster --src-sel gbt --sink-sel hits ### sets data router input to GBT source and sink to hitfinder output ###

  auto lFlowMasterNode = flx.getNode<FlowMasterNode>("flowmaster");
  lFlowMasterNode.SourceSelect("gbt", DISPATCH_FALSE);
  lFlowMasterNode.SinkSelect("hits", DISPATCH_FALSE);

  //hfButler.py flx-0-p2-hf link hitfinder -t 20 ### hitfinder threshold to 20 ###

  std::vector<std::string> links {"linkproc0.", "linkproc1.", "linkproc2.",
      "linkproc3.", "linkproc4."};
  uint32_t threshold = 20;
  for (auto& lnk : links) {
    //auto lDRlinkproc0 = flx.getNode<DataReceptionNode>("linkproc0.drtr.dr");
    auto streamProcArrayCS = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    auto streamProcCSR = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    for (uint32_t i=0; i<=lFirmwareInfo["n_port"]; i++){
      streamProcCSR.SetThreshold(threshold, DISPATCH_FALSE);
      streamProcArrayCS.StreamSelect(i, DISPATCH_TRUE);
    }
    flx.getClient().dispatch();
  }

  // hfButler.py flx-0-p2-hf link mask enable -c 1-63 ### this setting masks all but one wire per pipeline ###
  uint32_t channel_start{1};
  uint32_t channel_finsih{63};
  uint64_t mask_word;
  for (auto& lnk : links) {
    auto streamProcCSR = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    auto streamProcArrayCS = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    mask_word = 0x0;
    for (uint32_t j=channel_start; j<=channel_finsih; j++){
      mask_word |= (1<<j);
    }
    for (uint32_t i=0; i<=lFirmwareInfo["n_port"]; i++){
      streamProcArrayCS.StreamSelect(i, DISPATCH_FALSE);
      streamProcCSR.SetMaskChannel00To31(mask_word, DISPATCH_TRUE, MASK_ENABLE);
      streamProcCSR.SetMaskChannel32To63(mask_word>>32, DISPATCH_TRUE, MASK_ENABLE);
      streamProcArrayCS.getNode("csr.stream_sel").write(i);
    }
    flx.getClient().dispatch();
  }

  // hfButler.py flx-0-p2-hf link config --dr-on --dpr-mux passthrough --drop-empty ### enable data router ###
  // passthrough mux_in 1, mux_out 1
  uint32_t mux_in{1};
  uint32_t mux_out{1};
  for (auto& lnk : links) {
    auto dprNode = flx.getNode<DPRNode>(lnk+"drtr.dpr");
    dprNode.SetMuxIn(mux_in, DISPATCH_FALSE);
    dprNode.SetMuxOut(mux_out, DISPATCH_FALSE);
    auto drNode = flx.getNode<DataReceptionNode>(lnk+"drtr.dr");
    drNode.EnableDataReception(DISPATCH_FALSE);
    auto streamProcArrayCS = flx.getNode<StreamProcessorArrayNode>(lnk+"stream_procs");
    auto streamProcCSR = flx.getNode<StreamProcessorNode>(lnk+"stream_procs.stream_proc");
    for (uint32_t i=0; i<=lFirmwareInfo["n_port"]; i++){
      streamProcArrayCS.StreamSelect(i, DISPATCH_FALSE);
      streamProcCSR.DropEmpty(DISPATCH_FALSE);
    }
    flx.getClient().dispatch();
  }  
}
