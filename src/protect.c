/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:33:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 02:14:54 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//protect aloc
int	allocate_protection(void	**mem, size_t size)
{
	if (!(mem))
		return (1);
	*mem = malloc(size);
	if (!*(mem))
		return (1);
	return (0);
}

protect init
int	init_protection(pthread_mutex_t	*forks, int n_of_philos)
{
	int	i;

	i = -1;
	while (++i < n_of_philos)
	{
		if ((pthread_mutex_init(&forks[i], NULL)) != 0)
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
		return (1);
	}
	return (0);
}

protect creating
int	create_protection(t_philo *philos, int i,
			pthread_mutex_t *forks, int n_of_philos)
{
	if (pthread_create(&(philos[i].thread),
			NULL, philo_routine, &(philos[i])) != 0)
	{
		while (--i >= 0)
		{
			pthread_join(philos[i].thread, NULL);
			pthread_mutex_destroy(&forks[i]);
		}
		return (1);
	}
	return (0);
}
