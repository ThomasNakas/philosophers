/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 02:04:43 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	print_with_enum(philo, FORK);
	pthread_mutex_lock(&philo->print_mutex);
	philo->lifespan = get_time_ms() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->print_mutex);
	pthread_mutex_unlock(&philo->right_fork);
}

void	*eating_routine(void	*arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	print_with_enum(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	print_with_enum(philo, FORK);
	print_with_enum(philo, EAT);
	pthread_mutex_lock(&philo->print_mutex);
	philo->last_meal_time = get_time_ms() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->print_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->print_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->print_mutex);
	print_status(philo, SLEEP);
	usleep(data->time_to_sleep * 1000);
	return ;
}
