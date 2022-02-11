
#include "uhal/log/log.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
//#include "DummyComponent.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include <iostream>

using namespace uhal;

int main(int argc, char const* argv[]) {

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm("file://" + std::string(argv[1])); //, {"ipbusflx-2.0"})
  uhal::HwInterface flx = cm.getDevice("U-SIMUDP-JS");

  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.SoftReset(DISPATCH_TRUE);
  lCtrlNode.MasterReset(DISPATCH_TRUE);

  auto lDRlinkproc0 = flx.getNode<DataReceptionNode>("linkproc0.drtr.dr");
  auto lDRlinkproc1 = flx.getNode<DataReceptionNode>("linkproc1.drtr.dr");
  auto lDRlinkproc2 = flx.getNode<DataReceptionNode>("linkproc2.drtr.dr");
  auto lDRlinkproc3 = flx.getNode<DataReceptionNode>("linkproc3.drtr.dr");
  auto lDRlinkproc4 = flx.getNode<DataReceptionNode>("linkproc4.drtr.dr");

  lDRlinkproc0.ResetInputWordCounter(DISPATCH_TRUE);
  lDRlinkproc0.ResetOutputWordCounter(DISPATCH_TRUE);
  lDRlinkproc0.ErrorReset(DISPATCH_TRUE);

  lDRlinkproc1.ResetInputWordCounter(DISPATCH_TRUE);
  lDRlinkproc1.ResetOutputWordCounter(DISPATCH_TRUE);
  lDRlinkproc1.ErrorReset(DISPATCH_TRUE);

  lDRlinkproc2.ResetInputWordCounter(DISPATCH_TRUE);
  lDRlinkproc2.ResetOutputWordCounter(DISPATCH_TRUE);
  lDRlinkproc2.ErrorReset(DISPATCH_TRUE);

  lDRlinkproc3.ResetInputWordCounter(DISPATCH_TRUE);
  lDRlinkproc3.ResetOutputWordCounter(DISPATCH_TRUE);
  lDRlinkproc3.ErrorReset(DISPATCH_TRUE);

  lDRlinkproc4.ResetInputWordCounter(DISPATCH_TRUE);
  lDRlinkproc4.ResetOutputWordCounter(DISPATCH_TRUE);
  lDRlinkproc4.ErrorReset(DISPATCH_TRUE);
}

