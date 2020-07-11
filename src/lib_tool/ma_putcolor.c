/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_putcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 05:34:26 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/23 05:34:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		ma_putcolor(char *color, char *msg, void *addr, size_t x)
{
	ma_putstr(color);
	if (msg)
		ma_putstr(msg);
	if (addr)
		ma_putaddr(addr, "");
	if (x)
		ma_putszt(x);
	ma_putstr(RESET);
}
