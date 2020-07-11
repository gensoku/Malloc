/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma_get_rights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 06:17:04 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/25 06:17:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mode_t		ma_get_rights(void)
{
	mode_t			ret;

	ret = 0;
	ret |= S_IWUSR;
	ret |= S_IRUSR;
	ret |= S_IRGRP;
	ret |= S_IROTH;
	return (ret);
}
