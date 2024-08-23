/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:40 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 17:33:52 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (true)
	{
		pthread_mutex_lock(&philo->table->thread_supervisor);
		if (&philo->table->start_simulation)
		{
			pthread_mutex_ulock(&philo->table->thread_supervisor);
			break ;
		}
		pthread_mutex_unlock(&philo->table->thread_supervisor);
	}
	while (true && !philo->he_is_full)
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
		pthread_mutex_lock(&philo->table->thread_supervisor);
		if ((get_time_ms() - philo->table->start_tv) >= philo->table->die)
		{
			pthread_mutex_lock(&philo->table->thread_change_die);
			philo->table->someone_died = 1;
			pthread_mutex_unlock(&philo->table->thread_change_die);
			pthread_mutex_lock(&philo->table->thread_supervisor);
			break ;
		}
		pthread_mutex_lock(&philo->table->thread_supervisor);
		if (philo->table->min_meals != -1)
		{
			philo->meals++;
			pthread_mutex_lock(&philo->table->min_checker);
			if ((philo->table->min_meals <= philo->meals)
				&& philo->table->min_meals >= 1)
			{
				pthread_mutex_lock(&philo->table->change_n_of_full);
				philo->table->n_of_full_philos++;
				pthread_mutex_unlock(&philo->table->change_n_of_full);
				pthread_mutex_unlock(&philo->table->min_checker);
				pthread_mutex_lock(&philo->table->thread_supervisor);
				philo->he_is_full = 1;
				break ;
			}
			pthread_mutex_unlock(&philo->table->min_checker);
		}
		pthread_mutex_unlock(&philo->table->thread_supervisor);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	// add the last time that has eat + current time
	//he must unlock left
	//he must unlock the right
	// sleep
}