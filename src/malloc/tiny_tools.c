/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 01:08:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 01:08:38 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				refresh_empty_t(t_tiny_head *h)
{
	unsigned short	max;
	unsigned short	cur;
	unsigned long	mem;
	char			i;

	max = 0;
	i = 0;
	mem = h->mem;
	cur = 0;
	while (i < T_ALLOC_BLK)
	{
		if (mem & ASSIGN_UBIT(i))
			cur = 0;
		else
		{
			cur++;
			if (cur > max)
				max = cur;
		}
		i++;
	}
	h->max_empty = max * MIN_TINY_SIZE;
}
