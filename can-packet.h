/*
 * can-packet.h
 * 2018 Copyright (c) Shane Snover           All rights reserved.

 * Author:Loovee
 * Contributor: Cory J. Fowler
 * Contributor: Shane Snover
 * 2018-06-26
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

#ifndef CAN_PACKET_H_
#define CAN_PACKET_H_

#include "stdint.h"

namespace CAN
{

struct PACKET final
{
    uint16_t my_id;
    uint8_t my_dlc;
    uint8_t * my_payload;
}; // struct PACKET

} // namespace CAN

#endif // CAN_PACKET_H_