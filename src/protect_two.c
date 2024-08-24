/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:13:04 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 14:25:13 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	protected_create_one_philo(t_table *t)
{
	int	j;

	if (pthread_create(&(t->arr_philos[0].thread), NULL, routine, &(t->arr_philos[0])))
	{
		j = -1;
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[j]);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		free(t->forks);
		return (11 + t->n_of_philos);
	}
	pthread_join(t->arr_philos[0].thread, NULL);
	return (0);
}

int	protected_create_arr_philos(t_table *t, int i)
{
	int	j;

	j = -1;
	if (pthread_create(&(t->arr_philos[i].thread), NULL, routine, &(t->arr_philos[i])))
	{
		j = -1;
		printf("here2\n");
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[i]);
		while (--i >= 0)
			pthread_join((t->arr_philos[i].thread), NULL);
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		free(t->forks);
		return (i + 12 + 2 * (t->n_of_philos));
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
			pthread_mutex_destroy(&t->arr_philos[i].routines);
		while (i-- > 0)
			pthread_join( (t->arr_philos[i].thread), NULL);
		free(t->arr_philos);
		j = -1;
		while (++j < t->n_of_philos)
			pthread_mutex_destroy(&t->forks[i]);
		free(t->forks);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_print);
		pthread_mutex_destroy(&t->thread_supervisor);
		return (i + 13 + 3 * (t->n_of_philos));
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
		pthread_mutex_destroy(&s->table->forks[j]);
	free(s->table->forks);
	pthread_mutex_destroy(&s->table->change_n_of_full);
	pthread_mutex_destroy(&s->table->min_checker);
	pthread_mutex_destroy(&s->table->thread_change_die);
	pthread_mutex_destroy(&s->table->thread_print);
	pthread_mutex_destroy(&s->table->thread_supervisor);
	return (j + 14 + 3 * (s->table->n_of_philos));
}
