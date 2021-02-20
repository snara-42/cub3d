/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:24:01 by snara             #+#    #+#             */
/*   Updated: 2020/11/17 14:36:38 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n;

	if ((n = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	n->content = content;
	n->next = NULL;
	return (n);
}
