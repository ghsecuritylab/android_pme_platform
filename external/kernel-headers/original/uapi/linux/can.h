/*
 * linux/can.h
 *
 * Definitions for CAN network layer (socket addr / CAN frame / CAN filter)
 *
 * Authors: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 *          Urs Thuermann   <urs.thuermann@volkswagen.de>
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

#ifndef _UAPI_CAN_H
#define _UAPI_CAN_H

#include <linux/types.h>
#include <linux/socket.h>


#define CAN_EFF_FLAG 0x80000000U 
#define CAN_RTR_FLAG 0x40000000U 
#define CAN_ERR_FLAG 0x20000000U 

#define CAN_SFF_MASK 0x000007FFU 
#define CAN_EFF_MASK 0x1FFFFFFFU 
#define CAN_ERR_MASK 0x1FFFFFFFU 

typedef __u32 canid_t;

#define CAN_SFF_ID_BITS		11
#define CAN_EFF_ID_BITS		29

typedef __u32 can_err_mask_t;

#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

#define CANFD_MAX_DLC 15
#define CANFD_MAX_DLEN 64

struct can_frame {
	canid_t can_id;  
	__u8    can_dlc; 
	__u8    data[CAN_MAX_DLEN] __attribute__((aligned(8)));
};

#define CANFD_BRS 0x01 
#define CANFD_ESI 0x02 

struct canfd_frame {
	canid_t can_id;  
	__u8    len;     
	__u8    flags;   
	__u8    __res0;  
	__u8    __res1;  
	__u8    data[CANFD_MAX_DLEN] __attribute__((aligned(8)));
};

#define CAN_MTU		(sizeof(struct can_frame))
#define CANFD_MTU	(sizeof(struct canfd_frame))

#define CAN_RAW		1 
#define CAN_BCM		2 
#define CAN_TP16	3 
#define CAN_TP20	4 
#define CAN_MCNET	5 
#define CAN_ISOTP	6 
#define CAN_NPROTO	7

#define SOL_CAN_BASE 100

struct sockaddr_can {
	__kernel_sa_family_t can_family;
	int         can_ifindex;
	union {
		
		struct { canid_t rx_id, tx_id; } tp;

		
	} can_addr;
};

struct can_filter {
	canid_t can_id;
	canid_t can_mask;
};

#define CAN_INV_FILTER 0x20000000U 

#endif 
