/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:37 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 00:58:16 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("%s number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each\
		_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	init_data(&data, argc, argv);
	init_philo(&data);
	i = -1;
	while (i < data.n_of_philos)
		pthread_join(data.philos[++i].thread, NULL);
	free_data(&data);
	return (0);
}
