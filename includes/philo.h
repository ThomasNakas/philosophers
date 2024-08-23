/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:03:59 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 17:27:02 by tnakas           ###   ########.fr       */
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
	int				he_is_full;
	int				he_is_alive;

	t_table			*table;
}	t_philo;

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

	pthread_mutex_t		thread_print;
	//------monitoring thread-------------
	//------change it to thread-----------
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
//----------------ROUTINE-----------------
//----------------UTILS_ONE---------------
long long	get_time_ms(void);
long		ft_p_atol(char *str);
void		print_with_enum(t_philo *philo, t_print mes);
//----------------UTILS_TWO---------------
int			big_sixty_ms(int a);
int			check_ms(int x, int y, int z);
#endif