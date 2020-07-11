/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 04:27:40 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 04:27:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			set_env_mun_t(t_alloc_page *p)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	if (p->prev && !p->next)
	{
		if (p == env.tinys)
			env.tinys = (t_alloc_page *)p->prev;
		((t_alloc_page *)p->prev)->next = NULL;
		mun_tiny(p);
	}
	else if (p->next && !p->prev)
	{
		env.tinys = (t_alloc_page *)p->next;
		((t_alloc_page *)p->next)->prev = NULL;
		mun_tiny(p);
	}
	else if (p->next && p->prev)
	{
		((t_alloc_page *)p->next)->prev = p->prev;
		((t_alloc_page *)p->prev)->next = p->next;
		if (env.tinys == p)
			env.tinys = (t_alloc_page *)p->next;
		mun_tiny(p);
	}
	get_malloc_env(&env);
}

static void			check_mun_tiny(t_alloc_page *p)
{
	t_tiny_head		*h;
	char			i;

	h = (t_tiny_head *)p->headers;
	i = 0;
	while (i < BLKS_PAGE)
	{
		if (h->max_empty != MAX_TINY)
			return ;
		h++;
		i++;
	}
	set_env_mun_t(p);
}

static char			free_tiny_blok_frag(t_alloc_page *p, char blok, char frag)
{
	t_tiny_head		*h;
	char			scale;

	h = (t_tiny_head *)p->headers + blok;
	if (!(h->heads & ASSIGN_UBIT(frag)))
	{
		if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
			abort_msg("Ptr beeing freed has already been freed, abort.");
		return (1);
	}
	scale = get_scale(h->size[(unsigned short)frag], TINY_P);
	h->heads -= ASSIGN_UBIT(frag);
	assign_mem_t(&h->mem, frag, scale, SUPRESS);
	if (get_malloc_env(NULL)->opt_flags & MA_SCRIB)
	{
		ma_fillmem(TME_O_F(p->mem, blok, frag),
			h->size[(unsigned short)frag], FREE_FILL);
	}
	h->size[(unsigned short)frag] = 0;
	refresh_empty_t(h);
	check_mun_tiny(p);
	return (1);
}

static char			free_tiny_with_blok(t_alloc_page *p, void *ptr, char blok)
{
	void			*mem;
	char			frag;

	mem = TME_O_F(p->mem, blok, 0);
	frag = 0;
	while (frag < T_ALLOC_BLK)
	{
		if (mem == ptr)
			return (free_tiny_blok_frag(p, blok, frag));
		if (ptr < mem)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
			return (1);
		}
		mem += MIN_TINY_SIZE;
		frag++;
	}
	return (1);
}

char				free_tiny(void *ptr, t_alloc_page *p)
{
	char			i;
	void			*mem;

	i = 0;
	mem = p->mem;
	while (i < BLKS_PAGE)
	{
		if (ptr == mem)
			return (free_tiny_blok_frag(p, i, 0));
		if (ptr < mem && i > 0)
			return (free_tiny_with_blok(p, ptr, i - 1));
		if (i == BLKS_PAGE - 1 && ptr < mem + MAX_TINY)
			return (free_tiny_with_blok(p, ptr, i));
		mem += MAX_TINY;
		i++;
	}
	return (0);
}
