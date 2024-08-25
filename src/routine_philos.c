/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 05:18:19 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *) arg;
	philos_wait_to_start(philo);
	if (philo->id % 2 == 0)
	{
		print_thread_routine(philo, SLEEP);
		ft_sleep(philo->table->eat / 2);
	}
	philos_main_routine(philo);
	return (NULL);
}

void	*routine_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_thread_routine(philo, FORK);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		while(should_stop_simulation(philo->table))
		{
			ft_sleep(100);
			update_last_time_meal(philo);
		}
	return (NULL);
}
