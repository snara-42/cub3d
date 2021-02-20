/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:51:14 by snara             #+#    #+#             */
/*   Updated: 2020/11/17 18:21:58 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*lclear(t_list **map, void (*del)(void *))
{
	t_list	*n;

	while (*map)
	{
		n = (*map)->next;
		del((*map)->content);
		(*map)->next = NULL;
		free(*map);
		*map = n;
	}
	map = NULL;
	return (NULL);
}

static t_list	*lnew(void *c)
{
	t_list	*n;

	if ((n = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	n->content = c;
	n->next = NULL;
	return (n);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*n;

	if (!f || !lst)
		return (NULL);
	map = NULL;
	if (lst)
	{
		if (!(n = lnew(f(lst->content))))
			return (NULL);
		map = n;
	}
	while (lst->next)
	{
		if (!(n->next = lnew(f(lst->next->content))))
			return (lclear(&map, del));
		lst = lst->next;
		n = n->next;
	}
	return (map);
}
