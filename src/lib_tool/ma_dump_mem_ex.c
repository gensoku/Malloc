/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_dump_mem_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 03:46:58 by tsedigi           #+#    #+#             */
/*   Updated: 2018/02/02 03:46:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	ma_dump_hex(char i)
{
	static char	arr[16] = "0123456789abcdef";

	if (!i)
	{
		ma_putchar('0');
		ma_putchar('0');
		return ;
	}
	if (i > 16)
	{
		ma_putchar(arr[i % 16]);
		i /= 16;
	}
	ma_putchar(arr[(unsigned short)i]);
}

static void	ma_dump_space(size_t diff)
{
	if (diff)
		ma_putchar(' ');
	if (diff >= 8)
		ma_putstr("    ");
	else if (diff >= 6)
		ma_putstr("   ");
	else if (diff >= 4)
		ma_putstr("  ");
	else if (diff >= 2)
		ma_putstr(" ");
}

static void	ma_printable_dump(char *content, size_t size)
{
	size_t	i;
	size_t	diff;

	i = 0;
	diff = 10 - size;
	if (content)
	{
		ma_putstr("          ");
		ma_dump_space(diff);
		while (diff)
		{
			ma_putchar(' ');
			ma_putchar(' ');
			diff--;
		}
		while (content && i < size)
		{
			if (content[i] >= 32 && content[i] < 127)
				ma_putchar(content[i]);
			else
				ma_putchar('.');
			i++;
		}
		ma_putchar('\n');
	}
}

static void	ma_dump_last(char *save, size_t i)
{
	if (i && !(i % 10))
	{
		ma_putchar(' ');
		ma_printable_dump(&save[i - 10], 10);
	}
	else
		ma_printable_dump(&save[i - (i % 10)], i % 10);
}

void		ma_dump_mem(void *addr, size_t size, char opts)
{
	size_t	i;
	char	*content;
	char	*save;

	if (!addr || !size)
		return ;
	if (opts & SHOW_COLOR)
		ma_putcolor(CYAN_H, "Memory dump : \n", NULL, 0);
	else
		ma_putendl("Memory dump : ");
	i = 0;
	content = (char *)addr;
	save = (char *)addr;
	while (i < size)
	{
		if (i != 0 && !(i % 2))
			ma_putchar(' ');
		if (i != 0 && !(i % 10))
			ma_printable_dump(&save[i - 10], 10);
		ma_dump_hex(save[i]);
		i++;
	}
	ma_dump_last(save, i);
}
