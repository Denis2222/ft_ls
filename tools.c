/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:27:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/09 00:18:38 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	mode(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else
		return (' ');
}

char	*modetostr(mode_t st_mode)
{
	char *str;

	str = (char*)malloc(sizeof(char) * 11);
	ft_memset(str, '-', 10);
	str[10] = '\0';
	str[0] = mode(st_mode);
	if (st_mode & S_IRUSR)
		str[1] = 'r';
	if (st_mode & S_IWUSR)
		str[2] = 'w';
	if (st_mode & S_IXUSR)
		str[3] = 'x';
	if (st_mode & S_IRGRP)
		str[4] = 'r';
	if (st_mode & S_IWGRP)
		str[5] = 'w';
	if (st_mode & S_IXGRP)
		str[6] = 'x';
	if (st_mode & S_IROTH)
		str[7] = 'r';
	if (st_mode & S_IWOTH)
		str[8] = 'w';
	if (st_mode & S_IXOTH)
		str[9] = 'x';
	return (str);
}

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
