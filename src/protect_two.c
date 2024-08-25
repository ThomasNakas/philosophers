/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:13:04 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 17:50:39 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	protected_create_one_philo(t_table *t)
{
	int	j;

	j = -1;
	t->arr_philos[0].id = 1;
	t->arr_philos[0].meals = 0;
	t->arr_philos[0].left_fork = 0;
	t->arr_philos[0].table = t;
	t->arr_philos[0].last_time_meal = get_time_ms();
	t->arr_philos[0].is_counted = 0;
	if (pthread_create(&(t->arr_philos[0].thread),
			NULL, routine_one, &(t->arr_philos[0])))
	{
		j = -1;
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[t->n_of_philos - j - 1]);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		free(t->forks);
		printf("Error: Threads creation failed");
		return (11 + t->n_of_philos);
	}
	return (0);
}

int	protected_mutex_init(t_table *t, int i)
{
	int	j;

	j = -1;
	if (pthread_mutex_init(&t->arr_philos[i].routines, NULL))
	{
		while (--i >= 0)
			pthread_join((t->arr_philos[i].thread), NULL);
		while (--i >= 0)
			pthread_mutex_destroy(&t->arr_philos[i].routines);
		free(t->arr_philos);
		j = -1;
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[j]);
		free(t->forks);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		printf("Error: Mutexes initialization failed");
		return (i + 13 + 3 * (t->n_of_philos));
	}
	return (0);
}

int	protected_create_arr_philos(t_table *t, int i)
{
	int	j;

	j = -1;
	if (pthread_create(&(t->arr_philos[i].thread),
			NULL, routine, &(t->arr_philos[i])))
	{
		j = -1;
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[t->n_of_philos - j - 1]);
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->arr_philos[t->n_of_philos
				- j - 1].routines);
		while (--i >= 0)
			pthread_join((t->arr_philos[i].thread), NULL);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		free(t->forks);
		printf("Error: Threads creation failed");
		return (i + 12 + 2 * (t->n_of_philos));
	}
	return (0);
}

int	protected_mutex_init_supervisor(t_supervisor *s)
{
	int	j;

	j = -1;
	while (++j < s->table->n_of_philos)
		pthread_mutex_destroy(&s->table->arr_philos[j].routines);
	j = -1;
	while (++j < s->table->n_of_philos)
		pthread_join((s->table->arr_philos[j].thread), NULL);
	free(s->table->arr_philos);
	j = -1;
	while (++j < s->table->n_of_philos)
		pthread_mutex_destroy(&s->table->forks[s->table->n_of_philos - j - 1]);
	free(s->table->forks);
	pthread_mutex_destroy(&s->table->change_n_of_full);
	pthread_mutex_destroy(&s->table->min_checker);
	pthread_mutex_destroy(&s->table->thread_print);
	pthread_mutex_destroy(&s->table->thread_supervisor);
	printf("Error: Threads creation failed");
	return (j + 14 + 3 * (s->table->n_of_philos));
}

int	final_clean(t_table *table)
{
	int	j;

	j = -1;
	while (++j < table->n_of_philos)
		pthread_mutex_destroy(&table->arr_philos[table->n_of_philos
			- j - 1].routines);
	if (table->arr_philos)
		free(table->arr_philos);
	j = -1;
	while (++j < table->n_of_philos)
		pthread_mutex_destroy(&table->forks[table->n_of_philos - j - 1]);
	if (table->forks)
		free(table->forks);
	pthread_mutex_destroy(&table->change_n_of_full);
	pthread_mutex_destroy(&table->min_checker);
	pthread_mutex_destroy(&table->thread_print);
	pthread_mutex_destroy(&table->thread_supervisor);
	return (j + 14 + 3 * (table->n_of_philos));
}
