/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <rduport@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:45:11 by rduport           #+#    #+#             */
/*   Updated: 2024/11/19 17:40:54 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
void	*ft_memcpy(void *destination, const void *source, size_t size);
void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
void	*ft_calloc(size_t elementcount, size_t elementsize);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strrchr(const char *string, int searchedchar);
int		ft_isalpha(int c);
int		ft_isascii(int c);
char	*ft_strdup(const char *source);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcat(char *dest, const char *src, int size);
void	*ft_memmove(void *destination, const void *source, size_t size);
void	ft_putnbr_fd(int nb, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *first, const char *second, size_t length);
size_t	ft_strlen(const char *string);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *pointer, int value, size_t count);
void	*ft_memccpy(void *destination, const void *source, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strchr(const char *string, int searchedchar);
int		ft_atoi(const char *string);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
char    *ft_strdup_export(const char *source);
int		ft_strncmp_export(const char *first, const char *second, size_t length);
size_t	ft_strlen_char(const char *string, char c);
char	*ft_strdup_quote(const char *source);

#endif
