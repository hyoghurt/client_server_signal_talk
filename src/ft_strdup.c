/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:31:18 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/06/30 21:24:36 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*i;
	int		y;

	if (!s)
		return (0);
	i = (char *)malloc(ft_strlen(s) + 1);
	if (!i)
		return (0);
	y = 0;
	while (s[y] != '\0')
	{
		i[y] = s[y];
		y++;
	}
	i[y] = '\0';
	return (i);
}
