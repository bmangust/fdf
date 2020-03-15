/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbloodax <jbloodax@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:03:59 by akraig            #+#    #+#             */
/*   Updated: 2020/02/09 19:41:23 by jbloodax         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_main(int fd, const char *restrict s, va_list valist)
{
	t_parse	*p;
	int		printed;

	p = new_param();
	while (*s)
	{
		if (*s != '%' && *s != '{')
			s = read_line(p, (char *)s);
		else if (*s == '{')
			s = read_color(p, (char *)s, ft_strdup("\033[30m"));
		else
		{
			parse_string((char *)++s, p, valist);
			if (!p->next)
				return (-1);
			s = p->next;
			clear_param(p);
		}
		s++;
	}
	ft_putstr_fd(p->buf, fd);
	printed = del_param(p, valist);
	return (printed);
}

int	ft_fprintf(int fd, const char *restrict s, ...)
{
	va_list	valist;
	int		printed;

	va_start(valist, s);
	printed = ft_printf_main(fd, s, valist);
	return (printed);
}

int	ft_printf(const char *restrict s, ...)
{
	va_list	valist;
	int		printed;

	va_start(valist, s);
	printed = ft_printf_main(1, s, valist);
	return (printed);
}
