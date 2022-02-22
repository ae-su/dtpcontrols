/**
 * @file DTPNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPNode.hpp"

#include <cstdint>
#include <uhal/HwInterface.hpp>
#include <uhal/ValMem.hpp>



DTPNode::DTPNode(const uhal::Node& node) : uhal::Node(node) {};

DTPNode::~DTPNode() {};

std::map<std::string, uhal::ValWord<uint32_t>> DTPNode::GetFirmwareConfigInfo(uhal::HwInterface& Iface) {
  std::vector<std::string> infoNodes{Iface.getNodes("info.id.config")};
  std::map<std::string, uhal::ValWord<uint32_t>> config_vals;
  for (const auto& node : infoNodes) {
    config_vals.insert({node, getNode(node).read()});
  }
  getClient().dispatch();
  return config_vals;
  };



