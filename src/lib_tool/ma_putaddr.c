/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 05:51:25 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 05:51:26 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		ma_putaddr(void *addr, char *msg)
{
	static char		arr[16] = "0123456789abcdef";
	char			buff[20];
	unsigned long	x;
	int				i;

	x = (unsigned long)addr;
	i = 0;
	buff[19] = 0;
	if (!addr)
		return ;
	while (x)
	{
		buff[18 - i] = arr[x % 16];
		x /= 16;
		i++;
	}
	if (!i)
		return ;
	ma_putstr("0x");
	ma_putstr(&buff[18 - i + 1]);
	msg ? ma_putstr(msg) : 0;
}
