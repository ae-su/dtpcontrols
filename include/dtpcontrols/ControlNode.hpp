/**
 * @file ControlNode.hpp
 *
 * ControlNode is a class derived from uhal::Node.
 * Its purpose is to control soft-reset, master-reset the
 * DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_CONTROLNODENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_CONTROLNODENODE_HPP_


#include "DTPNode.hpp"

class ControlNode : public DTPNode{

  UHAL_DERIVEDNODE(ControlNode)
  
public:
  explicit ControlNode(const uhal::Node& );
  virtual ~ControlNode();

  void Nuke(bool);
  void SoftReset(bool);
  void MasterReset(bool);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_CONTROLNODE_HPP_
