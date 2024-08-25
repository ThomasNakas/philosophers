/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:14 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 00:31:16 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	died_condition(t_table *t, int	i)
{
	pthread_mutex_lock(&t->thread_print);
	t->print_flag = 1;
	pthread_mutex_unlock(&t->thread_print);
	pthread_mutex_lock(&t->thread_print);
	print_with_enum(&t->arr_philos[i], DEAD);
	pthread_mutex_unlock(&t->thread_print);
	t->stop_simulation = 1;
	pthread_mutex_unlock(&t->thread_supervisor);
}

void	meals_update(t_table *t, int i)
{
	if (t->min_meals <= t->arr_philos[i].meals)
	{
		t->n_of_full_philos++;
		t->arr_philos[i].is_counted = 1;
	}
}

void	died_cond_and_meals_update(t_table *t)
{
	int		i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		pthread_mutex_lock(&t->arr_philos[i].routines);
		if ((t->die <= t->arr_philos[i].last_eat - t->arr_philos[i].prev_last)
		&& (t->print_flag == 0))
		{
			died_condition(t, i);
			break ;
		}
		pthread_mutex_unlock(&t->arr_philos[i].routines);
		pthread_mutex_lock(&t->min_checker);
		if (t->min_meals != -1 && t->arr_philos[i].is_counted == 0)
			meals_update(t, i);
		pthread_mutex_unlock(&t->min_checker);
	}
}

void	*supervisor(void *arg)
{
	t_table			*t;

	t = (t_table *)arg;
	died_cond_and_meals_update(t);
	if (t->min_meals != -1
		&& t->n_of_philos == t->n_of_full_philos)
		{
			t->stop_simulation = 1;
		}
	usleep(1000);
	return (NULL);
}