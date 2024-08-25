/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_supervisor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:14 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 16:11:12 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	died_condition(t_table *t, int i)
{
	t->print_flag = 1;
	print_thread_routine(&t->arr_philos[i], DEAD);
	pthread_mutex_lock(&t->thread_supervisor);
	t->stop_simulation = 1;
	pthread_mutex_unlock(&t->thread_supervisor);
}

void	meals_update(t_table *t, int i)
{
	pthread_mutex_lock(&t->arr_philos[i].routines);
	if (t->min_meals <= t->arr_philos[i].meals && i % 2
		&& t->n_of_philos % 2 != 0)
	{
		t->n_of_full_philos++;
		t->arr_philos[i].is_counted = 1;
		pthread_mutex_lock(&t->thread_supervisor);
		t->stop_simulation = 1;
		pthread_mutex_unlock(&t->thread_supervisor);
	}
	pthread_mutex_unlock(&t->arr_philos[i].routines);
}

void	died_cond_and_meals_update(t_table *t)
{
	int		i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		pthread_mutex_lock(&t->arr_philos[i].routines);
		if (get_time_ms() - t->die > t->arr_philos[i].last_time_meal
			&& (t->print_flag == 0))
		{
			pthread_mutex_unlock(&t->arr_philos[i].routines);
			died_condition(t, i);
			break ;
		}
		pthread_mutex_unlock(&t->arr_philos[i].routines);
		pthread_mutex_lock(&t->min_checker);
		if (t->min_meals != -1 && t->arr_philos[i].is_counted == 0)
			meals_update(t, i);
		pthread_mutex_unlock(&t->min_checker);
		if (i == t->n_of_philos - 1)
			i = 0;
	}
}

void	*supervisor(void *arg)
{
	t_table			*t;

	t = (t_table *)arg;
	died_cond_and_meals_update(t);
	if (t->min_meals != -1
		&& t->n_of_philos == t->n_of_full_philos)
		t->stop_simulation = 1;
	usleep(1000);
	return (NULL);
}
