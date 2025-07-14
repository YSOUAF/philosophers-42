/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:32 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:42:13 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		return (ft_error("malloc error: forks", NULL));
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philos)
		return (ft_error("malloc error: philos", data));
	return (0);
}

static int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_error("mutex init failed: fork", data), 1);
		data->n_mutexc++;
		i++;
	}
	return (0);
}

static void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nbr_philo];
		i++;
	}
}

static int	init_philo_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal_t = 0;
		data->philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			return (ft_error("mutex init failed: philo", data), 1);
		data->n_philoc++;
		i++;
	}
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	if (check_parse(ac, av, data))
		return (1);
	if (alloc(data))
		return (1);
	if (init_fork_mutexes(data))
		return (1);
	assign_forks(data);
	if (init_philo_data(data))
		return (1);
	return (0);
}
