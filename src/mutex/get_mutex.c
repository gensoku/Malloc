/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 08:31:57 by tsedigi           #+#    #+#             */
/*   Updated: 2018/01/10 08:31:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <errno.h>

pthread_mutex_t		*get_mutex(void)
{
	static pthread_mutex_t		mutex;
	static pthread_mutexattr_t	attr;
	static char					x = 0;

	if (!x)
	{
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
		pthread_mutexattr_init(&attr);
		pthread_mutex_init(&mutex, &attr);
	}
	x = 1;
	return (&mutex);
}
