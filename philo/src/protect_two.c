/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:13:04 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 22:16:05 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	protected_create_one_philo(t_table *t)
// {
// 	int	j;

// 	j = -1;
// 	t->arr_philos[0].id = 1;
// 	t->arr_philos[0].meals = 0;
// 	t->arr_philos[0].left_fork = 0;
// 	t->arr_philos[0].table = t;
// 	t->arr_philos[0].last_time_meal = get_time_ms();
// 	t->arr_philos[0].is_counted = 0;
// 	if (pthread_create(&(t->arr_philos[0].thread),
// 			NULL, routine_one, &(t->arr_philos[0])))
// 	{
// 		j = t->n_of_philos;
// 		while (--j >= 0)
// 			pthread_mutex_destroy(&t->forks[j]);
// 		free(t->forks);
// 		free(t->arr_philos);
// 		pthread_mutex_destroy(&t->change_n_of_full);
// 		pthread_mutex_destroy(&t->min_checker);
// 		pthread_mutex_destroy(&t->thread_supervisor);
// 		pthread_mutex_destroy(&t->thread_print);
// 		printf("Error: Thread(s) creation failure");
// 		return (11 + t->n_of_philos);
// 	}
// 	pthread_join(t->arr_philos[0].thread, NULL);
// 	return (0);
// }

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
		j = t->n_of_philos;
		while (--j >= 0)
			pthread_mutex_destroy(&t->forks[j]);
		free(t->forks);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		printf("Error: Mutexes initialization failure");
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
		while (--i >= 0)
			pthread_join((t->arr_philos[i].thread), NULL);
		j = t->n_of_philos;
		while (--j >= 0)
			pthread_mutex_destroy(&t->arr_philos[j].routines);
		free(t->arr_philos);
		j = t->n_of_philos;
		while (--j >= 0)
			pthread_mutex_destroy(&t->forks[j]);
		free(t->forks);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		printf("Error: Threads creation failure");
		return (i + 12 + 2 * (t->n_of_philos));
	}
	return (0);
}

int	protected_mutex_init_supervisor(t_supervisor *s)
{
	int	j;

	j = s->table->n_of_philos;
	while (--j >= 0)
		pthread_join((s->table->arr_philos[j].thread), NULL);
	j = s->table->n_of_philos;
	while (--j >= 0)
		pthread_mutex_destroy(&s->table->arr_philos[j].routines);
	free(s->table->arr_philos);
	j = s->table->n_of_philos;
	while (--j >= 0)
		pthread_mutex_destroy(&s->table->forks[j]);
	free(s->table->forks);
	free(s->table->arr_philos);
	pthread_mutex_destroy(&s->table->change_n_of_full);
	pthread_mutex_destroy(&s->table->min_checker);
	pthread_mutex_destroy(&s->table->thread_supervisor);
	pthread_mutex_destroy(&s->table->thread_print);
	printf("Error: Threads creation failure");
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
	return (0);
}
