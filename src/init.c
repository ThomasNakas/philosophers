/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 07:21:49 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_supervisor(int argc, char **argv, t_supervisor *s, t_table *table)
{
	int	i;

	s->table = table;
	if (init_table(argc, argv, s->table))
		return (4);
	if (pthread_create(&s->super, NULL, supervisor, (void *)s->table))
		return (protected_mutex_init_supervisor(s));
	i = -1;
	while (++i < s->table->n_of_philos)
		pthread_join(s->table->arr_philos[i].thread, NULL);
	pthread_join(s->super, NULL);
	return (0);
}

int	init_table(int argc, char **argv, t_table *table)
{
	if (parsing(argc, argv, table)
		|| protected_init_from_print_to_change_die(table)
		|| protected_init_change_of_full(table)
		|| protected_malloc_arr_philos(table)
		|| protected_malloc_arr_forks(table)
		|| protected_init_arr_forks(table))
		return (1);
	table->start_simulation = 1;
	table->start_tv = get_time_ms();
	table->print_flag = 0;
	if (table->n_of_philos == 1)
	{
		if (protected_create_one_philo(table))
			return (2);
	}
	else
	{
		if (init_many_philos(table))
			return (3);
	}
	return (0);
}

int	init_many_philos(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		t->arr_philos[i].id = i + 1;
		t->arr_philos[i].meals = 0;
		t->arr_philos[i].right_fork = i;
		t->arr_philos[i].left_fork = (i + 1) % t->n_of_philos;
		t->arr_philos[i].table = t;
		t->arr_philos[i].start_time = get_time_ms();
		t->arr_philos[i].last_time_meal = get_time_ms();
		t->arr_philos[i].run = 1;
		t->arr_philos[i].is_counted = 0;
		if (protected_mutex_init(t, i))
			return (3);
		if (protected_create_arr_philos(t, i))
			return (4);
	}
	return (0);
}
