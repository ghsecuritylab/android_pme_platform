

/*
  This file is part of Valgrind, a dynamic binary instrumentation
  framework.

  Copyright (C) 2010-2013 Tilera Corp.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307, USA.

  The GNU General Public License is contained in the file COPYING.
*/


#ifndef __VKI_TILEGX_LINUX_H
#define __VKI_TILEGX_LINUX_H

#define VKI_LITTLE_ENDIAN  1


typedef unsigned char __vki_u8;

typedef __signed__ short __vki_s16;
typedef unsigned short __vki_u16;

typedef __signed__ int __vki_s32;
typedef unsigned int __vki_u32;

typedef __signed__ long long __vki_s64;
typedef unsigned long long __vki_u64;

typedef unsigned short vki_u16;

typedef unsigned int vki_u32;


#define VKI_PAGE_SHIFT       16
#define VKI_PAGE_SIZE       (1UL << VKI_PAGE_SHIFT)
#define VKI_MAX_PAGE_SHIFT       VKI_PAGE_SHIFT
#define VKI_MAX_PAGE_SIZE       VKI_PAGE_SIZE


#define VKI_SHMLBA  VKI_PAGE_SIZE


#define _VKI_NSIG       64
#define _VKI_NSIG_BPW       64
#define _VKI_NSIG_WORDS       (_VKI_NSIG / _VKI_NSIG_BPW)

typedef unsigned long vki_old_sigset_t;

typedef struct {
  unsigned long sig[_VKI_NSIG_WORDS];
} vki_sigset_t;

#define VKI_SIGHUP               1
#define VKI_SIGINT               2
#define VKI_SIGQUIT              3
#define VKI_SIGILL               4
#define VKI_SIGTRAP              5
#define VKI_SIGABRT              6
#define VKI_SIGIOT               6
#define VKI_SIGBUS               7
#define VKI_SIGFPE               8
#define VKI_SIGKILL              9
#define VKI_SIGUSR1              10
#define VKI_SIGSEGV              11
#define VKI_SIGUSR2              12
#define VKI_SIGPIPE              13
#define VKI_SIGALRM              14
#define VKI_SIGTERM              15
#define VKI_SIGSTKFLT            16
#define VKI_SIGCHLD              17
#define VKI_SIGCONT              18
#define VKI_SIGSTOP              19
#define VKI_SIGTSTP              20
#define VKI_SIGTTIN              21
#define VKI_SIGTTOU              22
#define VKI_SIGURG               23
#define VKI_SIGXCPU              24
#define VKI_SIGXFSZ              25
#define VKI_SIGVTALRM            26
#define VKI_SIGPROF              27
#define VKI_SIGWINCH             28
#define VKI_SIGIO                29
#define VKI_SIGPOLL              29
#define VKI_SIGPWR               30
#define VKI_SIGSYS               31
#define VKI_SIGUNUSED            31

#define VKI_SIGRTMIN             32
#define VKI_SIGRTMAX            _VKI_NSIG

#define VKI_SA_NOCLDSTOP        0x00000001
#define VKI_SA_NOCLDWAIT        0x00000002
#define VKI_SA_SIGINFO          0x00000004
#define VKI_SA_ONSTACK          0x08000000
#define VKI_SA_RESTART          0x10000000
#define VKI_SA_NODEFER          0x40000000
#define VKI_SA_RESETHAND        0x80000000

#define VKI_SA_NOMASK           VKI_SA_NODEFER
#define VKI_SA_ONESHOT          VKI_SA_RESETHAND

#define VKI_SA_RESTORER         0x04000000

#define VKI_SS_ONSTACK          1
#define VKI_SS_DISABLE          2

#define VKI_MINSIGSTKSZ         2048

#define VKI_SIG_BLOCK           0       
#define VKI_SIG_UNBLOCK         1       
#define VKI_SIG_SETMASK         2       

typedef void __vki_signalfn_t(int);
typedef __vki_signalfn_t __user *__vki_sighandler_t;

typedef void __vki_restorefn_t(void);
typedef __vki_restorefn_t __user *__vki_sigrestore_t;

#define VKI_SIG_DFL       ((__vki_sighandler_t)0)       
#define VKI_SIG_IGN       ((__vki_sighandler_t)1)       

struct vki_sigaction_base {
  
  
  
  
  __vki_sighandler_t ksa_handler;
  unsigned long sa_flags;
  __vki_sigrestore_t sa_restorer;
  vki_sigset_t sa_mask;              
};

typedef  struct vki_sigaction_base  vki_sigaction_toK_t;
typedef  struct vki_sigaction_base  vki_sigaction_fromK_t;


typedef struct vki_sigaltstack {
  void __user *ss_sp;
  int ss_flags;
  vki_size_t ss_size;
} vki_stack_t;


struct _vki_fpstate {

};

struct vki_sigcontext {
  unsigned long gregs[53];
  unsigned long tp;
  unsigned long sp;
  unsigned long lr;
  unsigned long pc;
  unsigned long ics;
  unsigned long faultnum;
  unsigned long pad[5];
};


#define VKI_PROT_READ       0x1              
#define VKI_PROT_WRITE      0x2              /* page can be written */
#define VKI_PROT_EXEC       0x4              
#define VKI_PROT_NONE       0x0              
#define VKI_PROT_GROWSDOWN  0x01000000       
#define VKI_PROT_GROWSUP    0x02000000       

#define VKI_MAP_SHARED      0x01              
#define VKI_MAP_PRIVATE     0x02              
#define VKI_MAP_FIXED       0x10              
#define VKI_MAP_ANONYMOUS   0x20              
#define VKI_MAP_HUGETLB     0x4000            


#define VKI_O_RDONLY          00
#define VKI_O_WRONLY          01
#define VKI_O_RDWR            02
#define VKI_O_ACCMODE         03
#define VKI_O_CREAT           0100       
#define VKI_O_EXCL            0200       
#define VKI_O_TRUNC           01000      
#define VKI_O_APPEND          02000
#define VKI_O_NONBLOCK        04000
#define VKI_O_LARGEFILE       0100000

#define VKI_AT_FDCWD            -100

#define VKI_F_DUPFD              0       
#define VKI_F_GETFD              1       
#define VKI_F_SETFD              2       
#define VKI_F_GETFL              3       
#define VKI_F_SETFL              4       
#define VKI_F_GETLK              5
#define VKI_F_SETLK              6
#define VKI_F_SETLKW             7

#define VKI_F_SETOWN             8       
#define VKI_F_GETOWN             9       
#define VKI_F_SETSIG             10       
#define VKI_F_GETSIG             11       

#define VKI_F_SETOWN_EX          15
#define VKI_F_GETOWN_EX          16
#define VKI_F_GETLK64            12
#define VKI_F_SETLK64            13
#define VKI_F_SETLKW64           14

#define VKI_F_OFD_GETLK          -1
#define VKI_F_OFD_SETLK          -2
#define VKI_F_OFD_SETLKW         -3

#define VKI_FD_CLOEXEC      1       

#define VKI_F_LINUX_SPECIFIC_BASE       1024

struct vki_f_owner_ex {
  int type;
  __vki_kernel_pid_t pid;
};


#define VKI_RLIMIT_DATA        2       
#define VKI_RLIMIT_STACK       3       
#define VKI_RLIMIT_CORE        4       
#define VKI_RLIMIT_NOFILE      7       


#define VKI_SOL_SOCKET         1
#define VKI_SO_TYPE            3
#define VKI_SO_ATTACH_FILTER   26


#define VKI_SIOCSPGRP          0x8902
#define VKI_SIOCGPGRP          0x8904
#define VKI_SIOCATMARK         0x8905
#define VKI_SIOCGSTAMP         0x8906              
#define VKI_SIOCGSTAMPNS       0x8907              


struct vki_stat {
  unsigned long      st_dev;        
  unsigned long      st_ino;        
  unsigned int       st_mode;       
  unsigned int       st_nlink;      
  unsigned int       st_uid;        
  unsigned int       st_gid;        
  unsigned long      st_rdev;       
  unsigned long      __pad1;
  long               st_size;       
  int                st_blksize;    
  int                __pad2;
  long               st_blocks;     
  long               st_atime;      
  unsigned long      st_atime_nsec;
  long               st_mtime;      
  unsigned long      st_mtime_nsec;
  long               st_ctime;      
  unsigned long      st_ctime_nsec;
  unsigned int       __unused4;
  unsigned int       __unused5;
};

struct vki_stat64 {
  unsigned long      st_dev;        
  unsigned long      st_ino;        
  unsigned int       st_mode;       
  unsigned int       st_nlink;      
  unsigned int       st_uid;        
  unsigned int       st_gid;        
  unsigned long      st_rdev;       
  unsigned long      __pad1;
  long               st_size;       
  int                st_blksize;    
  int                __pad2;
  long               st_blocks;     
  long               st_atime;      
  unsigned long      st_atime_nsec;
  long               st_mtime;      
  unsigned long      st_mtime_nsec;
  long               st_ctime;      
  unsigned long      st_ctime_nsec;
  unsigned int       __unused4;
  unsigned int       __unused5;
};


struct vki_statfs {
  long f_type;
  long f_bsize;
  long f_blocks;
  long f_bfree;
  long f_bavail;
  long f_files;
  long f_ffree;
  __vki_kernel_fsid_t f_fsid;
  long f_namelen;
  long f_frsize;
  long f_flags;
  long f_spare[4];
};


struct vki_winsize {
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

#define VKI_NCC 8
struct vki_termio {
  unsigned short c_iflag;            
  unsigned short c_oflag;            
  unsigned short c_cflag;            
  unsigned short c_lflag;            
  unsigned char c_line;              
  unsigned char c_cc[VKI_NCC];       
};


typedef unsigned char       vki_cc_t;
typedef unsigned int        vki_tcflag_t;

#define VKI_NCCS 19
struct vki_termios {
  vki_tcflag_t c_iflag;              
  vki_tcflag_t c_oflag;              
  vki_tcflag_t c_cflag;              
  vki_tcflag_t c_lflag;              
  vki_cc_t c_line;                   
  vki_cc_t c_cc[VKI_NCCS];           
};



#define _VKI_IOC_NRBITS              8
#define _VKI_IOC_TYPEBITS            8
#define _VKI_IOC_SIZEBITS           14
#define _VKI_IOC_DIRBITS             2

#define _VKI_IOC_SIZEMASK      ((1 << _VKI_IOC_SIZEBITS)-1)
#define _VKI_IOC_DIRMASK       ((1 << _VKI_IOC_DIRBITS)-1)

#define _VKI_IOC_NRSHIFT         0
#define _VKI_IOC_TYPESHIFT       (_VKI_IOC_NRSHIFT+_VKI_IOC_NRBITS)
#define _VKI_IOC_SIZESHIFT       (_VKI_IOC_TYPESHIFT+_VKI_IOC_TYPEBITS)
#define _VKI_IOC_DIRSHIFT        (_VKI_IOC_SIZESHIFT+_VKI_IOC_SIZEBITS)

#define _VKI_IOC_NONE            0U
#define _VKI_IOC_WRITE           1U
#define _VKI_IOC_READ            2U

#define _VKI_IOC(dir,type,nr,size)              \
  (((dir)  << _VKI_IOC_DIRSHIFT) |              \
   ((type) << _VKI_IOC_TYPESHIFT) |             \
   ((nr)   << _VKI_IOC_NRSHIFT) |               \
   ((size) << _VKI_IOC_SIZESHIFT))

#define _VKI_IO(type,nr)        _VKI_IOC(_VKI_IOC_NONE,(type),(nr),0)
#define _VKI_IOR(type,nr,size)  _VKI_IOC(_VKI_IOC_READ,(type),(nr),sizeof(size))
#define _VKI_IOW(type,nr,size)  _VKI_IOC(_VKI_IOC_WRITE,(type),(nr),sizeof(size))
#define _VKI_IOWR(type,nr,size) _VKI_IOC(_VKI_IOC_READ|_VKI_IOC_WRITE,(type),(nr),sizeof(size))

#define _VKI_IOC_DIR(nr)     (((nr) >> _VKI_IOC_DIRSHIFT) & _VKI_IOC_DIRMASK)
#define _VKI_IOC_SIZE(nr)    (((nr) >> _VKI_IOC_SIZESHIFT) & _VKI_IOC_SIZEMASK)


#define VKI_TCGETS         0x5401
#define VKI_TCSETS         0x5402
#define VKI_TCSETSW        0x5403
#define VKI_TCSETSF        0x5404
#define VKI_TCGETA         0x5405
#define VKI_TCSETA         0x5406
#define VKI_TCSETAW        0x5407
#define VKI_TCSETAF        0x5408
#define VKI_TCSBRK         0x5409
#define VKI_TCXONC         0x540A
#define VKI_TCFLSH         0x540B
#define VKI_TIOCEXCL       0x540C
#define VKI_TIOCNXCL       0x540D
#define VKI_TIOCSCTTY      0x540E
#define VKI_TIOCGPGRP      0x540F
#define VKI_TIOCSPGRP      0x5410
#define VKI_TIOCOUTQ       0x5411
#define VKI_TIOCSTI        0x5412
#define VKI_TIOCGWINSZ     0x5413
#define VKI_TIOCSWINSZ     0x5414
#define VKI_TIOCMGET       0x5415
#define VKI_TIOCMBIS       0x5416
#define VKI_TIOCMBIC       0x5417
#define VKI_TIOCMSET       0x5418
#define VKI_TIOCGSOFTCAR   0x5419
#define VKI_TIOCSSOFTCAR   0x541A
#define VKI_FIONREAD       0x541B
#define VKI_TIOCINQ        VKI_FIONREAD
#define VKI_TIOCLINUX      0x541C
#define VKI_TIOCCONS       0x541D
#define VKI_TIOCGSERIAL    0x541E
#define VKI_TIOCSSERIAL    0x541F
#define VKI_TIOCPKT        0x5420
#define VKI_FIONBIO        0x5421
#define VKI_TIOCNOTTY      0x5422
#define VKI_TIOCSETD       0x5423
#define VKI_TIOCGETD       0x5424
#define VKI_TCSBRKP        0x5425
#define VKI_TIOCGPTN       _VKI_IOR('T',0x30, unsigned int) 
#define VKI_TIOCSPTLCK     _VKI_IOW('T',0x31, int)  

#define VKI_FIONCLEX       0x5450
#define VKI_FIOCLEX        0x5451
#define VKI_FIOASYNC       0x5452
#define VKI_TIOCSERGETLSR  0x5459 
#define VKI_TIOCGICOUNT    0x545D 


#define VKI_TIOCGPTN       _VKI_IOR('T',0x30, unsigned int) 
#define VKI_TIOCSPTLCK     _VKI_IOW('T',0x31, int)  

#define VKI_FIOASYNC       0x5452
#define VKI_TIOCSERGETLSR  0x5459 
#define VKI_TIOCGICOUNT    0x545D       


#define VKI_POLLIN              0x0001

struct vki_pollfd {
  int fd;
  short events;
  short revents;
};



struct vki_ucontext {
  unsigned long            uc_flags;
  struct vki_ucontext      *uc_link;
  vki_stack_t              uc_stack;
  struct vki_sigcontext    uc_mcontext;
  vki_sigset_t             uc_sigmask;       
};




struct vki_ipc64_perm
{
  __vki_kernel_key_t         key;
  __vki_kernel_uid32_t       uid;
  __vki_kernel_gid32_t       gid;
  __vki_kernel_uid32_t       cuid;
  __vki_kernel_gid32_t       cgid;
  __vki_kernel_mode_t        mode;
  unsigned char              __pad1[4 - sizeof(__vki_kernel_mode_t)];
  unsigned short             seq;
  unsigned short             __pad2;
  unsigned long              __unused1;
  unsigned long              __unused2;
};


struct vki_semid64_ds {
  struct vki_ipc64_perm    sem_perm;              
  __vki_kernel_time_t      sem_otime;              
  __vki_kernel_time_t      sem_ctime;              
  unsigned long            sem_nsems;              
  unsigned long            __unused3;
  unsigned long            __unused4;
};


struct vki_msqid64_ds {
  struct vki_ipc64_perm msg_perm;
  __vki_kernel_time_t   msg_stime;       
  __vki_kernel_time_t   msg_rtime;       
  __vki_kernel_time_t   msg_ctime;       
  unsigned long         msg_cbytes;      
  unsigned long         msg_qnum;        
  unsigned long         msg_qbytes;      
  __vki_kernel_pid_t    msg_lspid;       
  __vki_kernel_pid_t    msg_lrpid;       
  unsigned long         __unused4;
  unsigned long         __unused5;
};


struct vki_shmid64_ds {
  struct vki_ipc64_perm   shm_perm;        
  vki_size_t              shm_segsz;       
  __vki_kernel_time_t     shm_atime;       
  __vki_kernel_time_t     shm_dtime;       
  __vki_kernel_time_t     shm_ctime;       
  __vki_kernel_pid_t      shm_cpid;        
  __vki_kernel_pid_t      shm_lpid;        
  unsigned long           shm_nattch;      
  unsigned long           __unused4;
  unsigned long           __unused5;
};

struct vki_shminfo64 {
  unsigned long       shmmax;
  unsigned long       shmmin;
  unsigned long       shmmni;
  unsigned long       shmseg;
  unsigned long       shmall;
  unsigned long       __unused1;
  unsigned long       __unused2;
  unsigned long       __unused3;
  unsigned long       __unused4;
};


struct vki_pt_regs {

  unsigned long regs[53];
  unsigned long tp;
  unsigned long sp;
  unsigned long lr;
  unsigned long pc;
  unsigned long ex1;
  unsigned long faultnum;
  unsigned long orig_r0;
  unsigned long flags;
  unsigned long pad[3];
};

#ifndef user_pt_regs
#define user_pt_regs  vki_pt_regs
#endif

struct  tilegx_elf_fpregset {};
typedef struct tilegx_elf_fpregset vki_elf_fpregset_t;

#define vki_user_regs_struct vki_pt_regs

#define TILEGX_r56       regs[56]
#define TILEGX_r55       regs[55]
#define TILEGX_r54       regs[54]
#define TILEGX_r53       regs[53]
#define TILEGX_r52       regs[52]
#define TILEGX_r51       regs[51]
#define TILEGX_r50       regs[50]
#define TILEGX_r49       regs[49]
#define TILEGX_r48       regs[48]
#define TILEGX_r47       regs[47]
#define TILEGX_r46       regs[46]
#define TILEGX_r45       regs[45]
#define TILEGX_r44       regs[44]
#define TILEGX_r43       regs[43]
#define TILEGX_r42       regs[42]
#define TILEGX_r41       regs[41]
#define TILEGX_r40       regs[40]
#define TILEGX_r39       regs[39]
#define TILEGX_r38       regs[38]
#define TILEGX_r37       regs[37]
#define TILEGX_r36       regs[36]
#define TILEGX_r35       regs[35]
#define TILEGX_r34       regs[34]
#define TILEGX_r33       regs[33]
#define TILEGX_r32       regs[32]
#define TILEGX_r31       regs[31]
#define TILEGX_r30       regs[30]
#define TILEGX_r29       regs[29]
#define TILEGX_r28       regs[28]
#define TILEGX_r27       regs[27]
#define TILEGX_r26       regs[26]
#define TILEGX_r25       regs[25]
#define TILEGX_r24       regs[24]
#define TILEGX_r23       regs[23]
#define TILEGX_r22       regs[22]
#define TILEGX_r21       regs[21]
#define TILEGX_r20       regs[20]
#define TILEGX_r19       regs[19]
#define TILEGX_r18       regs[18]
#define TILEGX_r17       regs[17]
#define TILEGX_r16       regs[16]
#define TILEGX_r15       regs[15]
#define TILEGX_r14       regs[14]
#define TILEGX_r13       regs[13]
#define TILEGX_r12       regs[12]
#define TILEGX_r11       regs[11]
#define TILEGX_r10       regs[10]
#define TILEGX_r9        regs[9]
#define TILEGX_r8        regs[8]
#define TILEGX_r7        regs[7]
#define TILEGX_r6        regs[6]
#define TILEGX_r5        regs[5]
#define TILEGX_r4        regs[4]
#define TILEGX_r3        regs[3]
#define TILEGX_r2        regs[2]
#define TILEGX_r1        regs[1]
#define TILEGX_r0        regs[0]

#define TILEGX_lr        TILEGX_r55
#define TILEGX_sp        TILEGX_r54
#define TILEGX_tp        TILEGX_r53
#define TILEGX_pc        TILEGX_r56

#define VKI_PTRACE_GETREGS            12
#define VKI_PTRACE_SETREGS            13
#define VKI_PTRACE_GETFPREGS          14
#define VKI_PTRACE_SETFPREGS          15



typedef unsigned long vki_elf_greg_t;

#define VKI_ELF_NGREG (sizeof (struct vki_user_regs_struct) / sizeof(vki_elf_greg_t))
typedef vki_elf_greg_t vki_elf_gregset_t[VKI_ELF_NGREG];


struct tilegx_dirent64 {
  long              d_ino;
  long              d_off;
  unsigned short    d_reclen;
  unsigned char     d_type;
  char              d_name[256];
};


#define       VKI_ENOSYS       38  
#define       VKI_EOVERFLOW    75  


#endif 

