/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:40 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:54:56 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philo_ate(t_data *data)
{
	if (data->must_eat > 0)
	{
		pthread_mutex_lock(&data->death);
		if (data->finished >= data->nbr_philo)
		{
			data->one_die = 1;
			pthread_mutex_unlock(&data->death);
			return (1);
		}
		pthread_mutex_unlock(&data->death);
	}
	return (0);
}

static int	check_death(t_data *data, int i)
{
	long	current_time;
	long	last_meal;
	int		already_dead;

	pthread_mutex_lock(&data->philos[i].lock);
	last_meal = data->philos[i].last_meal_t;
	pthread_mutex_unlock(&data->philos[i].lock);
	current_time = get_time_in_ms();
	if (current_time - last_meal > data->t_die)
	{
		pthread_mutex_lock(&data->death);
		already_dead = data->one_die;
		if (!already_dead)
		{
			data->one_die = 1;
			pthread_mutex_lock(&data->message);
			printf("%ld %d %s\n", current_time - data->start_time,
				data->philos[i].id, DIED);
			pthread_mutex_unlock(&data->message);
		}
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	return (0);
}

void	*monitor(void *data_ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_ptr;
	while (1)
	{
		pthread_mutex_lock(&data->death);
		if (data->one_die)
		{
			pthread_mutex_unlock(&data->death);
			break ;
		}
		pthread_mutex_unlock(&data->death);
		i = 0;
		while (i < data->nbr_philo)
		{
			if (check_death(data, i))
				return (NULL);
			if (all_philo_ate(data))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
