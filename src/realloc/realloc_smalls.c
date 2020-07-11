/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_smalls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:08:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 02:08:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t		get_empty_s(t_small_head *h, char frag)
{
	char			i;
	size_t			ret;

	i = frag;
	ret = 0;
	while (i < S_ALLOC_BLK)
	{
		if (i == frag && !(h->heads & ASSIGN_UBIT(i)))
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Internal malloc error, abort.");
		}
		else if (i == frag)
			ret += MIN_SMALL_SZ;
		else if (!(h->heads & ASSIGN_UBIT(i)))
			ret += MIN_SMALL_SZ;
		else
			return (ret);
		i++;
	}
	return (ret);
}

static void			*ma_realloc_small_hlp(t_rea_s *rea, size_t size,
	t_small_head *h, void *ptr)
{
	size_t			check_empty;
	void			*to_free;
	void			*ret;

	ret = NULL;
	check_empty = get_empty_s(h, rea->frag);
	if (check_empty >= size)
	{
		assign_mem_s(&h->mem, rea->frag, get_scale(size, SMALL_P), ASSIGN);
		h->size[(unsigned short)rea->frag] = (unsigned short)size;
		refresh_empty_s(h);
		return (ptr);
	}
	else
	{
		ret = call_malloc(size);
		to_free = SME_O_F(rea->page->mem, rea->blok, rea->frag);
		ma_mem_cpy(to_free, ret, (size_t)h->size[(unsigned short)rea->frag]);
		call_free(to_free);
	}
	return (ret);
}

void				*realloc_smalls(t_rea_s *rea, void *ptr, size_t size)
{
	t_small_head	*h;

	if (rea->err || !rea->page)
	{
		if (rea->err == REA_NOT_ALLOCATED)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing reallocated was not allocated, abort.");
			return (NULL);
		}
		return (call_malloc(size));
	}
	h = (t_small_head *)rea->page->headers;
	h += rea->blok;
	if (size < (size_t)h->size[(unsigned short)rea->frag])
		return (ptr);
	return (ma_realloc_small_hlp(rea, size, h, ptr));
}
