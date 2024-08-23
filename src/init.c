/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 21:44:11 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_table(int	argc, char **argv, t_table *table)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("%s number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each\
		_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	table->n_of_philos = ft_p_atol(argv[1]);
	table->die = ft_p_atol(argv[2]) * 1000;
	table->eat = ft_p_atol(argv[3]) * 1000;
	table->sleep = ft_p_atol(argv[4]) * 1000;
	if (argc == 6)
		table->min_meals = ft_p_atol(argv[5]);
	else
		table->min_meals = -1;
	if (table->n_of_philos <= 0 || table->die == 1
		|| table->eat == 1 || table->sleep == 1
		|| table->min_meals <= 0
		|| check_ms(table->die, table->eat, table->sleep))
		return (1);
	table->n_of_full_philos = 0;
	table->someone_died = 0;
	table->start_simulation = 0;
	table->stop_simulation = 0;
	if (pthread_mutex_init(&table->thread_print, NULL))
		return (2);
	if (pthread_mutex_init(&table->thread_supervisor, NULL))
	{
		pthread_mutex_destroy(&table->thread_print);
		return (3);
	}
	if (pthread_mutex_init (&table->thread_change_die, NULL))
	{
		pthread_mutex_destroy(&table->thread_supervisor);
		pthread_mutex_destroy(&table->thread_print);
		return (4);
	}
	if (pthread_mutex_init(&table->min_checker, NULL))
	{
		pthread_mutex_destroy(&table->thread_change_die);
		pthread_mutex_destroy(&table->thread_supervisor);
		pthread_mutex_destroy(&table->thread_print);
		return (5);
	}
	if (pthread_mutex_init(&table->change_n_of_full, NULL))
	{
		pthread_mutex_destroy(&table->thread_change_die);
		pthread_mutex_destroy(&table->thread_supervisor);
		pthread_mutex_destroy(&table->thread_print);
		return (6);
	}
	table->arr_philos = (t_philo *)malloc(sizeof(t_philo) * table->n_of_philos);
	if (!table->arr_philos)
	{
		pthread_mutex_destroy(&table->change_n_of_full);
		pthread_mutex_destroy(&table->min_checker);
		pthread_mutex_destroy(&table->thread_change_die);
		pthread_mutex_destroy(&table->thread_supervisor);
		pthread_mutex_destroy(&table->thread_print);
		return (7);
	}
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->n_of_philos);
	if (!table->forks)
	{
		pthread_mutex_destroy(&table->change_n_of_full);
		pthread_mutex_destroy(&table->min_checker);
		pthread_mutex_destroy(&table->thread_change_die);
		pthread_mutex_destroy(&table->thread_supervisor);
		pthread_mutex_destroy(&table->thread_print);
		free(table->arr_philos);
		return (8);
	}
	i = -1;
	while (++i < table->n_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			pthread_mutex_destroy(&table->change_n_of_full);
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->min_checker);
			pthread_mutex_destroy(&table->thread_change_die);
			pthread_mutex_destroy(&table->thread_supervisor);
			pthread_mutex_destroy(&table->thread_print);
			free(table->arr_philos);
			free(table->forks);
			return (i + 9);
		}
	}
	i = -1;
	if (table->n_of_full_philos == 1)
	{
		if (pthread_create(&(table->arr_philos[0].thread), NULL, routine, NULL))
		{
			j = -1;
			while (++j < table->n_of_philos)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->arr_philos);
			pthread_mutex_destroy(&table->change_n_of_full);
			pthread_mutex_destroy(&table->min_checker);
			pthread_mutex_destroy(&table->thread_change_die);
			pthread_mutex_destroy(&table->thread_print);
			pthread_mutex_destroy(&table->thread_supervisor);
			free(table->forks);
			return (i + 10 + table->n_of_philos);
		}
	}
	else
	{
		while (++i < table->n_of_philos)
		{
			if (pthread_create(&(table->arr_philos[i].thread),
					NULL, routine, NULL))
			{
				j = -1;
				while (++j < table->n_of_philos)
					pthread_mutex_destroy(&table->forks[i]);
				while (--i >= 0)
					pthread_join(&(table->arr_philos[i].thread), NULL);
				free(table->arr_philos);
				pthread_mutex_destroy(&table->change_n_of_full);
				pthread_mutex_destroy(&table->min_checker);
				pthread_mutex_destroy(&table->thread_change_die);
				pthread_mutex_destroy(&table->thread_print);
				pthread_mutex_destroy(&table->thread_supervisor);
				free(table->forks);
				return (i + 11 + 2 * (table->n_of_philos));
			}
			table->arr_philos[i].id = i + 1;
			table->arr_philos[i].meals = 0;
			table->arr_philos[i].left_fork = table->forks[i];
			table->arr_philos[i].right_fork
				= table->forks[table->arr_philos[i].id % table->n_of_philos];
			table->arr_philos[i].table = table;
			if (pthread_mutex_init(&table->arr_philos[i].routines, NULL))
			{
				while (--i >= 0)
					pthread_mutex_destroy(&table->arr_philos[i].routines);
				while (i-- > 0)
					pthread_join(&(table->arr_philos[i].thread), NULL);
				free(table->arr_philos);
				j = -1;
				while (++j < table->n_of_philos)
					pthread_mutex_destroy(&table->forks[i]);
				free(table->forks);
				pthread_mutex_destroy(&table->change_n_of_full);
				pthread_mutex_destroy(&table->min_checker);
				pthread_mutex_destroy(&table->thread_change_die);
				pthread_mutex_destroy(&table->thread_print);
				pthread_mutex_destroy(&table->thread_supervisor);
				return (i + 12 + 3 * (table->n_of_philos));
			}
		}
	}
	table->start_tv = get_time_ms();
	pthread_mutex_lock(&table->thread_supervisor);
	table->start_simulation = 1;
	pthread_mutex_unlock(&table->thread_supervisor);
}

int	init_supervisor(int argc, char *argv, t_supervisor *s)
{
	int	j;

	if (init_table(argc, argv, s->table))
		return (1);
	j = -1;
	if (pthread_mutex_create(&s->super, NULL, supervisor, NULL))
	{
		j = -1;
		while (++j < s->table->n_of_philos)
			pthread_mutex_destroy(&s->table->arr_philos[j].routines);
		j = -1;
		while (++j < s->table->n_of_philos)
			pthread_join(&(s->table->arr_philos[j].thread), NULL);
		free(s->table->arr_philos);
		j = -1;
		while (++j < s->table->n_of_philos)
			pthread_mutex_destroy(&s->table->forks[j]);
		free(s->table->forks);
		pthread_mutex_destroy(&s->table->change_n_of_full);
		pthread_mutex_destroy(&s->table->min_checker);
		pthread_mutex_destroy(&s->table->thread_change_die);
		pthread_mutex_destroy(&s->table->thread_print);
		pthread_mutex_destroy(&s->table->thread_supervisor);
		return (j + 13 + 3 * (s->table->n_of_philos));
	}
}
