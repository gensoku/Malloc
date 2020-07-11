/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tinys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:08:11 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 02:08:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t		get_empty_t(t_tiny_head *h, char frag)
{
	char			i;
	size_t			ret;

	i = frag;
	ret = 0;
	while (i < T_ALLOC_BLK)
	{
		if (i == frag && !(h->heads & ASSIGN_UBIT(i)))
			ma_putendl("intern error");
		else if (i == frag)
			ret += MIN_TINY_SIZE;
		else if (!(h->heads & ASSIGN_UBIT(i)))
			ret += MIN_TINY_SIZE;
		else
			return (ret);
		i++;
	}
	return (ret);
}

static void			*ma_realloc_tiny_hlp(t_rea_s *rea, size_t size,
	t_tiny_head *h, void *ptr)
{
	size_t			check_empty;
	void			*ret;
	void			*to_free;

	ret = NULL;
	check_empty = get_empty_t(h, rea->frag);
	if (check_empty >= size)
	{
		assign_mem_t(&h->mem, rea->frag, get_scale(size, TINY_P), ASSIGN);
		h->size[(unsigned short)rea->frag] = (unsigned short)size;
		refresh_empty_t(h);
		return (ptr);
	}
	else
	{
		ret = call_malloc(size);
		to_free = TME_O_F(rea->page->mem, rea->blok, rea->frag);
		ma_mem_cpy(to_free, ret, h->size[(unsigned short)rea->frag]);
		call_free(to_free);
	}
	return (ret);
}

void				*realloc_tinys(t_rea_s *rea, void *ptr, size_t size)
{
	t_tiny_head		*h;

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
	h = (t_tiny_head *)rea->page->headers;
	h += rea->blok;
	if (size < (size_t)h->size[(unsigned short)rea->frag])
		return (ptr);
	return (ma_realloc_tiny_hlp(rea, size, h, ptr));
}
