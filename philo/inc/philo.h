/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:27:15 by selrhair          #+#    #+#             */
/*   Updated: 2023/05/27 19:39:09 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_infos
{
	int				num;
	long long		time_2d;
	long long		time_2e;
	long long		time_2s;
	long long		nbr_t2e;
	long long		overeat;
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	putmsg;

}		t_infos;

typedef struct s_philosophere
{
	int				id;
	size_t			start;
	long			last_eat;
	int				is_eaten;
	pthread_mutex_t	check_death;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*lf;
	t_infos			*info;

}	t_philo;

void		putmsg(t_philo *philo, char *action, int is_done);
int			philosopheres(t_infos *info);
long long	ft_atoi(const char *str);
void		ft_usleep(long time);
long		get_time_ms(void);

#endif