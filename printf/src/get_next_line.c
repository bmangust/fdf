/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:47:47 by akraig            #+#    #+#             */
/*   Updated: 2019/10/06 17:06:31 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_find(t_list **head, size_t fd)
{
	t_list	*p;
	t_list	*new;

	if (!head || !*head)
	{
		new = ft_lstnew(NULL, 0);
		new->content_size = fd;
		*head = new;
		return (*head);
	}
	p = *head;
	while (p->next && p->content_size != fd)
		p = p->next;
	if (p->content_size == fd)
		return (p);
	new = ft_lstnew(NULL, fd);
	new->content_size = fd;
	p->next = new;
	return (new);
}

void		ft_lstdelete(t_list **head, t_list *p)
{
	t_list	*ls;

	ls = *head;
	if (p != NULL)
	{
		if (ls->content_size != p->content_size)
			while (ls->next && ((ls->next)->content_size != p->content_size))
				ls = ls->next;
		ft_strdel((char**)&(p->content));
		if (p == *head)
			*head = p->next;
		else
			ls->next = p->next;
		free(p);
		return ;
	}
	while (ls->next)
	{
		*head = ls->next;
		ft_strdel((char**)&ls->content);
		free(ls);
		ls = *head;
	}
	ft_strdel((char**)&ls->content);
	free(*head);
}

int			find_and_cut(t_list *p, char **line, int ret, t_list **head)
{
	char	*nl;
	size_t	index;
	char	*tmp;

	if (ret != 0 && (nl = ft_strchr((char*)p->content, '\n')))
	{
		index = nl - (char*)p->content;
		if (!(*line = ft_strsub((char*)(p->content), 0, index)))
			return (ERROR);
		tmp = (char*)p->content;
		if (!(p->content = ft_strsub(tmp, (index + 1),
									(ft_strlen(tmp) - index))))
			return (ERROR);
		ft_strdel(&tmp);
		return (1);
	}
	else if (ret != 0)
		return (0);
	*line = ft_strdup((char*)p->content);
	ft_lstdelete(head, p);
	return (1);
}

int			read_buf(int fd, t_list *p, char **line, t_list *head)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (p->content == NULL)
			p->content = ft_strdup(buf);
		else
		{
			tmp = p->content;
			p->content = ft_strjoin(tmp, buf);
			ft_strdel(&tmp);
		}
		if ((ret = find_and_cut(p, line, ret, &head)) == -1)
			return (ERROR);
		else if (ret == 1)
			return (READ_OK);
	}
	return (END_OF_FILE);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*head;
	t_list			*p;
	char			b[1];
	int				ret;

	if (fd < 0 || read(fd, b, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	p = ft_lst_find(&head, (size_t)fd);
	if ((p->content) && ft_strchr((char*)p->content, '\n'))
		if (find_and_cut(p, line, 1, &head))
			return (READ_OK);
	if ((ret = read_buf(fd, p, line, head)) > 0)
		return (READ_OK);
	if (ret == 0 && p->content != NULL && ft_strlen(p->content) != 0)
		return (find_and_cut(p, line, ret, &head));
	ft_lstdelete(&head, p);
	*line = NULL;
	return (END_OF_FILE);
}
