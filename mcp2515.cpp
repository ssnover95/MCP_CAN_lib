/*
  mcp_can.cpp
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.
  2014 Copyright (c) Cory J. Fowler  All Rights Reserved.
  2018 Copyright (c) Shane Snover           All rights reserved.

  Author: Loovee
  Contributor: Cory J. Fowler
  Contributor: Shane Snover

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-
  1301  USA
*/
#include "mcp2515.h"
#include "can-packet.h"
#include "mcp2515-register-map.h"

namespace CAN
{
namespace
{
enum class SPI_INSTRUCTION : uint8_t
{
    RESET = 0xC0,
    READ = 0x03,
    READ_RX_BUFFER = 0x90,
    WRITE = 0x02,
    LOAD_TX_BUFFER = 0x40,
    RTS = 0x80,
    READ_STATUS = 0xA0,
    RX_STATUS = 0xB0,
    BIT_MODIFY = 0x05,
}; // enum class SPI_INSTRUCTION

} // namespace

} // namespace CAN
