/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:20:34 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/13 21:47:22 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void	smart_sleep(long duration_ms, t_philo *philo)
{
	long	start;

	if (check_death1(philo))
		return ;
	start = get_time_in_ms();
	while (get_time_in_ms() - start < duration_ms)
	{
		usleep(500);
		if (check_death1(philo))
			break ;
	}
}
