/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 06:00:21 by akraig            #+#    #+#             */
/*   Updated: 2020/01/23 12:27:16 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchrn(const char *s, int c)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	i = 0;
	while (i < slen)
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strrchrn(const char *s, int c)
{
	int	slen;

	slen = (int)ft_strlen(s);
	while (--slen >= 0)
	{
		if (s[slen] == (char)c)
			return (slen);
	}
	return (-1);
}
