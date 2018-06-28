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
#include "Arduino.h"
#include "can-packet.h"
#include "mcp2515-register-map.h"

namespace CAN
{
namespace
{
enum class SPI_INSTRUCTION : uint8_t
{
    DONT_CARE = 0x00,
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

struct MCP2515::STATUS_FIELD
{
    bool RX0InterruptFlag : 1;
    bool RX1InterruptFlag : 1;
    bool TX0TransmitRequest : 1;
    bool TX0InterruptFlag : 1;
    bool TX1TransmitRequest : 1;
    bool TX1InterruptFlag : 1;
    bool TX2TransmitRequest : 1;
    bool TX2InterruptFlag : 1;
}; // struct STATUS_FIELD

void MCP2515::resetController()
{
    digitalWrite(this->my_chip_select_pin, LOW);
    SPI.transfer(static_cast<uint8_t>(SPI_INSTRUCTION::RESET));
    digitalWrite(this->my_chip_select_pin, HIGH);
}

uint8_t MCP2515::readRegister(MCP2515_HARDWARE_ADDRESS address)
{
    digitalWrite(this->my_chip_select_pin, LOW);
    SPI.transfer(static_cast<uint8_t>(SPI_INSTRUCTION::READ));
    SPI.transfer(static_cast<uint8_t>(address));
    uint8_t data(SPI.transfer(SPI_INSTRUCTION::DONT_CARE));
    digitalWrite(this->my_chip_select_pin, HIGH);
    return data;
}

void MCP2515::writeRegister(MCP2515_HARDWARE_ADDRESS address, uint8_t data)
{
    digitalWrite(this->my_chip_select_pin, LOW);
    SPI.transfer(static_cast<uint8_t>(SPI_INSTRUCTION::WRITE));
    SPI.transfer(static_cast<uint8_t>(address));
    SPI.transfer(data);
    digitalWrite(this->my_chip_select_pin, HIGH);
}

MCP2515::STATUS_FIELD MCP2515::readStatus()
{
    digitalWrite(this->my_chip_select_pin, LOW);
    SPI.transfer(static_cast<uint8_t>(SPI_INSTRUCTION::READ_STATUS));
    auto status(static_cast<STATUS_FIELD>(SPI.transfer(SPI_INSTRUCTION::DONT_CARE)));
    digitalWrite(this->my_chip_select_pin, HIGH);
    return status;
}

} // namespace CAN
