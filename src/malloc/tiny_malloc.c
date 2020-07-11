/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 05:19:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/18 05:19:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			*tiny_alloc_blk(size_t size, t_tiny_head *h,
	t_alloc_page *p, char blk)
{
	char			i;
	unsigned int	he;
	unsigned int	me;
	char			scale;

	i = 0;
	me = h->mem;
	he = h->heads;
	scale = get_scale(size, TINY_P);
	while (i < T_ALLOC_BLK)
	{
		if (i + scale <= T_ALLOC_BLK &&
			!(he & ASSIGN_UBIT(i)) && check_umem(me, i, scale))
		{
			assign_mem_t(&h->mem, i, scale, ASSIGN);
			h->heads |= ASSIGN_UBIT(i);
			h->size[(unsigned short)i] = (unsigned short)size;
			refresh_empty_t(h);
			return (TME_O_F(p->mem, blk, i));
		}
		i++;
	}
	if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
		abort_msg("Internal malloc tiny size error, abort.");
	return (NULL);
}

static void			*new_tiny_page(size_t size)
{
	t_alloc_page	*p;
	t_alloc_page	*cur;

	cur = get_malloc_env(NULL)->tinys;
	while (cur && cur->next)
		cur = cur->next;
	p = create_page(TINY_P, 0);
	cur->next = p;
	p->prev = cur;
	return (tiny_alloc_blk(size, (t_tiny_head *)p->headers, p, 0));
}

void				*tiny_malloc(size_t size)
{
	t_malloc_env	env;
	t_alloc_page	*p;
	t_tiny_head		*h;
	char			i;

	env = *(get_malloc_env(NULL));
	p = env.tinys;
	while (p)
	{
		h = (t_tiny_head *)p->headers;
		i = 0;
		while (i < BLKS_PAGE)
		{
			if ((unsigned long)h->max_empty >= size)
				return (tiny_alloc_blk(size, h, p, i));
			i++;
			h++;
		}
		p = p->next;
	}
	return (new_tiny_page(size));
}
