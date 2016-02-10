/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:27:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/09 20:23:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*putstrnright(char *newstr, char *str, int n)
{
	int	i;
	int	length;

	i = 0;
	length = n - ft_strlen(str);
	while (i < length)
	{
		newstr[i] = ' ';
		i++;
	}
	newstr[i] = '\0';
	return (ft_strcat(newstr, str));
}

void	ft_putstrn(char *str, int n, int s)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = (char *)malloc(sizeof(char) * n + 1);
	if (s)
	{
		newstr = putstrnright(newstr, str, n);
	}
	else
	{
		i = ft_strlen(str);
		ft_strcpy(newstr, str);
		while (i < n)
		{
			newstr[i] = ' ';
			i++;
		}
		newstr[i] = '\0';
	}
	ft_putstr(newstr);
	ft_strdel(&newstr);
}

char	*ctimetols(struct timespec *timespec)
{
	char	*str;
	time_t	now;
	time_t ftime;
	char *toto;
	char *day;
	char *year;

	ftime = timespec->tv_sec;
	now = time(&now);
	if (now < ftime || ftime + 60 * 60 * 24 * 31 * 6 < now)
	{
		toto = ctime(&timespec->tv_sec);
		toto[ft_strlen(toto) - 1] = '\0';
		day = ft_strsub(toto, 4, 7);
		year = str = ft_strsub(toto, ft_strlen(toto) - ft_strlen(ft_strrchr(toto, ' ')), 6);
		str = ft_strjoin(day, year);
		ft_strdel(&day);
		ft_strdel(&year);
	}
	else
		str = ft_strsub(ctime(&timespec->tv_sec), 4, 12);
	return (str);
}

char *majorminor(dev_t dev)
{
	int		major;
	int		minor;
	int		length;
	char	*strmajor;
	char	*strminor;
	char	*out;

	major = major(dev);
	minor = minor(dev);
	strmajor = ft_itoa(major);
	strminor = ft_itoa(minor);
	length = ft_strlen(strmajor) + ft_strlen(strminor);
	out = (char*)malloc(sizeof(char) * (length + 1));
	out = ft_strcat(out, strmajor);
	out = ft_strcat(out, ", ");
	out = ft_strcat(out, strminor);
	ft_strdel(&strmajor);
	ft_strdel(&strminor);
	return (out);
}
