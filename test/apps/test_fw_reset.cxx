#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/ControlNode.hpp"

#include "uhal/uhal.hpp"

#include <cstdlib>
#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

  uhal::setLogLevelTo(uhal::Debug());
  if (argc != 3){
    std::cout<< "Wrong number of arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  uhal::ConnectionManager cm("file://" + std::string(argv[1]), {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice("U-SIMUDP");

  auto lCtrlNode = flx.getNode<ControlNode>("ctrl");
  lCtrlNode.soft_reset(true);
  std::cout << "Done soft reset" << std::endl;
  lCtrlNode.master_reset(true);
  std::cout << "Done master reset" << std::endl;

  auto lDRlinkproc0 = flx.getNode<DataReceptionNode>("linkproc0.drtr.dr");
  auto lDRlinkproc1 = flx.getNode<DataReceptionNode>("linkproc1.drtr.dr");
  auto lDRlinkproc2 = flx.getNode<DataReceptionNode>("linkproc2.drtr.dr");
  auto lDRlinkproc3 = flx.getNode<DataReceptionNode>("linkproc3.drtr.dr");
  auto lDRlinkproc4 = flx.getNode<DataReceptionNode>("linkproc4.drtr.dr");
  
  lDRlinkproc0.reset_input_word_counter(true);
  lDRlinkproc0.reset_output_word_counter(true);
  lDRlinkproc0.error_reset(true);

  std::cout << "linkproc0 DR reset." << std::endl;
  
  lDRlinkproc1.reset_input_word_counter(true);
  lDRlinkproc1.reset_output_word_counter(true);
  lDRlinkproc1.error_reset(true);
  
  lDRlinkproc2.reset_input_word_counter(true);
  lDRlinkproc2.reset_output_word_counter(true);
  lDRlinkproc2.error_reset(true);
  
  lDRlinkproc3.reset_input_word_counter(true);
  lDRlinkproc3.reset_output_word_counter(true);
  lDRlinkproc3.error_reset(true);

  lDRlinkproc4.reset_input_word_counter(true);
  lDRlinkproc4.reset_output_word_counter(true);
  lDRlinkproc4.error_reset(true);
  
  std::cout << "Done link DR reset" << std::endl;
  return 0;
}

