/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 04:27:57 by tsedigi           #+#    #+#             */
/*   Updated: 2017/12/20 04:27:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			set_free_large(t_alloc_page *p)
{
	if (p->prev)
		((t_alloc_page *)p->prev)->next = p->next;
	if (p->next)
		((t_alloc_page *)p->next)->prev = p->prev;
}

char				free_large(t_alloc_page *p)
{
	size_t			val;
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	val = size_large_page(((t_large_head *)p->headers)->size, env.opt_flags);
	if (env.opt_flags & MA_SCRIB)
		ma_fillmem(p->mem, ((t_large_head *)p->headers)->size, FREE_FILL);
	if (p == env.larges)
	{
		if (p->next)
		{
			env.larges = (t_alloc_page *)p->next;
			((t_alloc_page *)p->next)->prev = NULL;
		}
		else
			env.larges = NULL;
		get_malloc_env(&env);
	}
	else
		set_free_large(p);
	ma_bzero(p, SZ_G_HD);
	if ((munmap((void *)p, val)) && env.opt_flags & MA_ABORT)
		abort_msg("Error munmap call failed, abort.");
	return (1);
}
