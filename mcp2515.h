/*
  mcp2515.h
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.
  2016 Copyright (c) Cory J. Fowler         All Rights Reserved.
  2018 Copyright (c) Shane Snover           All rights reserved.

  Author:Loovee
  Contributor: Cory J. Fowler
  Contributor: Shane Snover
  2018-06-26
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

#ifndef _MCP2515_H_
#define _MCP2515_H_

namespace CAN
{
/*
 * Forward Declarations
 */
struct PACKET;

/*
 * Class Implementations
 */
class MCP2515 final
{
public:
    struct STATUS_FIELD;

    enum class RETURN_CODE : uint8_t
    {
        FAILURE = 0u,
        SUCCESS = 1u,
    }; // class RETURN_CODE

    enum class MODE : uint8_t
    {
        ANY = 0u,
        STDEXT = 1u,
    }; // class MODE

    enum class BAUDRATE : uint8_t
    {
        KHZ_5 = 0u,
        KHZ_10,
        KHZ_20,
        KHZ_31_25,
        KHZ_33_3,
        KHZ_40,
        KHZ_50,
        KHZ_80,
        KHZ_100,
        KHZ_125,
        KHZ_200,
        KHZ_250,
        KHZ_500,
        KHZ_1000
    }; // class BAUDRATE

    enum class EXTERNAL_OSCILLATOR
    {
        INVALID = 0u,
        MHZ_8 = 1u,
        MHZ_16 = 2u,
        MHZ_20 = 3u,
    }; // class EXTERNAL_OSCILLATOR

    using CONFIG = uint32_t;

private:
    uint8_t const my_chip_select_pin;
    BAUDRATE const my_baudrate;
    MODE my_mode;

    static constexpr CONFIG organizeConfigBytes(uint8_t cfg1, uint8_t cfg2, uint8_t cfg3)
    {
        return (cfg1 << 16) | (cfg2 << 8) | (cfg3);
    }

    void resetController();

    uint8_t readRegister(MCP2515_HARDWARE_ADDRESS address);

    void writeRegister(MCP2515_HARDWARE_ADDRESS address, uint8_t data);

    STATUS_FIELD readStatus();

public:
    MCP2515() = delete;
    MCP2515(MCP2515 const &) = delete;
    MCP2515 & operator=(MCP2515 const &) = delete;

    ~MCP2515() = default;

    MCP2515(uint8_t chipSelectPin);

    RETURN_CODE begin(MODE mode, CONFIG baudrate_config);

    RETURN_CODE setMode(MODE mode);

    void sendMessage(PACKET const &);

    RETURN_CODE readMessage(PACKET &);

    // TODO: Fill in the rest of these
    static constexpr CONFIG getBaudrateConfiguration(MCP2515::EXTERNAL_OSCILLATOR const oscillatorFrequency,
                                                     MCP2515::BAUDRATE const baud)
    {
        switch (oscillatorFrequency)
        {
            case EXTERNAL_OSCILLATOR::MHZ_8:
                break;
            case EXTERNAL_OSCILLATOR::MHZ_16:
                switch (baud)
                {
                    case BAUDRATE::KHZ_100:
                        return organizeConfigBytes(0x03, 0xFA, 0x87);
                    case BAUDRATE::KHZ_250:
                        return organizeConfigBytes(0x41, 0xF1, 0x85);
                    case BAUDRATE::KHZ_500:
                        return organizeConfigBytes(0x00, 0xF0, 0x86);
                    case BAUDRATE::KHZ_1000:
                        return organizeConfigBytes(0x00, 0xD0, 0x82);
                    default:
                        break;
                }
                break;
            case EXTERNAL_OSCILLATOR::MHZ_20:
                break;
            default:
                break;

                return 0ul;
        }
    }

}; // class MCP2515

} // namespace CAN

#endif // MCP2515_H_
