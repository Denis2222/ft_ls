/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsfct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:34:00 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/07 19:34:18 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strasc(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

int		ft_strdec(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s2[x] - (unsigned char)s1[x]);
}

int		ft_timeasc(time_t s1, time_t s2)
{
	return (s1 - s2);
}

int		ft_timedec(time_t s1, time_t s2)
{
	return (s2 - s1);
}
