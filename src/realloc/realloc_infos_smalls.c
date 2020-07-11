/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_infos_smalls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:01:45 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 02:01:46 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			get_info_frag(t_alloc_page *p, void *ptr,
	t_rea_s *ret, char blok)
{
	void			*mem;
	char			frag;

	mem = SME_O_F(p->mem, blok, 0);
	frag = 0;
	while (frag < S_ALLOC_BLK)
	{
		if (mem == ptr)
		{
			ret->frag = frag;
			ret->blok = blok;
			break ;
		}
		if (ptr < mem)
		{
			ret->err = REA_NOT_ALLOCATED;
			break ;
		}
		mem += MIN_SMALL_SZ;
		frag++;
	}
}

void				get_infos_rea_s(t_alloc_page *p, void *ptr, t_rea_s *ret)
{
	char			blok;
	void			*mem;

	blok = 0;
	mem = p->mem;
	while (blok < BLKS_PAGE)
	{
		if (ptr == mem)
		{
			ret->blok = blok;
			ret->frag = 0;
			return ;
		}
		if ((ptr < mem && blok > 0) ||
			(blok == BLKS_PAGE - 1 && ptr < mem + MAX_SMALL))
		{
			get_info_frag(p, ptr, ret, ptr < mem ? blok - 1 : blok);
			return ;
		}
		mem += MAX_SMALL;
		blok++;
	}
	ret->err = REA_INTERN_ERR;
}
