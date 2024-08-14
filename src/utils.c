/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 01:06:19 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) +(tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lld %d %s\n", get_time_ms(), philo-> id, status);
	pthread_mutex_unlock(philo->print_mutex);
}

void	free_data(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philos)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(data->print_mutex);
	free(data->forks);
	free(data->philos);
}
