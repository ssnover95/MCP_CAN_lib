/*
 * mcp2515-register-map.h
 * 2018 Copyright (c) Shane Snover           All rights reserved.

 * Author:Loovee
 * Contributor: Cory J. Fowler
 * Contributor: Shane Snover
 * 2018-06-27
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-
 * 1301  USA
 */

#ifndef MCP2515_REGISTER_MAP_H_
#define MCP2515_REGISTER_MAP_H_

#include <stdint.h>

namespace CAN
{
using REGISTER = uint8_t;

enum class MCP2515_HARDWARE_ADDRESS : uint8_t
{
    RXF0SIDH = 0x00,
    RXF0SIDH,
    RXF0SIDL,
    RXF0EID8,
    RXF0EID0,
    RXF1SIDH,
    RXF1SIDL,
    RXF1EID8,
    RXF1EID0,
    RXF2SIDH,
    RXF2SIDL,
    RXF2EID8,
    RXF2EID0,
    CANSTAT = 0x0E,
    CANCTRL,
    RXF3SIDH,
    RXF3SIDL,
    RXF3EID8,
    RXF3EID0,
    RXF4SIDH,
    RXF4SIDL,
    RXF4EID8,
    RXF4EID0,
    RXF5SIDH,
    RXF5SIDL,
    RXF5EID8,
    RXF5EID0,
    TEC,
    REC,
    RXM0SIDH = 0x20,
    RXM0SIDL,
    RXM0EID8,
    RXM0EID0,
    RXM1SIDH,
    RXM1SIDL,
    RXM1EID8,
    RXM1EID0,
    CNF3,
    CNF2,
    CNF1,
    CANINTE,
    CANINTF,
    EFLG,
    TXB0CTRL = 0x30,
    TXB1CTRL = 0x40,
    TXB2CTRL = 0x50,
    RXB0CTRL = 0x60,
    RXB0SIDH = 0x61,
    RXB1CTRL = 0x70,
    RXB1SIDH = 0x71,
}; // enum class MCP2515_HARDWARE_ADDRESS

} // namespace CAN

#endif // MCP2515_REGISTER_MAP_H_
