#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodNode.hpp"
#include "dtpcontrols/toolbox.hpp"

#include "uhal/uhal.hpp"

#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

  std::cout << "FLX-TPG FW reset" << std::endl;

  std::string conn_file = find_connection_file();
  std::string device("");

  if (argc >1) {
    device = argv[1];
  }
  else {
    std::cout << "At least specify a device" << std::endl;
  }

  if (argc > 2) {
    conn_file = std::string(argv[2]);
  }
  
  std::cout << "Connections : " << conn_file << std::endl;
  std::cout << "Device      : " << device << std::endl;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(std::string(argv[1]));

  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
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

  
}

