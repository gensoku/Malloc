/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_head_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 00:51:17 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 00:51:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_head_mem(unsigned int m, unsigned int h, char type, char opts)
{
	opts & SHOW_COLOR ? ma_putcolor(MAGENT_H, "head ", NULL, 0) :
		ma_putstr("head ");
	ma_print_u_bit(h, type, opts);
	opts & SHOW_COLOR ? ma_putcolor(MAGENT_H, "mem  ", NULL, 0) :
		ma_putstr("mem  ");
	ma_print_u_bit(m, type, opts);
}
