/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:17:21 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/14 18:37:24 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//because is int I must cast it as a character
char	*ft_strrchr(char *str, int c)
{
	int	i;

	i = 0;
	i = ft_strlen(str);
	i++;
	while (--i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
	}
	return (NULL);
}
