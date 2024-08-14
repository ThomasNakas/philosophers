/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 00:55:54 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	data->n_of_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->meals_must_eat = atoi(argv[5]);
	else
		data->meals_must_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->n_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_philos);
	if (!data->philos || !data->forks)
		return ;
	pthread_mutex_init(data->print_mutex, NULL);
	i = -1;
	while (++i < data->n_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	if (!(data->philos))
		return ;
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].right_fork
			= &(data->forks[(i + 1) % data->n_of_philos]);
		pthread_create(&(data->philos[i].thread),
			NULL, philo_routine, &(data->philos[i]));
		data->philos[i].data = data;
	}
	i = -1;
	while (++i < data->n_of_philos)
		pthread_join(data->philos[i].thread, NULL);
}
