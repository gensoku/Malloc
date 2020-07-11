/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 04:47:57 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/14 04:47:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		ma_putendl(char *str)
{
	write(DEFAULT_FD, str, ma_strlen(str));
	write(DEFAULT_FD, "\n", 1);
}
