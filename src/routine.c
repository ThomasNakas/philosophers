/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 12:32:34 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*supervisor(void *arg)
{
	t_supervisor	*s;
	int				i;

	s = (t_supervisor *)arg;
	i = -1;
	while (++i < s->table->n_of_philos)
	{
		pthread_mutex_lock(&s->table->thread_supervisor);
		if (s->table->die <= s->table->arr_philos[i].lifespan)
		{
			pthread_mutex_lock(&s->table->thread_print);
			print_with_enum(&s->table->arr_philos[i], DEAD);
			pthread_mutex_unlock(&s->table->thread_print);
			pthread_mutex_lock(&s->table->thread_change_die);
			s->table->someone_died = 1;
			pthread_mutex_unlock(&s->table->thread_change_die);
			pthread_mutex_unlock(&s->table->thread_supervisor);
			s->table->stop_simulation = 1;
			break ;
		}
		pthread_mutex_unlock(&s->table->thread_supervisor);
		pthread_mutex_lock(&s->table->min_checker);
		if (s->table->min_meals != -1)
		{
			if (s->table->min_meals <= s->table->arr_philos[i].meals)
				s->table->n_of_full_philos++;
		}
		pthread_mutex_unlock(&s->table->min_checker);
	}
	if (s->table->min_meals != -1
		&& s->table->n_of_philos == s->table->n_of_full_philos)
		s->table->stop_simulation = 1;
	return (NULL);
}

void	*routine(void *arg)
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
		philo->meals++;
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_lock(&philo->routines);
		if (philo->table->stop_simulation == 1)
			break ;
		pthread_mutex_unlock(&philo->routines);
		pthread_mutex_lock(&philo->routines);
		philo->lifespan = get_time_ms() - philo->table->start_simulation;
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
		philo->lifespan = get_time_ms() + philo->table->start_tv;
		pthread_mutex_unlock(&philo->routines);
		ft_sleep(philo->table->die);
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