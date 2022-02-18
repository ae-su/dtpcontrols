
#include "uhal/log/log.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
//#include "DummyComponent.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include <iostream>

using namespace uhal;

int main(int argc, char const* argv[]) {

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm("file://" + std::string(argv[1])); //, {"ipbusflx-2.0"})
  uhal::HwInterface flx = cm.getDevice("U-SIMUDP-JS");

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
 

}
