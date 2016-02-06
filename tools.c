/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:27:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/06 15:16:01 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char mode(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		return('d');
	else if ((st_mode & S_IFMT) == S_IFBLK)
		return('b');
	else if ((st_mode & S_IFMT) == S_IFIFO)
		return('p');
	else if ((st_mode & S_IFMT) == S_IFCHR)
		return('c');
	else if ((st_mode & S_IFMT) == S_IFLNK)
		return('l');
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		return('s');
	else
		return('-');
}

char *modetostr(mode_t st_mode)
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

void	ft_putstrn(char *str, int n, int s)
{
	int		length;
	char	*newstr;
	int		i;

	i = 0;
	newstr = (char *)malloc(sizeof(char) * n + 1);
	if (s)
	{
		length = n - ft_strlen(str);
		while (i < length)
		{
			newstr[i] = ' ';
			i++;
		}
		newstr[i] = '\0';
		newstr = ft_strcat(newstr, str);
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
	free(newstr);
}

char	*ctimetols(char *time)
{
	char	*str;

	str = ft_strsub(time, 4, 12);
	return (str);
}

int	ft_strasc(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

int	ft_strdec(char *s1, char *s2)
{
	int x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return ((unsigned char)s2[x] - (unsigned char)s1[x]);
}

int	ft_timeasc(time_t s1, time_t s2)
{
	return (s1 - s2);
}

int	ft_timedec(time_t s1, time_t s2)
{
	return (s2 - s1);
}
