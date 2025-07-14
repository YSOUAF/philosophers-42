/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:19:19 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/13 21:40:47 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_signe(const char *s, int *i, int *signe)
{
	if (s[*i] == '+')
		(*i)++;
	else if (s[*i] == '-')
	{
		*signe *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			i;
	long		nbr;
	long		n;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	check_signe(str, &i, &sign);
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = nbr;
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)(nbr * sign));
}
