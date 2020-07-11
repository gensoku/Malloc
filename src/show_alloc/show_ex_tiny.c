/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_ex_tiny.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 02:31:46 by tsedigi           #+#    #+#             */
/*   Updated: 2018/02/02 02:31:47 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			color_tiny(void *addr, t_tiny_head *th, char opts, char y)
{
	if (opts & SHOW_COLOR)
	{
		ma_putcolor(GREEN_H, "", addr, 0);
		ma_putcolor(RED_H, " - ", NULL, 0);
		ma_putcolor(GREEN_H, "", addr + th->size[(short)y], 0);
		ma_putcolor(YELLOW_H, " : ", NULL, th->size[(short)y]);
		ma_putcolor(YELLOW_H, " Octets \n", NULL, 0);
	}
	else
	{
		ma_putaddr(addr, " - ");
		ma_putaddr(addr + th->size[(short)y], " : ");
		ma_putnbr(th->size[(short)y]);
		ma_putendl(" Octets");
	}
}

static void			show_mem_blk(t_alloc_page *p, char i, char opts)
{
	char			y;
	t_tiny_head		*th;
	void			*addr;

	y = 0;
	th = (t_tiny_head *)p->headers;
	th += i;
	if (opts & SHOW_FRAG)
		print_head_mem(th->mem, th->heads, TINY_P, opts);
	while (y < T_ALLOC_BLK)
	{
		if (th->heads & ASSIGN_UBIT(y))
		{
			addr = TME_O_F(p->mem, i, y);
			color_tiny(addr, th, opts, y);
			opts & DUMP_MEM ? ma_dump_mem(addr, th->size[(short)y], opts) : 0;
		}
		y++;
	}
}

void				show_ex_tiny(t_alloc_page *p, char opts)
{
	t_tiny_head		*h;
	char			i;

	if (!p)
		return ;
	i = 0;
	h = (t_tiny_head *)p->headers;
	while (i < BLKS_PAGE)
	{
		if (h->max_empty != (unsigned short)MAX_TINY)
			show_mem_blk(p, i, opts);
		i++;
		h++;
	}
}
