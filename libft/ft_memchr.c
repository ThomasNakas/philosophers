/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:16:37 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/22 16:35:25 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int b_value, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (*(unsigned char *)(str + i) == (unsigned char)b_value)
			return ((void *)(str + i));
	}
	return (NULL);
}
