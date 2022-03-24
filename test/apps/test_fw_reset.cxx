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

  DTPPodNode dtp_pod_node (flx.getNode());
  dtp_pod_node.reset();
  
}

