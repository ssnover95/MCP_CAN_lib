/*
  mcp_can.h
  2012 Copyright (c) Seeed Technology Inc.  All right reserved.
  2016 Copyright (c) Cory J. Fowler  All Rights Reserved.
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

#include "mcp_can_dfs.h"
#define MAX_CHAR_IN_MESSAGE 8

namespace CAN
{

// Forward declaration
struct PACKET;

class MCP2515 final
{
public:

    enum class RETURN_CODE : uint8_t
    {
        FAILURE     = 0u,
        SUCCESS     = 1u,
    }; // class RETURN_CODE

    enum class MODE : uint8_t
    {
        INIT    = 0u,
        NORMAL  = 1u,
        SLEEP   = 2u,
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
        MHZ_8   = 1u,
        MHZ_16  = 2u,
        MHZ_20  = 3u,
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

public:

    MCP2515() = delete;
    MCP2515(MCP2515 const &) = delete;
    MCP2515 & operator=(MCP2515 const &) = delete;

    ~MCP2515() = default;

    MCP2515(uint8_t chipSelectPin);

    RETURN_CODE begin(MODE mode, BAUDRATE baud, EXTERNAL_OSCILLATOR extOsc);

    RETURN_CODE setMode(MODE mode);

    void sendMessage(PACKET const &);

    RETURN_CODE readMessage(PACKET &);

    //TODO: Fill in the rest of these
    static constexpr CONFIG getBaudrateConfiguration(MCP2515::EXTERNAL_OSCILLATOR const oscillatorFrequency, MCP2515::BAUDRATE const baud)
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

class MCP_CAN
{
    private:
    
    INT8U   m_nExtFlg;                                                  // Identifier Type
                                                                        // Extended (29 bit) or Standard (11 bit)
    INT32U  m_nID;                                                      // CAN ID
    INT8U   m_nDlc;                                                     // Data Length Code
    INT8U   m_nDta[MAX_CHAR_IN_MESSAGE];                            	// Data array
    INT8U   m_nRtr;                                                     // Remote request flag
    INT8U   m_nfilhit;                                                  // The number of the filter that matched the message
    INT8U   MCPCS;                                                      // Chip Select pin number
    INT8U   mcpMode;                                                    // Mode to return to after configurations are performed.
    

/*********************************************************************************************************
 *  mcp2515 driver function 
 *********************************************************************************************************/
   // private:
   private:

    void mcp2515_reset(void);                                           // Soft Reset MCP2515

    INT8U mcp2515_readRegister(const INT8U address);                    // Read MCP2515 register
    
    void mcp2515_readRegisterS(const INT8U address,                     // Read MCP2515 successive registers
	                             INT8U values[], 
                               const INT8U n);
   
    void mcp2515_setRegister(const INT8U address,                       // Set MCP2515 register
                             const INT8U value);

    void mcp2515_setRegisterS(const INT8U address,                      // Set MCP2515 successive registers
                              const INT8U values[],
                              const INT8U n);
    
    void mcp2515_initCANBuffers(void);
    
    void mcp2515_modifyRegister(const INT8U address,                    // Set specific bit(s) of a register
                                const INT8U mask,
                                const INT8U data);

    INT8U mcp2515_readStatus(void);                                     // Read MCP2515 Status
    INT8U mcp2515_setCANCTRL_Mode(const INT8U newmode);                 // Set mode
    INT8U mcp2515_configRate(const INT8U canSpeed,                      // Set baudrate
                             const INT8U canClock);
                             
    INT8U mcp2515_init(const INT8U canIDMode,                           // Initialize Controller
                       const INT8U canSpeed,
                       const INT8U canClock);
		       
    void mcp2515_write_mf( const INT8U mcp_addr,                        // Write CAN Mask or Filter
                           const INT8U ext,
                           const INT32U id );
			       
    void mcp2515_write_id( const INT8U mcp_addr,                        // Write CAN ID
                           const INT8U ext,
                           const INT32U id );

    void mcp2515_read_id( const INT8U mcp_addr,                         // Read CAN ID
				INT8U* ext,
                                INT32U* id );

    void mcp2515_write_canMsg( const INT8U buffer_sidh_addr );          // Write CAN message
    void mcp2515_read_canMsg( const INT8U buffer_sidh_addr);            // Read CAN message
    INT8U mcp2515_getNextFreeTXBuf(INT8U *txbuf_n);                     // Find empty transmit buffer

/*********************************************************************************************************
 *  CAN operator function
 *********************************************************************************************************/

    INT8U setMsg(INT32U id, INT8U rtr, INT8U ext, INT8U len, INT8U *pData);        // Set message
    INT8U clearMsg();                                                   // Clear all message to zero
    INT8U readMsg();                                                    // Read message
    INT8U sendMsg();                                                    // Send message

public:
    MCP_CAN(INT8U _CS);
    INT8U begin(INT8U idmodeset, INT8U speedset, INT8U clockset);       // Initilize controller prameters
    INT8U init_Mask(INT8U num, INT8U ext, INT32U ulData);               // Initilize Mask(s)
    INT8U init_Mask(INT8U num, INT32U ulData);                          // Initilize Mask(s)
    INT8U init_Filt(INT8U num, INT8U ext, INT32U ulData);               // Initilize Filter(s)
    INT8U init_Filt(INT8U num, INT32U ulData);                          // Initilize Filter(s)
    INT8U setMode(INT8U opMode);                                        // Set operational mode
    INT8U sendMsgBuf(INT32U id, INT8U ext, INT8U len, INT8U *buf);      // Send message to transmit buffer
    INT8U sendMsgBuf(INT32U id, INT8U len, INT8U *buf);                 // Send message to transmit buffer
    INT8U readMsgBuf(INT32U *id, INT8U *ext, INT8U *len, INT8U *buf);   // Read message from receive buffer
    INT8U readMsgBuf(INT32U *id, INT8U *len, INT8U *buf);               // Read message from receive buffer
    INT8U checkReceive(void);                                           // Check for received data
    INT8U checkError(void);                                             // Check for errors
    INT8U getError(void);                                               // Check for errors
    INT8U errorCountRX(void);                                           // Get error count
    INT8U errorCountTX(void);                                           // Get error count
    INT8U enOneShotTX(void);                                            // Enable one-shot transmission
    INT8U disOneShotTX(void);                                           // Disable one-shot transmission
};

#endif
/*********************************************************************************************************
 *  END FILE
 *********************************************************************************************************/
