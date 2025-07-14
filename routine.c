/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:18:56 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:56:02 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death1(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death);
	dead = philo->data->one_die;
	pthread_mutex_unlock(&philo->data->death);
	return (dead);
}

static int	check_meals(t_philo *philo, int *set_flag)
{
	int	done;

	done = 0;
	if (philo->data->must_eat > 0
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->data->death);
		if (*set_flag == 0)
		{
			philo->data->finished++;
			*set_flag = 1;
			if (philo->data->finished >= philo->data->nbr_philo)
				done = 1;
		}
		pthread_mutex_unlock(&philo->data->death);
	}
	return (done);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	int		set_flag;

	set_flag = 0;
	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		smart_sleep(1, philo);
	while (1)
	{
		if (check_death1(philo))
			break ;
		eat(philo);
		if (check_death1(philo))
			break ;
		if (check_meals(philo, &set_flag))
			break ;
		messages(SLEEPING, philo);
		smart_sleep(philo->data->t_sleep, philo);
		messages(THINKING, philo);
	}
	return (NULL);
}
