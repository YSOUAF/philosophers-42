/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:35 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/14 13:38:45 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init(&data, ac, av))
		return (1);
	if (data.nbr_philo == 1)
		return (case_one(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
