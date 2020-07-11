/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_print_u_bit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 06:09:20 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/18 06:09:22 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ma_print_u_bit(unsigned int c, char type, char opts)
{
	int i;

	i = 0;
	while (i < (type == TINY_P ? T_ALLOC_BLK : S_ALLOC_BLK))
	{
		if (c & ASSIGN_UBIT(i))
		{
			if (opts & SHOW_COLOR)
				ma_putcolor(RED_H, "1", NULL, 0);
			else
				ma_putchar('1');
		}
		else
		{
			if (opts & SHOW_COLOR)
				ma_putcolor(GREEN_H, "0", NULL, 0);
			else
				ma_putchar('0');
		}
		i++;
	}
	ma_putchar('\n');
}
