/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ma_hist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 01:32:08 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/23 01:32:09 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void				push_ma_hist(void *ret, size_t size, void *ptr, char type)
{
	t_ma_hist		*node;
	t_malloc_env	env;

	if (!(node = call_malloc(sizeof(t_ma_hist))))
		return ;
	env = *(get_malloc_env(NULL));
	node->type = type;
	node->ret = ret;
	node->ptr = ptr;
	node->size = size;
	node->next = NULL;
	if (!env.history)
	{
		env.history = node;
		env.last_hist = node;
	}
	else if (env.last_hist)
	{
		env.last_hist->next = node;
		env.last_hist = node;
	}
	get_malloc_env(&env);
}
