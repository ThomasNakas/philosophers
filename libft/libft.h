/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:45:35 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/03 13:21:35 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
//------------------STRUCTS-------------------------------------
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_split
{
	int		i;
	int		j;
	int		w;
	char	**res;
}	t_split;
//---------------CHECK FUNCTIONS--------------------------------
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
char		*ft_itoa(int n);
//----------------PRINT------------------------------------------
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
//------------------STRINGS--------------------------------------
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strchr(const char *str, int c);
char		*ft_strnstr(const char *str, const char *sub, size_t l);
char		*ft_strrchr(char *str, int c);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcat(char *dest, char *src, size_t size);
size_t		ft_strlcpy(char *cpy, char *src, size_t l);
size_t		ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
void		ft_free(char **s, int last);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
//----------------------MEMORY-----------------------------------
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *str, int b_value, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b_filled, int b_value, size_t len);
void		*ft_calloc(size_t num_el, size_t el_size);
void		ft_bzero(void *str, size_t n);
#endif
