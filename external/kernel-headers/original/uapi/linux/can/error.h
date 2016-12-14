/*
 * linux/can/error.h
 *
 * Definitions of the CAN error messages to be filtered and passed to the user.
 *
 * Author: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which case the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data structures and external interfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef _UAPI_CAN_ERROR_H
#define _UAPI_CAN_ERROR_H

#define CAN_ERR_DLC 8 

#define CAN_ERR_TX_TIMEOUT   0x00000001U 
#define CAN_ERR_LOSTARB      0x00000002U 
#define CAN_ERR_CRTL         0x00000004U 
#define CAN_ERR_PROT         0x00000008U 
#define CAN_ERR_TRX          0x00000010U 
#define CAN_ERR_ACK          0x00000020U 
#define CAN_ERR_BUSOFF       0x00000040U 
#define CAN_ERR_BUSERROR     0x00000080U 
#define CAN_ERR_RESTARTED    0x00000100U 

#define CAN_ERR_LOSTARB_UNSPEC   0x00 
				      

#define CAN_ERR_CRTL_UNSPEC      0x00 
#define CAN_ERR_CRTL_RX_OVERFLOW 0x01 
#define CAN_ERR_CRTL_TX_OVERFLOW 0x02 
#define CAN_ERR_CRTL_RX_WARNING  0x04 
#define CAN_ERR_CRTL_TX_WARNING  0x08 
#define CAN_ERR_CRTL_RX_PASSIVE  0x10 
#define CAN_ERR_CRTL_TX_PASSIVE  0x20 
				      
				      

#define CAN_ERR_PROT_UNSPEC      0x00 
#define CAN_ERR_PROT_BIT         0x01 
#define CAN_ERR_PROT_FORM        0x02 
#define CAN_ERR_PROT_STUFF       0x04 
#define CAN_ERR_PROT_BIT0        0x08 
#define CAN_ERR_PROT_BIT1        0x10 
#define CAN_ERR_PROT_OVERLOAD    0x20 
#define CAN_ERR_PROT_ACTIVE      0x40 
#define CAN_ERR_PROT_TX          0x80 

#define CAN_ERR_PROT_LOC_UNSPEC  0x00 
#define CAN_ERR_PROT_LOC_SOF     0x03 
#define CAN_ERR_PROT_LOC_ID28_21 0x02 
#define CAN_ERR_PROT_LOC_ID20_18 0x06 
#define CAN_ERR_PROT_LOC_SRTR    0x04 
#define CAN_ERR_PROT_LOC_IDE     0x05 
#define CAN_ERR_PROT_LOC_ID17_13 0x07 
#define CAN_ERR_PROT_LOC_ID12_05 0x0F 
#define CAN_ERR_PROT_LOC_ID04_00 0x0E 
#define CAN_ERR_PROT_LOC_RTR     0x0C 
#define CAN_ERR_PROT_LOC_RES1    0x0D 
#define CAN_ERR_PROT_LOC_RES0    0x09 
#define CAN_ERR_PROT_LOC_DLC     0x0B 
#define CAN_ERR_PROT_LOC_DATA    0x0A 
#define CAN_ERR_PROT_LOC_CRC_SEQ 0x08 
#define CAN_ERR_PROT_LOC_CRC_DEL 0x18 
#define CAN_ERR_PROT_LOC_ACK     0x19 
#define CAN_ERR_PROT_LOC_ACK_DEL 0x1B 
#define CAN_ERR_PROT_LOC_EOF     0x1A 
#define CAN_ERR_PROT_LOC_INTERM  0x12 

#define CAN_ERR_TRX_UNSPEC             0x00 
#define CAN_ERR_TRX_CANH_NO_WIRE       0x04 
#define CAN_ERR_TRX_CANH_SHORT_TO_BAT  0x05 
#define CAN_ERR_TRX_CANH_SHORT_TO_VCC  0x06 
#define CAN_ERR_TRX_CANH_SHORT_TO_GND  0x07 
#define CAN_ERR_TRX_CANL_NO_WIRE       0x40 
#define CAN_ERR_TRX_CANL_SHORT_TO_BAT  0x50 
#define CAN_ERR_TRX_CANL_SHORT_TO_VCC  0x60 
#define CAN_ERR_TRX_CANL_SHORT_TO_GND  0x70 
#define CAN_ERR_TRX_CANL_SHORT_TO_CANH 0x80 


#endif 
