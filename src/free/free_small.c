/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 04:27:47 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 04:27:52 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			set_env_mun_s(t_alloc_page *p)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	if (p->prev && !p->next)
	{
		if (env.smalls == p)
			env.smalls = (t_alloc_page *)p->prev;
		((t_alloc_page *)p->prev)->next = NULL;
		mun_small(p);
	}
	else if (p->next && !p->prev)
	{
		env.smalls = (t_alloc_page *)p->next;
		((t_alloc_page *)p->next)->prev = NULL;
		mun_small(p);
	}
	else if (p->prev && p->next)
	{
		((t_alloc_page *)p->next)->prev = p->prev;
		((t_alloc_page *)p->prev)->next = p->next;
		if (env.smalls == p)
			env.smalls = (t_alloc_page *)p->next;
		mun_small(p);
	}
	get_malloc_env(&env);
}

static void			check_mun_small(t_alloc_page *p)
{
	t_small_head	*h;
	char			i;

	if (!p->prev && !p->next)
		return ;
	h = (t_small_head *)p->headers;
	i = 0;
	while (i < BLKS_PAGE)
	{
		if (h->max_empty != (unsigned short)MAX_SMALL)
			return ;
		h++;
		i++;
	}
	set_env_mun_s(p);
}

static char			free_small_blok_frag(t_alloc_page *p, char blok, char frag)
{
	t_small_head	*h;
	char			scale;

	h = (t_small_head *)p->headers + blok;
	if (!(h->heads & ASSIGN_UBIT(frag)))
	{
		if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
			abort_msg("Ptr beeing freed has already been freed, abort.");
		return (1);
	}
	scale = get_scale(h->size[(unsigned short)frag], SMALL_P);
	h->heads -= ASSIGN_UBIT(frag);
	assign_mem_s(&h->mem, frag, scale, SUPRESS);
	if (get_malloc_env(NULL)->opt_flags & MA_SCRIB)
	{
		ma_fillmem(SME_O_F(p->mem, blok, frag),
			h->size[(unsigned short)frag], FREE_FILL);
	}
	h->size[(unsigned short)frag] = 0;
	refresh_empty_s(h);
	check_mun_small(p);
	return (1);
}

static char			free_small_with_blok(t_alloc_page *p, void *ptr, char blok)
{
	void			*mem;
	char			frag;

	mem = SME_O_F(p->mem, blok, 0);
	frag = 0;
	while (frag < S_ALLOC_BLK)
	{
		if (mem == ptr)
			return (free_small_blok_frag(p, blok, frag));
		if (ptr < mem)
		{
			if (get_malloc_env(NULL)->opt_flags & MA_ABORT)
				abort_msg("Ptr beeing freed was not allocated, abort.");
			return (1);
		}
		mem += MIN_SMALL_SZ;
		frag++;
	}
	return (1);
}

char				free_small(void *ptr, t_alloc_page *p)
{
	char			i;
	void			*mem;

	i = 0;
	mem = p->mem;
	while (i < BLKS_PAGE)
	{
		if (ptr == mem)
			return (free_small_blok_frag(p, i, 0));
		if (ptr < mem && i > 0)
			return (free_small_with_blok(p, ptr, i - 1));
		if (i == BLKS_PAGE - 1 && ptr < mem + MAX_SMALL)
			return (free_small_with_blok(p, ptr, i));
		mem += MAX_SMALL;
		i++;
	}
	return (0);
}
