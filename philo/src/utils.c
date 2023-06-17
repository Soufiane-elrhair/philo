/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:42:21 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/22 17:38:58 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * putmsg - print the message of the philosopher with the time and the id
 * @philo: the struct that contains all the information of the philosopher
 * @action: the action of the philosopher (is eating, is sleeping, is thinking)
 * @is_done: if the philosopher is done (if he is done, the mutex is unlock)
 * Return: void
*/
void	putmsg(t_philo *philo, char *action, int is_done)
{
	pthread_mutex_lock(&philo->info->putmsg);
	printf("%zu %d %s\n", get_time_ms() - philo->start, philo->id + 1, action);
	if (!is_done)
		pthread_mutex_unlock(&philo->info->putmsg);
}
