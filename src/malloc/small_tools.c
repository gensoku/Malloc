/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 01:22:17 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 01:22:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				refresh_empty_s(t_small_head *h)
{
	unsigned short			max;
	unsigned short			cur;
	unsigned long			mem;
	char					i;

	max = 0;
	i = 0;
	mem = h->mem;
	cur = 0;
	while (i < S_ALLOC_BLK)
	{
		if (!(mem & ASSIGN_UBIT(i)))
		{
			cur++;
			if (cur > max)
				max = cur;
		}
		else
		{
			cur = 0;
		}
		i++;
	}
	h->max_empty = max * MIN_SMALL_SZ;
}
