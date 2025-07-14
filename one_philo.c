/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:20:08 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:40:12 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[0];
	data->start_time = get_time_in_ms();
	messages(FORK, philo);
	smart_sleep(data->t_die, data->philos);
	messages(DIED, philo);
	ft_exit(data);
	return (0);
}
