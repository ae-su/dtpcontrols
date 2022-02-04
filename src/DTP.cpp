/**
 * @file DTPNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPNode.hpp"

DTPNode::DTPNode(const uhal::Node& node) : uhal::Node(node) {};

DTPNode::~DTPNode() {};

/*
template <> void DTP::WriteReg(const Response<uint32_t> & lNodePath){};

template<> void DTP::ReadReg(const Response<uint32_t> & lNodePath) {};
*/
