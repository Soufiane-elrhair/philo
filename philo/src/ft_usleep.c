/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:32:12 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/22 17:38:26 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * ft_usleep - sleep the program for a certain amount of time in milliseconds
 * @time: the time in milliseconds to sleep
 * Return: void
*/
void	ft_usleep(long time)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(150);
}
