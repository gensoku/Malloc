/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 01:16:31 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 01:16:32 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			*small_alloc_blk(size_t size,
	t_small_head *h, t_alloc_page *p, char blk)
{
	char			i;
	unsigned int	he;
	unsigned int	me;
	char			scale;

	i = 0;
	me = h->mem;
	he = h->heads;
	scale = get_scale(size, SMALL_P);
	while (i < S_ALLOC_BLK)
	{
		if (i + scale <= S_ALLOC_BLK &&
			!(he & ASSIGN_UBIT(i)) && check_umem(me, i, scale))
		{
			assign_mem_s(&h->mem, i, scale, ASSIGN);
			h->heads |= ASSIGN_UBIT(i);
			h->size[(int)i] = (unsigned short)size;
			refresh_empty_s(h);
			return (SME_O_F(p->mem, blk, i));
		}
		i++;
	}
	if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
		abort_msg("Internal malloc small size error, abort.");
	return (NULL);
}

static void			*new_small_page(size_t size)
{
	t_alloc_page	*p;
	t_alloc_page	*cur;

	cur = get_malloc_env(NULL)->smalls;
	while (cur && cur->next)
		cur = cur->next;
	p = create_page(SMALL_P, 0);
	cur->next = p;
	p->prev = cur;
	return (small_alloc_blk(size, (t_small_head *)p->headers, p, 0));
}

void				*small_malloc(size_t size)
{
	t_malloc_env	env;
	t_alloc_page	*p;
	t_small_head	*h;
	char			i;

	env = *(get_malloc_env(NULL));
	p = env.smalls;
	while (p)
	{
		h = (t_small_head *)p->headers;
		i = 0;
		while (i < BLKS_PAGE)
		{
			if ((unsigned long)h->max_empty >= size)
				return (small_alloc_blk(size, h, p, i));
			i++;
			h++;
		}
		p = p->next;
	}
	return (new_small_page(size));
}
