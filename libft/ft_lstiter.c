/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:48:52 by snara             #+#    #+#             */
/*   Updated: 2020/11/17 19:12:39 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (f && lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
**#include <stdio.h>
**void f(void*l){char*p=(char*)l;int i=0;while(p[i]){i++;}}
**int main(){t_list l={"content",NULL};ft_lstiter(&l,f);return (0);}
*/
