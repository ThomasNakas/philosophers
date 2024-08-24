/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 15:27:57 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_table(int argc, char **argv, t_table *table)
{
	if(parsing(argc, argv, table)
	|| protected_init_from_print_to_change_die(table)
	|| protected_init_change_of_full(table)
	|| protected_malloc_arr_philos(table)
	|| protected_malloc_arr_forks(table)
	|| protected_init_arr_forks(table))
		return (1);
	table->start_simulation = 1;
	table->start_tv = get_time_ms();
	if (table->n_of_full_philos == 1)
	{
		if (protected_create_one_philo(table))
			return (2);
	}
	else
	{
		if (init_philos(table))
			return (3);
	}
	pthread_mutex_lock(&table->thread_supervisor);
	pthread_mutex_unlock(&table->thread_supervisor);
	return (0);
}

int	init_philos(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		if (protected_create_arr_philos(t, i))
			return (3);
		t->arr_philos[i].id = i + 1;
		t->arr_philos[i].meals = 0;
		t->arr_philos[i].left_fork = t->forks[i];
		t->arr_philos[i].right_fork
			= t->forks[t->arr_philos[i].id % t->n_of_philos];
		t->arr_philos[i].table = t;
		if (protected_mutex_init(t, i))
			return (4);
	}
	i = -1;
	while (++i < t->n_of_philos)
		pthread_join(t->arr_philos[i].thread, NULL);
	return (0);
}

int	init_supervisor(int argc, char **argv, t_supervisor *s, t_table *table)
{
	s->table = table;
	if (init_table(argc, argv, s->table))
		return (4);
	if (pthread_create(&s->super, NULL, supervisor, (void *)s->table))
		return (protected_mutex_init_supervisor(s));
	pthread_join(s->super, NULL);
	return (0);
	//join threads
}
