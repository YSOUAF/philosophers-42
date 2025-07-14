/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:05 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 12:36:19 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(const char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->death);
	if (philo->data->one_die)
	{
		pthread_mutex_unlock(&philo->data->death);
		return ;
	}
	pthread_mutex_lock(&philo->data->message);
	time = get_time_in_ms() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->message);
	pthread_mutex_unlock(&philo->data->death);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		messages(FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		messages(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		messages(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		messages(FORK, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->meals_eaten++;
	philo->last_meal_t = get_time_in_ms();
	messages(EATING, philo);
	pthread_mutex_unlock(&philo->lock);
	smart_sleep(philo->data->t_eat, philo);
	drop_forks(philo);
}
