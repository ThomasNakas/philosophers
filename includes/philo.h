/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:03:59 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 01:47:12 by tnakas           ###   ########.fr       */
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
	long long		lifespan;
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
	int				all_full;
	int				one_died;
	long long		starting_tv;
}	t_data;

typedef enum e_print
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_print;

//----------------INIT--------------------
int			init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);
//----------------ROUTINE-----------------
void		*eating_routine(void	*arg);
//----------------UTILS-------------------
long long	get_time_ms(void);
void		print_status(t_philo *philo, const char *status);
void		print_with_enum(t_philo *philo, t_print mes);
void		free_data(t_data	*data);
long		ft_p_atol(char *str);
#endif