/*
 *  BSD Process Accounting for Linux - Definitions
 *
 *  Author: Marco van Wieringen (mvw@planets.elm.net)
 *
 *  This header file contains the definitions needed to implement
 *  BSD-style process accounting. The kernel accounting code and all
 *  user-level programs that try to do something useful with the
 *  process accounting log must include this file.
 *
 *  Copyright (C) 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.
 *
 */

#ifndef _UAPI_LINUX_ACCT_H
#define _UAPI_LINUX_ACCT_H

#include <linux/types.h>

#include <asm/param.h>
#include <asm/byteorder.h>


typedef __u16	comp_t;
typedef __u32	comp2_t;

/*
 *   accounting file record
 *
 *   This structure contains all of the information written out to the
 *   process accounting file whenever a process exits.
 */

#define ACCT_COMM	16

struct acct
{
	char		ac_flag;		
	char		ac_version;		
	
	__u16		ac_uid16;		
	__u16		ac_gid16;		
	__u16		ac_tty;			
	__u32		ac_btime;		
	comp_t		ac_utime;		
	comp_t		ac_stime;		
	comp_t		ac_etime;		
	comp_t		ac_mem;			
	comp_t		ac_io;			
	comp_t		ac_rw;			/* Blocks Read or Written */
	comp_t		ac_minflt;		
	comp_t		ac_majflt;		
	comp_t		ac_swaps;		
#if !defined(CONFIG_M68K) || !defined(__KERNEL__)
	__u16		ac_ahz;			
#endif
	__u32		ac_exitcode;		
	char		ac_comm[ACCT_COMM + 1];	
	__u8		ac_etime_hi;		
	__u16		ac_etime_lo;		
	__u32		ac_uid;			
	__u32		ac_gid;			
};

struct acct_v3
{
	char		ac_flag;		
	char		ac_version;		
	__u16		ac_tty;			
	__u32		ac_exitcode;		
	__u32		ac_uid;			
	__u32		ac_gid;			
	__u32		ac_pid;			
	__u32		ac_ppid;		
	__u32		ac_btime;		
#ifdef __KERNEL__
	__u32		ac_etime;		
#else
	float		ac_etime;		
#endif
	comp_t		ac_utime;		
	comp_t		ac_stime;		
	comp_t		ac_mem;			
	comp_t		ac_io;			
	comp_t		ac_rw;			/* Blocks Read or Written */
	comp_t		ac_minflt;		
	comp_t		ac_majflt;		
	comp_t		ac_swaps;		
	char		ac_comm[ACCT_COMM];	
};

				
#define AFORK		0x01	
#define ASU		0x02	
#define ACOMPAT		0x04	
#define ACORE		0x08	
#define AXSIG		0x10	

#if defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
#define ACCT_BYTEORDER	0x80	
#elif defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
#define ACCT_BYTEORDER	0x00	
#else
#error unspecified endianness
#endif

#ifndef __KERNEL__
#define ACCT_VERSION	2
#define AHZ		(HZ)
#endif	


#endif 
