/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 21:58:23 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_thread_routine(philo, FORK);
	update_last_time_meal(philo);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->n_of_philos == 1)
	{
		routine_one_philo(philo);
		return (NULL);
	}
	philos_wait_to_start(philo);
	if (philo->id % 2 == 0)
	{
		print_thread_routine(philo, SLEEP);
		ft_sleep(philo->table->sleep / 2);
	}
	philos_main_routine(philo);
	return (NULL);
}

// void	*routine_one(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) arg;
// 	philos_wait_to_start(philo);
// 	while (!should_stop_simulation(philo->table))
// 	{
// 		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
// 		print_thread_routine(philo, FORK);
// 		ft_sleep(1);
// 		update_last_time_meal(philo);
// 		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
// 		if (should_stop_simulation(philo->table))
// 			break ;
// 	}
// 	return (NULL);
// }
