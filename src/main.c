/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:37 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 07:08:04 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table			table;
	t_supervisor	s;

	if (!init_supervisor(argc, argv, &s, &table))
		final_clean(&table);
	return (0);
}
