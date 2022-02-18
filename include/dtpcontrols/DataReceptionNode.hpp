/**
 * @file DataReceptionNode.hpp
 *
 * DataReceptionNode is a class derived from 
 * Its purpose is to control and read status of the data-
 * reception firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class DataReceptionNode : public uhal::Node {

  UHAL_DERIVEDNODE(DataReceptionNode)
  
public:
  explicit DataReceptionNode(const uhal::Node& );
  virtual ~DataReceptionNode();

  void EnableDataReception(bool);
  void ResetInputWordCounter(bool);
  void ResetOutputWordCounter(bool);
  void ErrorReset(bool);
  uhal::ValWord<uint32_t> DualPortRamWriteFlag(bool);
  uhal::ValWord<uint32_t> StickyErrorBit(bool);
  uhal::ValWord<uint32_t> BackPressureBit(bool);
  uhal::ValWord<uint32_t> OutOfSync(bool);
  uhal::ValWord<uint32_t> RxWordCount(bool);
  uhal::ValWord<uint32_t> SentWordCount(bool);
  uhal::ValWord<uint32_t> SentPacketCount(bool);
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_
