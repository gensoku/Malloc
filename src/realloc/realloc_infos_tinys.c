/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_infos_tinys.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 01:34:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 01:34:40 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			get_info_frag(t_alloc_page *p, void *ptr,
	t_rea_s *ret, char blok)
{
	void			*mem;
	char			frag;

	mem = TME_O_F(p->mem, blok, 0);
	frag = 0;
	while (frag < T_ALLOC_BLK)
	{
		if (mem == ptr)
		{
			ret->frag = frag;
			ret->blok = blok;
			return ;
		}
		if (ptr < mem)
		{
			ret->err = REA_NOT_ALLOCATED;
			return ;
		}
		mem += MIN_TINY_SIZE;
		frag++;
	}
}

void				get_infos_rea_t(t_alloc_page *p, void *ptr, t_rea_s *ret)
{
	char			blok;
	void			*mem;

	blok = 0;
	mem = p->mem;
	while (blok < BLKS_PAGE)
	{
		if (ptr == mem)
		{
			ret->frag = 0;
			ret->blok = blok;
			return ;
		}
		if ((ptr < mem && blok > 0) ||
			(blok == BLKS_PAGE - 1 && ptr < mem + MAX_TINY))
		{
			get_info_frag(p, ptr, ret, ptr < mem ? blok - 1 : blok);
			return ;
		}
		mem += MAX_TINY;
		blok++;
	}
	ret->err = REA_INTERN_ERR;
}
