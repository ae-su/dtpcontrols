/**
 * @file WibulatorNode.hpp
 *
 * WibulatorNode is a class derived from uhal::Node.
 * Its purpose is to control the wibulator component inside
 * DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

#include "uhal/DerivedNode.hpp"
#include <cstdint>
#include <uhal/ValMem.hpp>

namespace dunedaq {
namespace dtpcontrols {

class WibulatorNode : public uhal::Node {

  UHAL_DERIVEDNODE(WibulatorNode)
  
public:
  explicit WibulatorNode(const uhal::Node& );
  virtual ~WibulatorNode();

  void SetFire(bool);
  void SetMaxWord(const uint32_t&, const bool);
  void SetBufferAddress(bool);
  void SetBufferData(const std::vector<uint32_t>&, const bool);
  void SetChain(bool);  
  uhal::ValVector<uint32_t> GetBufferData(const uint32_t&, const bool);
  uhal::ValWord<uint32_t> GetAddressWidth(const bool);
  uhal::ValWord<uint32_t> GetMaxWord(const bool);
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

/*
csr.ctrl.max_word
csr.addr_width
buf.addr
buf.data
csr.ctrl.fire
csr.ctrl.chain
*/
