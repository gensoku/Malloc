/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_ex_large.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 02:31:57 by tsedigi           #+#    #+#             */
/*   Updated: 2018/02/02 02:31:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				show_ex_large(t_alloc_page *p, char opts)
{
	t_large_head	*h;
	void			*addr;
	char			i;

	if (!p)
		return ;
	i = 0;
	h = (t_large_head *)p->headers;
	addr = p->mem;
	if (opts & SHOW_COLOR)
	{
		ma_putcolor(GREEN_H, "", addr, 0);
		ma_putcolor(RED_H, " - ", NULL, 0);
		ma_putcolor(GREEN_H, "", addr + h->size, 0);
		ma_putcolor(YELLOW_H, " : ", NULL, h->size);
		ma_putcolor(YELLOW_H, " Octets \n", NULL, 0);
	}
	else
	{
		ma_putaddr(addr, " - ");
		ma_putaddr(addr + h->size, " : ");
		ma_putszt(h->size);
		ma_putendl(" Octets");
	}
	opts & DUMP_MEM ? ma_dump_mem(addr, h->size, opts) : 0;
}
