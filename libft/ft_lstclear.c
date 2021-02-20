/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:22:36 by snara             #+#    #+#             */
/*   Updated: 2020/11/17 14:56:24 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;

	while (del && lst && *lst)
	{
		t = (*lst)->next;
		del((*lst)->content);
		(*lst)->next = NULL;
		free(*lst);
		*lst = t;
	}
	lst = NULL;
}
