#include "dtpcontrols/DTP.hpp"

DTP::DTP(const uhal::Node& node) : uhal::Node(node) {};

DTP::~DTP() {};

/*
template <> void DTP::WriteReg(const Response<uint32_t> & lNodePath){};

template<> void DTP::ReadReg(const Response<uint32_t> & lNodePath) {};
*/
