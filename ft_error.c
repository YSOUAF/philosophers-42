/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:24 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:41:52 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks && data->n_mutexc > 0)
	{
		while (i < data->n_mutexc)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	if (data->philos && data->n_philoc > 0)
	{
		i = 0;
		while (i < data->n_philoc)
		{
			pthread_mutex_destroy(&data->philos[i].lock);
			i++;
		}
	}
	pthread_mutex_destroy(&data->message);
	pthread_mutex_destroy(&data->death);
	clean_data(data);
}

int	ft_error(char *str, t_data *data)
{
	printf("error : %s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}
