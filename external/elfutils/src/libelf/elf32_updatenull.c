/* Update data structures for changes.
   Copyright (C) 2000-2010 Red Hat, Inc.
   This file is part of elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2000.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <assert.h>
#include <endian.h>
#include <libelf.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>

#include "libelfP.h"
#include "elf-knowledge.h"

#ifndef LIBELFBITS
# define LIBELFBITS 32
#endif



static int
ELFW(default_ehdr,LIBELFBITS) (Elf *elf, ElfW2(LIBELFBITS,Ehdr) *ehdr,
			       size_t shnum, int *change_bop)
{
  
  if (memcmp (&ehdr->e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0)
    {
      memcpy (&ehdr->e_ident[EI_MAG0], ELFMAG, SELFMAG);
      elf->state.ELFW(elf,LIBELFBITS).ehdr_flags |= ELF_F_DIRTY;
    }

  
  update_if_changed (ehdr->e_ident[EI_CLASS], ELFW(ELFCLASS,LIBELFBITS),
		     elf->state.ELFW(elf,LIBELFBITS).ehdr_flags);

  
  if (unlikely (ehdr->e_ident[EI_DATA] == ELFDATANONE))
    {
      ehdr->e_ident[EI_DATA] =
	BYTE_ORDER == BIG_ENDIAN ? ELFDATA2MSB : ELFDATA2LSB;
      elf->state.ELFW(elf,LIBELFBITS).ehdr_flags |= ELF_F_DIRTY;
    }
  else if (unlikely (ehdr->e_ident[EI_DATA] >= ELFDATANUM))
    {
      __libelf_seterrno (ELF_E_DATA_ENCODING);
      return 1;
    }
  else
    *change_bop = ((BYTE_ORDER == LITTLE_ENDIAN
		    && ehdr->e_ident[EI_DATA] != ELFDATA2LSB)
		   || (BYTE_ORDER == BIG_ENDIAN
		       && ehdr->e_ident[EI_DATA] != ELFDATA2MSB));

  
  update_if_changed (ehdr->e_ident[EI_VERSION], EV_CURRENT,
		     elf->state.ELFW(elf,LIBELFBITS).ehdr_flags);

  if (unlikely (ehdr->e_version == EV_NONE)
      || unlikely (ehdr->e_version >= EV_NUM))
    {
      __libelf_seterrno (ELF_E_UNKNOWN_VERSION);
      return 1;
    }

  if (unlikely (shnum >= SHN_LORESERVE))
    {
      update_if_changed (ehdr->e_shnum, 0,
			 elf->state.ELFW(elf,LIBELFBITS).ehdr_flags);
    }
  else
    update_if_changed (ehdr->e_shnum, shnum,
		       elf->state.ELFW(elf,LIBELFBITS).ehdr_flags);

  if (unlikely (ehdr->e_ehsize != elf_typesize (LIBELFBITS, ELF_T_EHDR, 1)))
    {
      ehdr->e_ehsize = elf_typesize (LIBELFBITS, ELF_T_EHDR, 1);
      elf->state.ELFW(elf,LIBELFBITS).ehdr_flags |= ELF_F_DIRTY;
    }

  return 0;
}


off_t
internal_function
__elfw2(LIBELFBITS,updatenull_wrlock) (Elf *elf, int *change_bop, size_t shnum)
{
  ElfW2(LIBELFBITS,Ehdr) *ehdr;
  int changed = 0;
  int ehdr_flags = 0;

  ehdr = __elfw2(LIBELFBITS,getehdr_wrlock) (elf);

  
  if (ELFW(default_ehdr,LIBELFBITS) (elf, ehdr, shnum, change_bop) != 0)
    return -1;

  
  off_t size = elf_typesize (LIBELFBITS, ELF_T_EHDR, 1);

  
  if (elf->state.ELFW(elf,LIBELFBITS).phdr == NULL
      && (ehdr->e_type == ET_EXEC || ehdr->e_type == ET_DYN
	  || ehdr->e_type == ET_CORE))
    (void) __elfw2(LIBELFBITS,getphdr_wrlock) (elf);
  if (elf->state.ELFW(elf,LIBELFBITS).phdr != NULL)
    {
      if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN
	  && unlikely (ehdr->e_type != ET_CORE))
	{
	  __libelf_seterrno (ELF_E_INVALID_PHDR);
	  return -1;
	}

      size_t phnum;
      if (unlikely (__elf_getphdrnum_rdlock (elf, &phnum) != 0))
	return -1;

      if (elf->flags & ELF_F_LAYOUT)
	{
	  size = MAX ((size_t) size,
		      ehdr->e_phoff
		      + elf_typesize (LIBELFBITS, ELF_T_PHDR, phnum));
	}
      else
	{
	  update_if_changed (ehdr->e_phoff,
			     elf_typesize (LIBELFBITS, ELF_T_EHDR, 1),
			     ehdr_flags);

	  
	  size += elf_typesize (LIBELFBITS, ELF_T_PHDR, phnum);
	}
    }

  if (shnum > 0)
    {
      Elf_ScnList *list;
      bool first = true;

      assert (elf->state.ELFW(elf,LIBELFBITS).scns.cnt > 0);

      if (shnum >= SHN_LORESERVE)
	{
	  Elf_Scn *scn0 = &elf->state.ELFW(elf,LIBELFBITS).scns.data[0];

	  update_if_changed (scn0->shdr.ELFW(e,LIBELFBITS)->sh_size,
			     shnum, scn0->shdr_flags);
	}

      
      list = &elf->state.ELFW(elf,LIBELFBITS).scns;

      if (list->data[1].shdr.ELFW(e,LIBELFBITS) == NULL)
	(void) __elfw2(LIBELFBITS,getshdr_wrlock) (&list->data[1]);

      do
	{
	  for (size_t cnt = first == true; cnt < list->cnt; ++cnt)
	    {
	      Elf_Scn *scn = &list->data[cnt];
	      ElfW2(LIBELFBITS,Shdr) *shdr = scn->shdr.ELFW(e,LIBELFBITS);
	      off_t offset = 0;

	      assert (shdr != NULL);
	      ElfW2(LIBELFBITS,Word) sh_entsize = shdr->sh_entsize;
	      ElfW2(LIBELFBITS,Word) sh_align = shdr->sh_addralign ?: 1;

	      
	      switch (shdr->sh_type)
		{
		case SHT_SYMTAB:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_SYM, 1);
		  break;
		case SHT_RELA:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_RELA, 1);
		  break;
		case SHT_GROUP:
		  
		  if (ehdr->e_type != ET_REL)
		    {
		      __libelf_seterrno (ELF_E_GROUP_NOT_REL);
		      return -1;
		    }
		  
		case SHT_SYMTAB_SHNDX:
		  sh_entsize = elf_typesize (32, ELF_T_WORD, 1);
		  break;
		case SHT_HASH:
		  sh_entsize = SH_ENTSIZE_HASH (ehdr);
		  break;
		case SHT_DYNAMIC:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_DYN, 1);
		  break;
		case SHT_REL:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_REL, 1);
		  break;
		case SHT_DYNSYM:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_SYM, 1);
		  break;
		case SHT_SUNW_move:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_MOVE, 1);
		  break;
		case SHT_SUNW_syminfo:
		  sh_entsize = elf_typesize (LIBELFBITS, ELF_T_SYMINFO, 1);
		  break;
		default:
		  break;
		}

	      update_if_changed (shdr->sh_entsize, sh_entsize,
				 scn->shdr_flags);

	      if (scn->data_read == 0
		  && __libelf_set_rawdata_wrlock (scn) != 0)
		
		return -1;

	      
	      if (list->data[cnt].data_list_rear != NULL)
		{
		  Elf_Data_List *dl = &scn->data_list;

		  while (dl != NULL)
		    {
		      Elf_Data *data = &dl->data.d;
		      if (dl == &scn->data_list && data->d_buf == NULL
			  && scn->rawdata.d.d_buf != NULL)
			data = &scn->rawdata.d;

		      if (unlikely (data->d_version == EV_NONE)
			  || unlikely (data->d_version >= EV_NUM))
			{
			  __libelf_seterrno (ELF_E_UNKNOWN_VERSION);
			  return -1;
			}

		      if (unlikely (! powerof2 (data->d_align)))
			{
			  __libelf_seterrno (ELF_E_INVALID_ALIGN);
			  return -1;
			}

		      sh_align = MAX (sh_align, data->d_align);

		      if (elf->flags & ELF_F_LAYOUT)
			{
			  if (unlikely ((GElf_Word) (data->d_off
						     + data->d_size)
					> shdr->sh_size))
			    {
			      __libelf_seterrno (ELF_E_SECTION_TOO_SMALL);
			      return -1;
			    }
			}
		      else
			{
			  
			  offset = ((offset + data->d_align - 1)
				    & ~(data->d_align - 1));

			  update_if_changed (data->d_off, offset, changed);

			  offset += data->d_size;
			}

		      
		      dl = dl->next;
		    }
		}
	      else
		offset += scn->rawdata.d.d_size;

	      if (elf->flags & ELF_F_LAYOUT)
		{
		  size = MAX ((GElf_Word) size,
			      shdr->sh_offset
			      + (shdr->sh_type != SHT_NOBITS
				 ? shdr->sh_size : 0));

		  if (unlikely (! powerof2 (shdr->sh_addralign))
		      || unlikely (shdr->sh_addralign < sh_align))
		    {
		      __libelf_seterrno (ELF_E_INVALID_ALIGN);
		      return -1;
		    }
		}
	      else
		{
		  
		  update_if_changed (shdr->sh_addralign, sh_align,
				     scn->shdr_flags);

		  size = (size + sh_align - 1) & ~(sh_align - 1);
		  int offset_changed = 0;
		  update_if_changed (shdr->sh_offset, (GElf_Word) size,
				     offset_changed);
		  changed |= offset_changed;

		  if (offset_changed && scn->data_list_rear == NULL)
		    {
		      if (__elf_getdata_rdlock (scn, NULL) == NULL)
			return -1;
		    }

		  
		  update_if_changed (shdr->sh_size, (GElf_Word) offset,
				     changed);

		  if (shdr->sh_type != SHT_NOBITS)
		    size += offset;

		  scn->flags |= changed;
		}

	      if (shdr->sh_entsize != 0
		  && unlikely (shdr->sh_size % shdr->sh_entsize != 0)
		  && (elf->flags & ELF_F_PERMISSIVE) == 0)
		{
		  __libelf_seterrno (ELF_E_INVALID_SHENTSIZE);
		  return -1;
		}
	    }

	  assert (list->next == NULL || list->cnt == list->max);

	  first = false;
	}
      while ((list = list->next) != NULL);

      
      if (elf->flags & ELF_F_LAYOUT)
	{
	  size = MAX ((GElf_Word) size,
		      (ehdr->e_shoff
		       + (elf_typesize (LIBELFBITS, ELF_T_SHDR, shnum))));
	}
      else
	{
#define SHDR_ALIGN sizeof (ElfW2(LIBELFBITS,Off))
	  size = (size + SHDR_ALIGN - 1) & ~(SHDR_ALIGN - 1);

	  update_if_changed (ehdr->e_shoff, (GElf_Word) size, elf->flags);
	  update_if_changed (ehdr->e_shentsize,
			     elf_typesize (LIBELFBITS, ELF_T_SHDR, 1),
			     ehdr_flags);

	  
	  size += elf_typesize (LIBELFBITS, ELF_T_SHDR, shnum);
	}
    }

  elf->state.ELFW(elf,LIBELFBITS).ehdr_flags |= ehdr_flags;

  return size;
}