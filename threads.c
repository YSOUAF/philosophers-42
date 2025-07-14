/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:21:19 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:47:41 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_partial_threads(t_data *data, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			printf("Warning: failed to join thread %d\n", i);
		i++;
	}
	return (0);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].last_meal_t = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine, &data->philos[i]))
		{
			pthread_mutex_lock(&data->death);
			data->one_die = 2;
			pthread_mutex_unlock(&data->death);
			join_partial_threads(data, i);
			return (ft_error("thread creation error", data));
		}
		i++;
	}
	return (0);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (ft_error("thread join error", data));
		i++;
	}
	return (0);
}

int	thread_init(t_data *data)
{
	pthread_t	monitor_thread;
	int			monitor_flag;

	monitor_flag = 0;
	data->start_time = get_time_in_ms();
	if (create_threads(data))
		return (1);
	if (pthread_create(&monitor_thread, NULL, &monitor, data) == 0)
		monitor_flag = 1;
	else
	{
		join_threads(data);
		return (ft_error("monitor thread creation error", data));
	}
	if (monitor_flag)
		pthread_join(monitor_thread, NULL);
	if (join_threads(data))
		return (1);
	return (0);
}
