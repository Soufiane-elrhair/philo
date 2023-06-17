/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:29:23 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/28 09:10:40 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * init_philo - initialize the struct philo
 * @philo: the struct that contains all the information about the philo
 * @info: the struct that contains all the information about the program
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	init_philo(t_philo *philo, t_infos *info)
{
	int		i;
	long	start_time;

	start_time = get_time_ms();
	i = -1;
	while (++i < info->num)
	{
		philo[i].id = i;
		philo[i].last_eat = 0;
		philo[i].rf = &info->fork[(i + 1) % info->num];
		philo[i].lf = &info->fork[i];
		philo[i].info = info;
		philo[i].start = start_time;
		philo[i].is_eaten = 0;
		if (pthread_mutex_init(&philo[i].check_death, NULL) != 0)
			return (write(2, "Error: mutex init failed\n", 25), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * philo_rotune - the function that each philosopheres will run in a thread
 	and do the actions of the philosopheres (eat, sleep, think)
 * @ptr: the struct that contains all the information about the philo
 * Return: NULL
*/
void	*philo_rotune(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(philo->lf);
		putmsg(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->rf);
		putmsg(philo, "has taken a fork", 0);
		putmsg(philo, "is eating", 0);
		pthread_mutex_lock(&philo->check_death);
		if (philo->info->nbr_t2e > 0)
			++philo->is_eaten;
		philo->last_eat = get_time_ms();
		pthread_mutex_unlock(&philo->check_death);
		ft_usleep(philo->info->time_2e);
		putmsg(philo, "is sleeping", 0);
		pthread_mutex_unlock(philo->lf);
		pthread_mutex_unlock(philo->rf);
		ft_usleep(philo->info->time_2s);
		putmsg(philo, "is thinking", 0);
	}
	return (NULL);
}

/**
 * check_death - check if a philosopher is dead or not 
 	and print the message if he is dead
 * @philo: struct with all info about philosopheres
 * Return: 1 if a philosopher is dead, 0 otherwise
*/
int	check_death(t_philo *philo)
{
	int		i;
	long	diff_time;

	i = -1;
	while (++i < philo->info->num)
	{
		pthread_mutex_lock(&philo[i].check_death);
		diff_time = get_time_ms() - philo[i].last_eat;
		if (philo[i].is_eaten == philo[i].info->nbr_t2e)
		{
			philo[i].is_eaten++;
			philo[i].info->overeat++;
		}
		if (philo[i].info->overeat >= philo[i].info->num)
		{
			pthread_mutex_lock(&philo[i].info->putmsg);
			printf("\033[0;32mall philos eate at least %lld times\033[0m\n",
				philo[i].info->nbr_t2e);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].check_death);
		if (diff_time > philo->info->time_2d)
			return (putmsg(&philo[i], "\033[91mdied\033[0m", 1), 1);
	}
	return (0);
}

/**
 * create_philo - create philosopheres threads
 * @philo: struct with all info about philosopheres
 * @num: number of philosopheres
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	create_philo(t_philo *philo, t_infos *info)
{
	int			i;

	info->th = (pthread_t *)malloc(sizeof(pthread_t) * info->num);
	if (!info->th)
		return (write(2, "Error: malloc failed\n", 21), EXIT_FAILURE);
	i = -1;
	while (++i < info->num)
	{
		philo[i].last_eat = get_time_ms();
		if (pthread_create(&info->th[i], NULL, &philo_rotune, &philo[i]))
			return (write(2, "Error: pthread_create failed\n", 29), 1);
	}
	while (!check_death(philo))
		;
	return (EXIT_SUCCESS);
}

/**
 * philosopheres - create philosopheres threads and init mutex
 * @info: struct with all info about program
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	philosopheres(t_infos *info)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * info->num);
	if (!philos)
		return (write(2, "Error: malloc failed\n", 21), EXIT_FAILURE);
	if (init_philo(philos, info) || create_philo(philos, info))
		return (free(philos), EXIT_FAILURE);
	return (free(philos), EXIT_SUCCESS);
}
