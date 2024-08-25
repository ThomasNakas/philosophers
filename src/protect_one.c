/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:33:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 05:02:39 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	protected_init_from_print_to_change_die(t_table *t)
{
	if (pthread_mutex_init(&t->thread_print, NULL))
		return (3);
	if (pthread_mutex_init(&t->thread_supervisor, NULL))
	{
		pthread_mutex_destroy(&t->thread_print);
		return (4);
	}
	if (pthread_mutex_init (&t->thread_change_die, NULL))
	{
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		return (5);
	}
	if (pthread_mutex_init(&t->min_checker, NULL))
	{
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		return (6);
	}
	return (0);
}

int	protected_init_change_of_full(t_table *t)
{
	if (pthread_mutex_init(&t->change_n_of_full, NULL))
	{
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		return (7);
	}
	return (0);
}

int	protected_malloc_arr_philos(t_table *t)
{
	t->arr_philos = (t_philo *)malloc(sizeof(t_philo) * t->n_of_philos);
	if (!t->arr_philos)
	{
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		return (8);
	}
	return (0);
}

int	protected_malloc_arr_forks(t_table *t)
{
	t->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* t->n_of_philos);
	if (!t->forks)
	{
		free(t->arr_philos);
		pthread_mutex_destroy(&t->change_n_of_full);
		pthread_mutex_destroy(&t->min_checker);
		pthread_mutex_destroy(&t->thread_change_die);
		pthread_mutex_destroy(&t->thread_supervisor);
		pthread_mutex_destroy(&t->thread_print);
		return (9);
	}
	return (0);
}

int	protected_init_arr_forks(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->forks[i]);
			free(t->forks);
			free(t->arr_philos);
			pthread_mutex_destroy(&t->change_n_of_full);
			pthread_mutex_destroy(&t->min_checker);
			pthread_mutex_destroy(&t->thread_change_die);
			pthread_mutex_destroy(&t->thread_supervisor);
			pthread_mutex_destroy(&t->thread_print);
			return (i + 10);
		}
	}
	return (0);
}