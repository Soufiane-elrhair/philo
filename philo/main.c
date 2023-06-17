/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:23:21 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/22 17:39:04 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * init - initialize the mutex for echo fork
 * @info: the struct that contains all the information
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	init_mutex(t_infos *info)
{
	int	i;

	i = -1;
	while (++i < info->num)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
		{
			write(2, "Error: mutex flaid\n", 19);
			return (EXIT_FAILURE);
		}
	}
	if (pthread_mutex_init(&info->putmsg, NULL))
	{
		write(2, "Error: mutex flaid\n", 19);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * init_infos - initialize the struct info with the arguments of the program
 * @info: the struct that contains all the information
 * @av: the arguments of the program
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	init_infos(t_infos *info, char **av)
{
	int	mutex;

	info->overeat = 0;
	info->num = ft_atoi(av[1]);
	info->time_2d = ft_atoi(av[2]);
	info->time_2e = ft_atoi(av[3]);
	info->time_2s = ft_atoi(av[4]);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num);
	if (!info->fork)
		return (write(1, "Error: malloc flaid\n", 20), EXIT_FAILURE);
	if (av[5] && av[5][0])
		info->nbr_t2e = ft_atoi(av[5]);
	else
		info->nbr_t2e = -1;
	mutex = init_mutex(info);
	if (mutex)
		return (write(1, "Error: init_mutex flaid\n", 24), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * check_args - check if the arguments are valid
 * @ac: the number of arguments
 * @av: the arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+' && j == 0)
				j++;
			if (av[i][j] < '0' || av[i][j] > '9')
				return (EXIT_FAILURE);
			j++;
		}
		if ((ft_atoi(av[i]) < 60 && i > 1 && i < 5) || ft_atoi(av[i]) < 0
			|| (av[i][0] == '\0' && i < 5) || !av[i] || !ft_atoi(av[1]))
			return (EXIT_FAILURE);
		i++;
	}
	if (i < 5)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * main - the main function of philo program
 * @ac: the number of arguments
 * @av: the arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int	main(int ac, char **av)
{
	t_infos	info;

	if (ac < 5 || ac > 6 || check_args(ac, av))
		return (write(2, "Error: Invalid agruments\n", 25), EXIT_FAILURE);
	if (init_infos(&info, av) || philosopheres(&info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
