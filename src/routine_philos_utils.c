/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:18:56 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 04:18:17 by tnakas           ###   ########.fr       */
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

void	update_time_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->routines);
	philo->update_time = get_time_ms();
	pthread_mutex_unlock(&philo->routines);
}

void	update_last_time_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->routines);
	philo->last_time_meal = get_time_ms();
	pthread_mutex_unlock(&philo->routines);
}

void	philos_main_routine(t_philo *philo)
{
	while(!should_stop_simulation(philo->table))
	{
		print_thread_routine(philo, THINK);
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_thread_routine(philo, FORK);
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_thread_routine(philo, FORK);
		print_thread_routine(philo, EAT);
		ft_sleep(philo->table->eat);
		update_last_time_meal(philo);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		if (should_stop_simulation(philo->table))
			break ;
		pthread_mutex_lock(&philo->routines);
		philo->meals++;
		pthread_mutex_unlock(&philo->routines);
		update_time_philo(philo);
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
