/**
 * @file DTP.hpp
 *
 * DTP.hpp is a class derived from uhal::Node.
 * Its purpose is to provide an interface to functions within
 * uhal::Node to classes in dtpcontrols.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPNODE_HPP_

#define DISPATCH_TRUE 1
#define DISPATCH_FALSE 0

// uhal includes
#include "uhal/uhal.hpp"
#include "uhal/ConnectionManager.hpp"
#include "uhal/HwInterface.hpp"
#include "uhal/DerivedNode.hpp"


class DTPNode : public uhal::Node {

public:
  DTPNode();
  explicit DTPNode(const uhal::Node&);
  virtual ~DTPNode();

  std::map<std::string, uhal::ValWord<uint32_t>> GetFirmwareConfigInfo(uhal::HwInterface& Iface);

};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPNODE_HPP_
