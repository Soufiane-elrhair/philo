/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:04:45 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/22 17:38:08 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	unsigned long int	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\n'
			|| *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\f'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result = result * 10 + (*str - 48);
		if (result >= LONG_MAX)
			return (-1);
		str++;
	}
	return (result * sign);
}
