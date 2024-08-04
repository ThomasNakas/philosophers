/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:17:02 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/10 20:50:56 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
	}
	if (str[i] == (char)c)
		return ((char *)(str + i));
	return (NULL);
}
