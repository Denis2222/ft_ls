/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:27:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/10 21:54:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define SIXMONTH 86400 * 31 * 6

void	ctimetols(struct timespec *timespec)
{
	char	*strtime;
	time_t	now;

	now = time(&now);
	strtime = ctime(&timespec->tv_sec);
	if (now + SIXMONTH < timespec->tv_sec || timespec->tv_sec + SIXMONTH < now)
	{
		strtime[ft_strlen(strtime) - 1] = '\0';
		write(1, strtime + 4, 7);
		ft_putstr(ft_strrchr(strtime, ' '));
	}
	else
	{
		write(1, strtime + 4, 12);
	}
}

char	*majorminor(dev_t dev)
{
	int		length;
	char	*strmajor;
	char	*strminor;
	char	*out;

	strmajor = ft_itoa(major(dev));
	strminor = ft_itoa(minor(dev));
	length = ft_strlen(strmajor) + ft_strlen(strminor);
	out = (char*)malloc(sizeof(char) * (length + 1));
	out = ft_strcat(out, strmajor);
	out = ft_strcat(out, ", ");
	out = ft_strcat(out, strminor);
	ft_strdel(&strmajor);
	ft_strdel(&strminor);
	return (out);
}
