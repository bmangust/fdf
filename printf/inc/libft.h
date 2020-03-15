/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:47:47 by akraig            #+#    #+#             */
/*   Updated: 2019/10/06 17:06:31 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# define BUFF_SIZE 7
# define ERROR -1
# define READ_OK 1
# define END_OF_FILE 0

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;
void					*ft_memset(void *dst, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t count);
void					*ft_memccpy(void *dst, const void *src,
									int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *arr, int c, size_t n);
int						ft_memcmp(const void *arr1, const void *arr2, size_t n);
size_t					ft_strlen(char const *s);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strcat(char *dest, const char *append);
char					*ft_strncat(char *dest, const char *append, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strchrn(const char *s, int c);
int						ft_strrchrn(const char *s, int c);
char					*ft_strstr(const char *src, const char *aim);
char					*ft_strnstr(const char *src, const char *aim,
									size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *s);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
char					ft_toupper(int c);
char					ft_tolower(int c);
char					*ft_strtoupper(char *str, int is_freeable);
char					*ft_strtolower(char *str, int is_freeable);
int64_t					ft_absint(int64_t n);
float					ft_absfloat(float n);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
char					*ft_strrev(char *str);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void(*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
									char(*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
									size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int64_t n);
char					*ft_itoa_base(uint64_t value, uint64_t base);
char					*ft_itoa_baseu(uint64_t value, uint64_t base);
char					*ft_dtoa(long double d);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int64_t n);
void					ft_unsigned_putnbr(uint64_t n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int64_t n, int fd);
void					ft_unsigned_putnbr_fd(uint64_t nb, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
									void (*del)(void*, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int						ft_isspace(int c);
int64_t					ft_pow(int64_t a, int64_t b);
int						ft_wrdcnt(char const *s, char c);
int						ft_wordlen(const char *s, char c, int start);
void					ft_lstrev(t_list **head);
void					ft_lstadd_last(t_list **alst, t_list *new);
int						ft_int_length_base(int64_t value, int base);
int						ft_uint_length_base(uint64_t value, int base);
char					*ft_ltoa(long long int base, int sign);
char					*ft_charstr(int size, char n);
int64_t					ft_max(int64_t a, int64_t b);
int						get_next_line(const int fd, char **line);

#endif
