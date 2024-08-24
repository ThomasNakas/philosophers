/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 16:22:51 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*supervisor(void *arg)
{
	// t_supervisor	*s;
	t_table			*t;
	int				i;

	// s = (t_supervisor *)arg;
	t = (t_table *)arg;
	i = -1;
	while (++i < t->n_of_philos)
	{
		pthread_mutex_lock(&t->thread_supervisor);
		if (t->die <= get_time_ms() - t->arr_philos[i].last_eat)
		{
			pthread_mutex_lock(&t->thread_print);
			print_with_enum(&t->arr_philos[i], DEAD);
			pthread_mutex_unlock(&t->thread_print);
			pthread_mutex_unlock(&t->thread_supervisor);
			pthread_mutex_lock(&t->thread_supervisor);
			t->stop_simulation = 1;
			pthread_mutex_unlock(&t->thread_supervisor);
			break ;
		}
		pthread_mutex_unlock(&t->thread_supervisor);
		pthread_mutex_lock(&t->min_checker);
		if (t->min_meals != -1)
		{
			if (t->min_meals <= t->arr_philos[i].meals)
				t->n_of_full_philos++;
		}
		pthread_mutex_unlock(&t->min_checker);
	}
	if (t->min_meals != -1
		&& t->n_of_philos == t->n_of_full_philos)
		t->stop_simulation = 1;
	usleep(1000); // Add a small delay to reduce CPU usage
	return (NULL);
}
void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *) arg;
	while (true)
	{
		pthread_mutex_lock(&philo->routines);
		if (philo->table->start_simulation)
		{
			pthread_mutex_unlock(&philo->routines);
			break ;
		}
		pthread_mutex_unlock(&philo->routines);
	}
	if (philo->id % 2 == 0)
		ft_sleep(philo->table->eat / 2);
	while (true)
	{
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, THINK);
		pthread_mutex_unlock(&philo->table->thread_print);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, FORK);
		pthread_mutex_unlock(&philo->table->thread_print);
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, FORK);
		pthread_mutex_unlock(&philo->table->thread_print);
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, EAT);
		pthread_mutex_unlock(&philo->table->thread_print);
		ft_sleep(philo->table->eat);
		pthread_mutex_lock(&philo->routines);
		philo->last_eat = get_time_ms();
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_lock(&philo->routines);
		philo->meals++;
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_lock(&philo->routines);
		if (philo->table->stop_simulation == 1)
			break ;
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, SLEEP);
		pthread_mutex_unlock(&philo->table->thread_print);
		ft_sleep(philo->table->sleep);
		pthread_mutex_lock(&philo->routines);
		if (philo->table->stop_simulation == 1)
			break ;
		pthread_mutex_unlock(&philo->routines);
		ft_sleep(100);
	}
	return (NULL);
}

void	*routine_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (true)
	{
		pthread_mutex_lock(&philo->table->thread_supervisor);
		if (philo->table->start_simulation)
		{
			pthread_mutex_unlock(&philo->table->thread_supervisor);
			break ;
		}
		pthread_mutex_unlock(&philo->table->thread_supervisor);
	}
	while (true)
	{
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, THINK);
		pthread_mutex_unlock(&philo->table->thread_print);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->thread_print);
		print_with_enum(philo, FORK);
		pthread_mutex_unlock(&philo->table->thread_print);
		pthread_mutex_lock(&philo->routines);
		philo->last_eat = get_time_ms() + philo->table->die;
		pthread_mutex_unlock(&philo->routines);
		supervisor(philo->table);
		pthread_mutex_lock(&philo->routines);
		if (philo->table->stop_simulation == 1)
		{
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->routines);
			break ;
		}
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_unlock(&philo->right_fork);
	}
	return (NULL);
}