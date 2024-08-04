/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:41:54 by tnakas            #+#    #+#             */
/*   Updated: 2024/05/20 19:58:35 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//==============FORTH VERSION===================

// // counting the words
int	words(const char *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		words++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (words);
}

// // computing the length
int	word_len(const char *s, int start, char c)
{
	int	length;

	start--;
	length = 0;
	while (s[++start] && s[start] != c)
		length++;
	return (length);
}

// // freeing the strings and the array|| we don't need
// to free for the current failed allocation
void	ft_free(char **s, int last)
{
	while (last > 0)
		free(s[--last]);
	free(s);
}
// // making the split

char	**ft_split(const char *s, char c)
{
	t_split	v;

	if (!s)
		return (NULL);
	v.i = 0;
	v.j = 0;
	v.w = words(s, c);
	v.res = (char **)malloc(sizeof(char *) * (v.w + 1));
	if (!v.res)
		return (NULL);
	while (v.i < v.w)
	{
		while (s[v.j] && s[v.j] == c)
			v.j++;
		v.res[v.i] = ft_substr(s, v.j, word_len(s, v.j, c));
		if (!v.res[v.i])
		{
			ft_free(v.res, v.i);
			return (NULL);
		}
		v.j += word_len(s, v.j, c);
		v.i++;
	}
	v.res[v.w] = NULL;
	return (v.res);
}
