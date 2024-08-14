/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 00:48:47 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void	*arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	while (1)
	{
		print_status(philo, "is thinking");
		usleep(100);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal_time = get_time_ms();
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_status(philo, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}
