/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 06:26:42 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/17 06:26:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			show_free_h(t_ma_hist *node, char opts)
{
	if (opts & SHOW_COLOR)
	{
		ma_putcolor(RED_H, "Free call : on ptr -> ", NULL, 0);
		ma_putcolor(RED_H, NULL, node->ptr, 0);
		ma_putendl("");
	}
	else
	{
		ma_putstr("Free call : on ptr -> ");
		ma_putaddr(node->ptr, "");
		ma_putendl("");
	}
}

static void			show_malloc_h(t_ma_hist *node, char opts)
{
	if (opts & SHOW_COLOR)
	{
		ma_putcolor(BLUE_H, "Malloc call : ", NULL, 0);
		ma_putcolor(BLUE_H, "size -> ", NULL, node->size);
		ma_putcolor(BLUE_H, " return -> ", node->ret, 0);
		ma_putendl("");
	}
	else
	{
		ma_putstr("Malloc call : size -> ");
		ma_putszt(node->size);
		ma_putstr(" return -> ");
		ma_putaddr(node->ret, "");
		ma_putendl("");
	}
}

static void			show_realloc_h(t_ma_hist *node, char opts)
{
	if (opts & SHOW_COLOR)
	{
		ma_putcolor(GREEN_H, "Realloc call : ", NULL, 0);
		ma_putcolor(GREEN_H, "size -> ", NULL, node->size);
		ma_putcolor(GREEN_H, " on ptr -> ", node->ptr, 0);
		ma_putcolor(GREEN_H, " return -> ", node->ret, 0);
		ma_putendl("");
	}
	else
	{
		ma_putstr("Realloc call : size -> ");
		ma_putszt(node->size);
		ma_putstr(" on -> ");
		ma_putaddr(node->ptr, "");
		ma_putstr(" return -> ");
		ma_putaddr(node->ret, "");
		ma_putendl("");
	}
}

static void			ma_show_history(char opts, int old_fd, t_ma_hist *h)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	h = env.history;
	if (env.hist_fd != 1 && env.hist_fd != -1)
	{
		old_fd = env.fd;
		env.fd = env.hist_fd;
		get_malloc_env(&env);
	}
	while (h)
	{
		if (h->type == MALLOC_TYPE)
			show_malloc_h(h, opts);
		else if (h->type == FREE_TYPE)
			show_free_h(h, opts);
		else if (h->type == REALLOC_TYPE)
			show_realloc_h(h, opts);
		h = h->next;
	}
	if (old_fd)
	{
		env.fd = old_fd;
		get_malloc_env(&env);
	}
}

void				show_alloc_mem_ex(char types, char opts)
{
	t_malloc_env	env;

	env = *(get_malloc_env(NULL));
	(void)types;
	if (!(env.is_set))
		return ;
	if (opts & SHOW_HIST && env.opt_flags & MA_HIST && env.history)
		ma_show_history(opts, -1, NULL);
	if (opts & SHOW_MEM)
		ma_show_memory(types, opts);
}
