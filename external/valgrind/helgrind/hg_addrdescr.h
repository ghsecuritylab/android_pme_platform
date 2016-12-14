

/*
   This file is part of Helgrind, a Valgrind tool for detecting errors
   in threaded programs.

   Copyright (C) 2007-2012 OpenWorks Ltd
      info@open-works.co.uk

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

#ifndef __HG_ADDRDESCR_H
#define __HG_ADDRDESCR_H

extern void HG_(describe_addr) ( Addr a, AddrInfo* ai );

extern Bool HG_(get_and_pp_addrdescr) (Addr a);

Bool HG_(mm_find_containing_block)( ExeContext** where,
                                    UInt*        tnr,
                                    Addr*        payload,
                                    SizeT*       szB,
                                    Addr                data_addr );


#endif 

