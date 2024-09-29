/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:02:18 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/01 10:26:55 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_tt *st, int *args)
{
	int	i;
	int	cnt;

	while (1)
	{
		i = 0;
		cnt = 0;
		while (i < args[0])
		{
			if (time_last_eat(&st[i]) == -1)
			{
				message_func_d(&st[i]);
				remove_thread(st);
				return ;
			}
			pthread_mutex_lock(st[i].cnt_eat_mutex);
			if (args[4] != -1 && st[i].cnt_eat >= args[4])
				cnt++;
			pthread_mutex_unlock(st[i++].cnt_eat_mutex);
		}
		if (cnt == args[0])
			break ;
	}
	remove_thread(st);
	return ;
}

pthread_mutex_t	*make_fork(int nums)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nums);
	if (!fork)
		return (NULL);
	while (i < nums)
		if (pthread_mutex_init(&fork[i++], NULL))
			return (NULL);
	return (fork);
}
