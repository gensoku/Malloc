/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_larges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 02:59:01 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 02:59:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			show_larges(void *p)
{
	t_large_head	*h;

	while (p)
	{
		h = (t_large_head *)(((t_alloc_page *)p)->headers);
		ma_putstr("LARGE : ");
		ma_putaddr((t_alloc_page *)p, "\n");
		ma_putaddr(((t_alloc_page *)p)->mem, " - ");
		ma_putaddr(((t_alloc_page *)p)->mem + h->size, " : ");
		ma_putszt(h->size);
		ma_putendl(" Octets");
		p = ((t_alloc_page *)p)->next;
	}
}
