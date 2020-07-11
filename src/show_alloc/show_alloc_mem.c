/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 04:07:14 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/18 04:07:16 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			show_frag_s(t_alloc_page *p, char i)
{
	char			y;
	t_small_head	*th;
	void			*addr;

	y = 0;
	th = (t_small_head *)p->headers;
	th += i;
	while (y < S_ALLOC_BLK)
	{
		if (th->heads & ASSIGN_UBIT(y))
		{
			addr = SME_O_F(p->mem, i, y);
			ma_putaddr(addr, " - ");
			ma_putaddr(addr + th->size[(unsigned short)y], " : ");
			ma_putnbr(th->size[(unsigned short)y]);
			ma_putendl(" Octets");
		}
		y++;
	}
}

static void			show_frag_t(t_alloc_page *p, char i)
{
	char			y;
	t_tiny_head		*th;
	void			*addr;

	y = 0;
	th = (t_tiny_head *)p->headers;
	th += i;
	while (y < T_ALLOC_BLK)
	{
		if (th->heads & ASSIGN_UBIT(y))
		{
			addr = TME_O_F(p->mem, i, y);
			ma_putaddr(addr, " - ");
			ma_putaddr(addr + th->size[(unsigned short)y], " : ");
			ma_putnbr(th->size[(unsigned short)y]);
			ma_putendl(" Octets");
		}
		y++;
	}
}

static void			show_content(void *headers, char type, t_alloc_page *p)
{
	t_tiny_head		*t_h;
	t_small_head	*s_h;
	char			i;

	t_h = type == TINY_P ? (t_tiny_head *)headers : NULL;
	s_h = type == SMALL_P ? (t_small_head *)headers : NULL;
	i = -1;
	if (type == TINY_P)
	{
		while (i++ < BLKS_PAGE)
		{
			if (t_h->max_empty != (unsigned short)MAX_TINY)
				show_frag_t(p, i);
			t_h++;
		}
	}
	else
	{
		while (i++ < BLKS_PAGE)
		{
			if (s_h->max_empty != (unsigned short)MAX_SMALL)
				show_frag_s(p, i);
			s_h++;
		}
	}
}

static void			show_pages(void *addr, char type)
{
	t_alloc_page	*p;

	p = (t_alloc_page *)addr;
	while (p)
	{
		ma_putstr(type == TINY_P ? "TINY : " : "SMALL : ");
		ma_putaddr(p, "\n");
		show_content(p->headers, type, p);
		p = p->next;
	}
}

void				show_alloc_mem(void)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	if (!(env.is_set))
		return ;
	if (pthread_mutex_lock(get_mutex()))
		return ;
	env.tinys ? show_pages(env.tinys, TINY_P) : 0;
	env.smalls ? show_pages(env.smalls, SMALL_P) : 0;
	env.larges ? show_larges(env.larges) : 0;
	pthread_mutex_unlock(get_mutex());
}
