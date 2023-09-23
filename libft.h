/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 09:12:56 by subaru            #+#    #+#             */
/*   Updated: 2023/09/23 09:12:57 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>

char	*str_skip(const char *s, char c);
char	*ft_strchr(const char *s, char c);
int		ft_strncmp(const char *s, const char *t, size_t n);
int		ft_strrcmp(const char *s, const char *t, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*get_next_line(int fd);

char	*ft_strtou_base(const char *s, unsigned int *np, const char *dig);
int		ft_sscanf(const char *s, const char *fmt, ...);

void	*or_exit(void *p, const char *msg);

#endif
