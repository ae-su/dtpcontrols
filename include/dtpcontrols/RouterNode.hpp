/**
 * @file RouterNode.hpp
 *
 * RouterNode is a class derived from DTPNode which
 * derives from uhal::Node.
 * Its purpose is to control and read status of the flowmaster
 * firmware block, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_ROUTERNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_ROUTERNODE_HPP_

#include "dtpcontrols/DTPNode.hpp"

class RouterNode : public DTPNode{

  UHAL_DERIVEDNODE(RouterNode)
  
public:
  explicit RouterNode(const uhal::Node& );
  virtual ~RouterNode();

  const uhal::Node & GetDataReceptionNode(void);
  const uhal::Node & GetDPRNode(void);
  //const uhal::Node & UnpackerNode(const std::string&, const bool);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_ROUTERNODE_HPP_
