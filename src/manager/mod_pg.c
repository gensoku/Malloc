/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_pg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 05:37:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 05:37:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		mod_pg(size_t size, char opt)
{
	size_t	ref;
	size_t	to_add;

	ref = getpagesize();
	to_add = 0;
	if (size > ref)
	{
		to_add = size % ref;
		to_add = ref - to_add;
	}
	else
		to_add = ref - size;
	if (opt > 0)
		return (to_add);
	return (size + to_add);
}
