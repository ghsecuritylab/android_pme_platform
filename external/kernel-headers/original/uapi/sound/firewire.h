#ifndef _UAPI_SOUND_FIREWIRE_H_INCLUDED
#define _UAPI_SOUND_FIREWIRE_H_INCLUDED

#include <linux/ioctl.h>
#include <linux/types.h>


#define SNDRV_FIREWIRE_EVENT_LOCK_STATUS	0x000010cc
#define SNDRV_FIREWIRE_EVENT_DICE_NOTIFICATION	0xd1ce004e
#define SNDRV_FIREWIRE_EVENT_EFW_RESPONSE	0x4e617475

struct snd_firewire_event_common {
	unsigned int type; 
};

struct snd_firewire_event_lock_status {
	unsigned int type;
	unsigned int status; 
};

struct snd_firewire_event_dice_notification {
	unsigned int type;
	unsigned int notification; 
};

#define SND_EFW_TRANSACTION_USER_SEQNUM_MAX	((__u32)((__u16)~0) - 1)
struct snd_efw_transaction {
	__be32 length;
	__be32 version;
	__be32 seqnum;
	__be32 category;
	__be32 command;
	__be32 status;
	__be32 params[0];
};
struct snd_firewire_event_efw_response {
	unsigned int type;
	__be32 response[0];	
};

union snd_firewire_event {
	struct snd_firewire_event_common            common;
	struct snd_firewire_event_lock_status       lock_status;
	struct snd_firewire_event_dice_notification dice_notification;
	struct snd_firewire_event_efw_response      efw_response;
};


#define SNDRV_FIREWIRE_IOCTL_GET_INFO _IOR('H', 0xf8, struct snd_firewire_get_info)
#define SNDRV_FIREWIRE_IOCTL_LOCK      _IO('H', 0xf9)
#define SNDRV_FIREWIRE_IOCTL_UNLOCK    _IO('H', 0xfa)

#define SNDRV_FIREWIRE_TYPE_DICE	1
#define SNDRV_FIREWIRE_TYPE_FIREWORKS	2
#define SNDRV_FIREWIRE_TYPE_BEBOB	3

struct snd_firewire_get_info {
	unsigned int type; 
	unsigned int card; 
	unsigned char guid[8];
	char device_name[16]; 
};


#endif 
