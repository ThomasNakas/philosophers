/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:03:59 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 20:04:12 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//---------LIBRARIES----------------------
# include  <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
#include <stdbool.h>
# include "../libft/libft.h"
//---------STRUCTS------------------------
typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;

	pthread_mutex_t	routines;

	int				meals;
	long long		lifespan;

	t_table			*table;
}	t_philo;

typedef struct s_supervisor
{
	pthread_t			super;
	t_table				*table;
}	t_supervisor;

typedef struct s_table
{
	long long			start_tv;
	t_philo				*arr_philos;

	int					n_of_philos;
	long long			die;
	long long			eat;
	long long			sleep;
	int					min_meals;

	int					n_of_full_philos;
	int					someone_died;
	int					start_simulation;
	int					stop_simulation;

	pthread_mutex_t		thread_print;

	pthread_mutex_t		thread_supervisor;
	pthread_mutex_t		min_checker;
	pthread_mutex_t		change_n_of_full;
	pthread_mutex_t		thread_change_die;
	pthread_mutex_t		*forks;
}	t_table;
//---------ENUMARATORS--------------------
typedef enum e_print
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_print;

//----------------INIT--------------------
int			init_table(int argc, char **argv, t_table *table);
int			init_supervisor(int argc, char *argv, t_supervisor *s);
//----------------ROUTINE-----------------
void		*routine(void *arg);
void		*supervisor(void *arg);
//----------------UTILS_ONE---------------
long long	get_time_ms(void);
long		ft_p_atol(char *str);
void		print_with_enum(t_philo *philo, t_print mes);
//----------------UTILS_TWO---------------
int			big_sixty_ms(int a);
int			check_ms(int x, int y, int z);
void		ft_sleep(long long routine_time);
#endif