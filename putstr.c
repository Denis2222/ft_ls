/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 18:47:09 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/11 16:26:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstrfree(char *str)
{
	if (str)
	{
		ft_putstr(str);
		free(str);
		str = NULL;
	}
}

void	ft_putstrnfree(char *str, int n, int s)
{
	ft_putstrn(str, n, s);
	ft_strdel(&str);
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
	return (ft_strncat(newstr, str, n));
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
		ft_strncpy(newstr, str, n);
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

void	ft_putstrpathdir(char *path)
{
	ft_putstr(path);
	ft_putstr(":\n");
}
