/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:03:59 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 20:34:37 by tnakas           ###   ########.fr       */
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
//---------COLORS-------------------------
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[24m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[97m"
# define RESET "\x1b[0m"
//---------STRUCTS------------------------
typedef struct s_table t_table;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;

	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;

	pthread_mutex_t	routines;

	int				meals;
	int				run;
	long long		last_eat;
	long long		prev_last;
	int				is_counted;

	t_table			*table;
}	t_philo;

typedef struct s_supervisor
{
	pthread_t			super;
	t_table				*table;
}	t_supervisor;

struct s_table
{
	long long			start_tv;
	t_philo				*arr_philos;

	int					n_of_philos;
	long long			die;
	long long			eat;
	long long			sleep;
	int					min_meals;

	int					print_flag;

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
} ;
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
int			init_supervisor(int argc, char **argv, t_supervisor *s, t_table *table);
int			init_many_philos(t_table *t);
//----------------ROUTINE-----------------
void		*routine(void *arg);
void		*supervisor(void *arg);
//----------------PARSING-----------------
int			parsing(int argc, char **argv, t_table *t);
//----------------UTILS_ONE---------------
long long	get_time_ms(void);
long		ft_p_atol(char *str);
void		print_with_enum(t_philo *philo, t_print mes);
//----------------UTILS_TWO---------------
int			big_sixty_ms(int a);
int			check_ms(int x, int y, int z);
void		ft_sleep(long long routine_time);
long long 	max(long long a, long long b);
//----------------PROTECTED_ONE------------
int			protected_init_from_print_to_change_die(t_table *t);
int			protected_init_change_of_full(t_table *t);
int			protected_malloc_arr_philos(t_table *t);
int			protected_malloc_arr_forks(t_table *t);
int			protected_init_arr_forks(t_table *t);
//----------------PROTECTED_TWO------------
int			protected_create_one_philo(t_table *t);
int			protected_create_arr_philos(t_table *t, int i);
int			protected_mutex_init(t_table *t, int i);
int			protected_mutex_init_supervisor(t_supervisor *s);
int			final_clean(t_table *table);
#endif