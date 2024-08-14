/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:03:59 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 01:03:10 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include  <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include "../libft/libft.h"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	struct			s_data *data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_must_eat;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*forks;
}	t_data;
//----------------INIT--------------------
void		init_data(t_data *data, int argc, char **argv);
void		init_philo(t_data *data);
//----------------ROUTINE-----------------
void		*philo_routine(void	*arg);
//----------------UTILS-------------------
long long	get_time_ms(void);
void		print_status(t_philo *philo, const char *status);
void		free_data(t_data	*data);
#endif