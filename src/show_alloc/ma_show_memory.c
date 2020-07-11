/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_show_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 02:19:39 by tsedigi           #+#    #+#             */
/*   Updated: 2018/02/02 02:19:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void				show_large_mem(char opts)
{
	t_alloc_page		*p;

	p = get_malloc_env(NULL)->larges;
	if (!p)
		return ;
	while (p)
	{
		if (opts & SHOW_COLOR)
		{
			ma_putcolor(RED_H, "LARGE page at : ", p, 0);
			ma_putendl("");
		}
		else
		{
			ma_putstr("LARGE page at : ");
			ma_putaddr(p, "");
			ma_putendl("");
		}
		show_ex_large(p, opts);
		p = p->next;
	}
}

static void				show_small_mem(char opts)
{
	t_alloc_page		*p;

	p = get_malloc_env(NULL)->smalls;
	if (!p)
		return ;
	while (p)
	{
		if (opts & SHOW_COLOR)
		{
			ma_putcolor(RED_H, "SMALL page at : ", p, 0);
			ma_putendl("");
		}
		else
		{
			ma_putstr("SMALL page at : ");
			ma_putaddr(p, "");
			ma_putendl("");
		}
		show_ex_small(p, opts);
		p = p->next;
	}
}

static void				show_tiny_mem(char opts)
{
	t_alloc_page		*p;

	p = get_malloc_env(NULL)->tinys;
	if (!p)
		return ;
	while (p)
	{
		if (opts & SHOW_COLOR)
		{
			ma_putcolor(RED_H, "TINY page at : ", p, 0);
			ma_putendl("");
		}
		else
		{
			ma_putstr("TINY page at : ");
			ma_putaddr(p, "");
			ma_putendl("");
		}
		show_ex_tiny(p, opts);
		p = p->next;
	}
}

void					ma_show_memory(char types, char opts)
{
	if (types == TINY_TYPE || types == ALL_TYPE)
		show_tiny_mem(opts);
	if (types == SMALL_TYPE || types == ALL_TYPE)
		show_small_mem(opts);
	if (types == LARGE_TYPE || types == ALL_TYPE)
		show_large_mem(opts);
}
