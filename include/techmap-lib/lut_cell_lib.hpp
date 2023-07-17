// ***************************************************************************************
// Copyright (c) 2023-2025 Peng Cheng Laboratory
// Copyright (c) 2023-2025 Shanghai Anlogic Infotech Co.,Ltd.
// Copyright (c) 2023-2025 Peking University
//
// iMAP-FPGA is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
// http://license.coscl.org.cn/MulanPSL2
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//
// See the Mulan PSL v2 for more details.
// ***************************************************************************************
#pragma once
#include "utils/ifpga_namespaces.hpp"

#include <cstring>
#include <array>

iFPGA_NAMESPACE_HEADER_START

#define MAX_LUT_SIZE 25

/**
 * @brief LUT CELL structure
 */
struct lut_cell
{ 
  std::string                         name{};
  uint8_t                             max_size = MAX_LUT_SIZE;
  std::array<float, MAX_LUT_SIZE+1>   areas{};
  std::array<float, MAX_LUT_SIZE+1>   delays{};
  // bfsnpn::interger_truth_table        tt{};
};

iFPGA_NAMESPACE_HEADER_END