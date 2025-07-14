/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:05:09 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/13 21:37:01 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_valid_number(char *str)
{
	int	j;

	j = 0;
	if (str[j] == '\0')
		return (0);
	while (is_space(str[j]))
		j++;
	if (str[j] == '+')
		j++;
	while (str[j] != '\0' && !is_space(str[j]))
	{
		if (str[j] > '9' || str[j] < '0')
			return (0);
		j++;
	}
	while (is_space(str[j]))
		j++;
	if (str[j] != '\0')
		return (0);
	return (1);
}

int	is_valid_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_check(char *str)
{
	int	res;

	res = ft_atoi(str);
	if (res <= 0 || res > INT_MAX)
		return (-1);
	return (res);
}
