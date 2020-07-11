/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_mem_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:30:12 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/22 02:30:13 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			ma_mem_cpy(void *src, void *dest, size_t size)
{
	size_t		i;

	i = 0;
	if (!size || !src || !dest)
		return ;
	while (i < size)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
}
