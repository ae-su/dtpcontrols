/**
 * @file CentralRouterInterfaceNode.hpp
 *
 * CentralRouterInterfaceNode is a class derived from DTPNode which
 * derives from uhal::Node.
 * Its purpose is to control and read status of the central-router-interface
 * firmware block, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_

#include "dtpcontrols/DTPNode.hpp"

class CentralRouterInterfaceNode : public DTPNode{

  UHAL_DERIVEDNODE(CentralRouterInterfaceNode)
  
public:
  explicit CentralRouterInterfaceNode(const uhal::Node& );
  virtual ~CentralRouterInterfaceNode();

  void EnableRouterInterface(bool);
  void DropEmpty(bool);
  /*
  void B0FIFOReady(bool);
  void B0FIFOValid(bool);
  void B0FIFOUser(bool);
  void B0FIFOLast(bool);
  void B0FIFOLastError(bool);
  void B0FIFOPktCount(bool);
  void B0FIFOAXIError(bool);
  void B1FrameManagerReady(bool);
  void B1FrameManagerValid(bool);
  void B1FrameManagerUser(bool);
  void B1FrameManagerLast(bool);
  void B1FrameManagerLastError(bool);
  void B1FrameManagerPktCount(bool);
  void B1FrameManagerAXIError(bool);

  void B2FrameMemoryReady(bool);
  void B2FrameMemoryValid(bool);
  void B2FrameMemoryUser(bool);
  void B2FrameMemoryLast(bool);
  void B2FrameMemoryLastError(bool);
  void B2FrameMemoryPktCount(bool);
  void B2FrameMemoryAXIError(bool);

  void B3OutIdle(bool);
  void B3OutEOP(bool);
  void B3OutSOP(bool);
  void B3Valid(bool);
  void B3OutPktCount(bool);
  void B3OutKError(bool);

  void B4MiscFrameReadPT(bool);
  void B4MiscFrameWritePT(bool);
  void B4MiscFmanSWord(bool);
  void B4MiscFrameCount(bool);
  void B4MiscWordCount(bool);
  void B4MiscCRWordType(bool);
  void B4MiscEndFrame(bool);
  void B4MiscFIFOEmpty(bool);
  void B4MiscFIFOFull(bool);

  void B5CRState(bool);
  */
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_
