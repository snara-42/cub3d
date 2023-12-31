/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:03:57 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 09:03:58 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void	*or_exit(void *p, const char *msg)
{
	if (p != NULL)
		return (p);
	printf("Error\n%s\n", msg);
	if (errno != 0 && errno != EAGAIN)
		perror("");
	exit(1);
}
