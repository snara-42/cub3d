/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:33:55 by snara             #+#    #+#             */
/*   Updated: 2020/11/10 20:11:01 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l;

	if (lst && *lst)
	{
		l = *lst;
		while (l->next)
			l = l->next;
		l->next = new;
		l->next->next = NULL;
	}
	else
	{
		*lst = new;
		(*lst)->next = NULL;
	}
}
