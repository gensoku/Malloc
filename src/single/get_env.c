/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_malloc_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 06:19:42 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/13 06:19:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_malloc_env		*get_malloc_env(t_malloc_env *env)
{
	static t_malloc_env cur_env;

	if (env)
		cur_env = *env;
	return (&cur_env);
}
