/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_s_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 01:23:38 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 01:23:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				assign_mem_t(unsigned int *mem,
	char i, char scale, char opt)
{
	char			x;

	x = i + scale;
	while (scale)
	{
		x--;
		if (opt == ASSIGN)
			*mem |= ASSIGN_UBIT(x);
		else if (opt == SUPRESS)
			*mem -= ASSIGN_UBIT(x);
		scale--;
	}
}

void				assign_mem_s(unsigned char *mem,
	char i, char scale, char opt)
{
	char			x;

	x = i + scale;
	while (scale)
	{
		x--;
		if (opt == ASSIGN)
			*mem |= ASSIGN_UBIT(x);
		else if (opt == SUPRESS)
			*mem -= ASSIGN_UBIT(x);
		scale--;
	}
}

char				check_umem(unsigned long mem, char i, char scale)
{
	char			val;

	while (scale)
	{
		val = i + scale - 1;
		if (mem & ASSIGN_UBIT(val))
			return (0);
		scale--;
	}
	return (1);
}

char				get_scale(size_t size, char type)
{
	char			r;
	size_t			val;

	val = type == TINY_P ? MIN_TINY_SIZE : MIN_SMALL_SZ;
	r = size / val;
	r += size % val ? 1 : 0;
	return (r);
}
