#include "dtpcontrols/DataReceptionNode.hpp"
//#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodNode.hpp"

#include "uhal/uhal.hpp"

#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

  std::string conn_string = std::string("file://") + std::string(getenv("DTP_SHARE")) + std::string("/config/connections.xml");
  if (argc > 2) {
    conn_string = std::string(argv[2]);
  }
  
  std::cout << conn_string << std::endl;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_string, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(std::string(argv[1]));

  auto lDTPPodNode = flx.getNode<DTPPodNode>("TOP");
  std::cout << lDTPPodNode.getNodes() << std::endl;

  /*  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.SoftReset(true);
  lCtrlNode.MasterReset(true);

  auto lDRlinkproc0 = flx.getNode<DataReceptionNode>("linkproc0.drtr.dr");
  auto lDRlinkproc1 = flx.getNode<DataReceptionNode>("linkproc1.drtr.dr");
  auto lDRlinkproc2 = flx.getNode<DataReceptionNode>("linkproc2.drtr.dr");
  auto lDRlinkproc3 = flx.getNode<DataReceptionNode>("linkproc3.drtr.dr");
  auto lDRlinkproc4 = flx.getNode<DataReceptionNode>("linkproc4.drtr.dr");

  lDRlinkproc0.ResetInputWordCounter(true);
  lDRlinkproc0.ResetOutputWordCounter(true);
  lDRlinkproc0.ErrorReset(true);

  lDRlinkproc1.ResetInputWordCounter(true);
  lDRlinkproc1.ResetOutputWordCounter(true);
  lDRlinkproc1.ErrorReset(true);

  lDRlinkproc2.ResetInputWordCounter(true);
  lDRlinkproc2.ResetOutputWordCounter(true);
  lDRlinkproc2.ErrorReset(true);

  lDRlinkproc3.ResetInputWordCounter(true);
  lDRlinkproc3.ResetOutputWordCounter(true);
  lDRlinkproc3.ErrorReset(true);

  lDRlinkproc4.ResetInputWordCounter(true);
  lDRlinkproc4.ResetOutputWordCounter(true);
  lDRlinkproc4.ErrorReset(true);

  */
}

