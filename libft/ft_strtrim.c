/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:46:07 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/08 22:52:50 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_malloc(int start, int end)
{
	char	*new_str;

	if (end < start)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!new_str)
		return (NULL);
	return (new_str);
}

int	ft_char_in_set(const char c, const char *set)
{
	int	i;

	if (!set)
		return (0);
	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimed_s1;
	int			i;
	int			start;
	int			end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	trimed_s1 = ft_trim_malloc(start, end);
	if (!trimed_s1)
		return (NULL);
	i = -1;
	while ((start + (++i)) < end)
		trimed_s1[i] = s1[start + i];
	trimed_s1[i] = '\0';
	return (trimed_s1);
}
