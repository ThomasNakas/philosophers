/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 02:11:38 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	big_sixty_ms(int a)
{
	return (a >= 60000);
}

int	check_ms(int x, int y, int z)
{
	return (big_sixty_ms(x)
		|| big_sixty_ms(y) 
		|| big_sixty_ms(z));
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	i = -1;
	data->starting_tv = get_time_ms();
	data->n_of_philos = ft_p_atol(argv[1]);
	data->time_to_die = ft_p_atol(argv[2]) * 1000;
	data->time_to_eat = ft_p_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_p_atol(argv[4]) * 1000;
	if (!check_ms(data->time_to_die, data->time_to_eat, data->time_to_sleep))
		return (1);
	if (argc == 6)
		data->meals_must_eat = f_p_atol(argv[5]);
	else
		data->meals_must_eat = -1;
	if (allocate_protection((void **)&data->philos,
			sizeof(t_philo) * data->n_of_philos))
		return (1);
	if (allocate_protection((void **)&data->forks,
			sizeof(pthread_mutex_t) * data->n_of_philos))
	{
		free(data->philos);
		return (1);
	}
	if (allocate_protection((void **)&data->print_mutex,
			sizeof(pthread_mutex_t)))
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}
	if (pthread_mutex_init(data->print_mutex, NULL) != 0)
	{
		free(data->philos);
		free(data->forks);
		free(data->print_mutex);
		return (1);
	}
	// if (init_protection(data->forks, data->n_of_philos) != 0)
	// {
	// 	free(data->philos);
	// 	free(data->forks);
	// 	pthread_mutex_destroy(data->print_mutex);
	// 	free(data->print_mutex);
	// 	return (1);
	// }
	data->one_died = 0;
	data->all_full = 0;
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].right_fork
			= &(data->forks[(i + 1) % data->n_of_philos]);
		// if (create_protection(data->philos, i,
		// 		data->forks, data->n_of_philos) == 1)
		// 	return (1);
	}
	i = -1;
	// while (++i < data->n_of_philos)
	// 	pthread_join(data->philos[i].thread, NULL);
	return (0);
}
