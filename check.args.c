/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:14 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:41:31 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_limits(t_data *data, int ac)
{
	if (data->nbr_philo <= 0)
		return (ft_error("Philos must be > 0", NULL));
	if (data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0)
		return (ft_error("Time values must be > 0 ms", NULL));
	if (ac == 6 && data->must_eat <= 0)
		return (ft_error("nbr of times each philo must eat must be > 0", NULL));
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->message, NULL) != 0)
		return (ft_error("Failed to init mutex 'message'", NULL));
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->message);
		return (ft_error("Failed to init mutex 'death'", NULL));
	}
	return (0);
}

int	check_parse(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (ft_error("Wrong argument count", NULL));
	if (!is_valid_args(av))
		return (ft_error("Invalid arguments", NULL));
	data->nbr_philo = ft_atoi_check(av[1]);
	data->t_die = ft_atoi_check(av[2]);
	data->t_eat = ft_atoi_check(av[3]);
	data->t_sleep = ft_atoi_check(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = ft_atoi_check(av[5]);
	if (validate_limits(data, ac) != 0)
		return (1);
	data->finished = 0;
	data->start_time = 0;
	data->one_die = 0;
	data->philos = NULL;
	data->forks = NULL;
	data->n_mutexc = 0;
	data->n_philoc = 0;
	return (init_mutexes(data));
}
