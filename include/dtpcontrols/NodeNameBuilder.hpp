/**
 * @file NodeNameBuilder.hpp
 *
 * NodeNameBuilder is a standalone class.
 * Its purpose is to stitch stings within AllNodeNames.hpp
 * to contruct hierarchial IPBus node names.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTP_INCLUDE_DTP_NODENAMEBUILDER_HPP_
#define DTP_INCLUDE_DTP_NODENAMEBUILDER_HPP_

#include <iostream>

class NodeNameBuilder{

public:

  NodeNameBuilder();
  ~NodeNameBuilder();

  template<typename T>
  T Stitch(T lLast);
  
  template<typename T, typename... Args>
  T Stitch(T lFirst, Args... lArgs);
};

inline NodeNameBuilder::NodeNameBuilder() {}

inline NodeNameBuilder::~NodeNameBuilder() {}

template<typename T>
T NodeNameBuilder::Stitch(T lLast) {
  return lLast;
}

template<typename T, typename... Args>
T NodeNameBuilder::Stitch(T lFirst, Args... lArgs) {
  return lFirst + '.' + Stitch(lArgs...);
}

#endif // DTP_INCLUDE_DTP_DATARECEPTIONNODE_HPP_
