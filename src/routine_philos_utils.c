/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:18:56 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 02:19:27 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int should_stop_simulation(t_table *table)
{
	int res;

	pthread_mutex_lock((&table->thread_supervisor));
	res = table->stop_simulation;
	pthread_mutex_unlock((&table->thread_supervisor));
	return (res);
}

void	philos_main_routine(t_philo *philo)
{
	while(!should_stop_simulation(philo->table))
	{
		print_thread_routine(philo, THINK);
		// pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_thread_routine(philo, FORK);
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		// pthread_mutex_lock(&philo->left_fork);
		print_thread_routine(philo, FORK);
		print_thread_routine(philo, EAT);
		pthread_mutex_lock(&philo->routines);
		philo->prev_last = philo->last_eat;
		philo->last_eat = get_time_ms() - max(philo->last_eat,
			philo->table->start_tv);
		pthread_mutex_unlock(&philo->routines);
		// supervisor(philo->table);
		ft_sleep(philo->table->eat);
		// pthread_mutex_unlock(&philo->left_fork);
		// pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->routines);
		philo->meals++;
		pthread_mutex_unlock(&philo->routines);
		if (should_stop_simulation(philo->table))
			break ;
		print_thread_routine(philo, SLEEP);
		ft_sleep(philo->table->sleep);
	}
}

void	philos_wait_to_start(t_philo *philo)
{
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
}
