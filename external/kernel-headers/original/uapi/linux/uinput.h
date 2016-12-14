/*
 *  User level driver support for input subsystem
 *
 * Heavily based on evdev.c by Vojtech Pavlik
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Author: Aristeu Sergio Rozanski Filho <aris@cathedrallabs.org>
 *
 * Changes/Revisions:
 *	0.4	01/09/2014 (Benjamin Tissoires <benjamin.tissoires@redhat.com>)
 *		- add UI_GET_SYSNAME ioctl
 *	0.3	24/05/2006 (Anssi Hannula <anssi.hannulagmail.com>)
 *		- update ff support for the changes in kernel interface
 *		- add UINPUT_VERSION
 *	0.2	16/10/2004 (Micah Dowty <micah@navi.cx>)
 *		- added force feedback support
 *             - added UI_SET_PHYS
 *	0.1	20/06/2002
 *		- first public version
 */
#ifndef _UAPI__UINPUT_H_
#define _UAPI__UINPUT_H_

#include <linux/types.h>
#include <linux/input.h>

#define UINPUT_VERSION		4


struct uinput_ff_upload {
	__u32			request_id;
	__s32			retval;
	struct ff_effect	effect;
	struct ff_effect	old;
};

struct uinput_ff_erase {
	__u32			request_id;
	__s32			retval;
	__u32			effect_id;
};

#define UINPUT_IOCTL_BASE	'U'
#define UI_DEV_CREATE		_IO(UINPUT_IOCTL_BASE, 1)
#define UI_DEV_DESTROY		_IO(UINPUT_IOCTL_BASE, 2)

#define UI_SET_EVBIT		_IOW(UINPUT_IOCTL_BASE, 100, int)
#define UI_SET_KEYBIT		_IOW(UINPUT_IOCTL_BASE, 101, int)
#define UI_SET_RELBIT		_IOW(UINPUT_IOCTL_BASE, 102, int)
#define UI_SET_ABSBIT		_IOW(UINPUT_IOCTL_BASE, 103, int)
#define UI_SET_MSCBIT		_IOW(UINPUT_IOCTL_BASE, 104, int)
#define UI_SET_LEDBIT		_IOW(UINPUT_IOCTL_BASE, 105, int)
#define UI_SET_SNDBIT		_IOW(UINPUT_IOCTL_BASE, 106, int)
#define UI_SET_FFBIT		_IOW(UINPUT_IOCTL_BASE, 107, int)
#define UI_SET_PHYS		_IOW(UINPUT_IOCTL_BASE, 108, char*)
#define UI_SET_SWBIT		_IOW(UINPUT_IOCTL_BASE, 109, int)
#define UI_SET_PROPBIT		_IOW(UINPUT_IOCTL_BASE, 110, int)

#define UI_BEGIN_FF_UPLOAD	_IOWR(UINPUT_IOCTL_BASE, 200, struct uinput_ff_upload)
#define UI_END_FF_UPLOAD	_IOW(UINPUT_IOCTL_BASE, 201, struct uinput_ff_upload)
#define UI_BEGIN_FF_ERASE	_IOWR(UINPUT_IOCTL_BASE, 202, struct uinput_ff_erase)
#define UI_END_FF_ERASE		_IOW(UINPUT_IOCTL_BASE, 203, struct uinput_ff_erase)

#define UI_GET_SYSNAME(len)	_IOC(_IOC_READ, UINPUT_IOCTL_BASE, 300, len)

#define UI_GET_VERSION		_IOR(UINPUT_IOCTL_BASE, 301, unsigned int)


#define EV_UINPUT		0x0101
#define UI_FF_UPLOAD		1
#define UI_FF_ERASE		2

#define UINPUT_MAX_NAME_SIZE	80
struct uinput_user_dev {
	char name[UINPUT_MAX_NAME_SIZE];
	struct input_id id;
	__u32 ff_effects_max;
	__s32 absmax[ABS_CNT];
	__s32 absmin[ABS_CNT];
	__s32 absfuzz[ABS_CNT];
	__s32 absflat[ABS_CNT];
};
#endif 
