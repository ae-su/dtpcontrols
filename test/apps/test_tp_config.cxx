
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/ControlNode.hpp"

#include "uhal/uhal.hpp"

#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

  std::string conn_string = std::string("file://") + std::string(getenv("DTP_SHARE")) + std::string("/config/etc/connections.xml");
  if (argc > 2) {
    conn_string = std::string(argv[2]);
  }
  
  std::cout << conn_string << std::endl;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_string, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(std::string(argv[1]));
  
  //hfButler.py flx-0-p2-hf init ### reset and initialise ####
  
  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.SoftReset(true);
  lCtrlNode.MasterReset(true);

  //hfButler.py flx-0-p2-hf cr-if --on --drop-empty ### enables cr-if and empty packet suppresion ###

  auto lCRIFNode = flx.getNode<CentralRouterInterfaceNode>("cr_if");
  lCRIFNode.EnableRouterInterface(true);
  lCRIFNode.DropEmpty(true);

  //hfButler.py flx-0-p2-hf flowmaster --src-sel gbt --sink-sel hits ### sets data router input to GBT source and sink to hitfinder output ###

  auto lFlowMasterNode = flx.getNode<FlowMasterNode>("flowmaster");
  lFlowMasterNode.SourceSelect("gbt", true);
  lFlowMasterNode.SinkSelect("hits", true);

  //hfButler.py flx-0-p2-hf link hitfinder -t 20 ### hitfinder threshold to 20 ###
 

}
