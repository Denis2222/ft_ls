/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 18:21:46 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/27 19:26:51 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	printstat(char *filepath, struct stat filestat)
{
	printf("%s st_dev:%d st_uid:%d \n", filepath, filestat.st_dev, filestat.st_uid);
	return (0);
}

void    listdir(t_arg *arg)
{
	DIR				*dirfd;
	struct dirent	*ent;
	struct stat		filestat;
	t_ent			*ment;

	dirfd = opendir(arg->path);
	if (dirfd != NULL)
	{
		while ((ent = readdir (dirfd)))
		{
			ment = newent(ent);
			arg->ent = addent(&(arg->ent), ment);
			ft_putstr(ent->d_name);
			//ft_putstr("(");
			//ft_putnbr(ent->d_type);
			//ft_putstr(")");
			if (ent->d_type == 8)
			{
				//lstat(ft_strjoin(av[firstpath], ent->d_name), &filestat);
				//printstat(filestat);
			}
			ft_putendl("");
		}
		printf("ent in dir : %d ", entlen(arg->ent));
		//ft_putendl("");
		(void) closedir (dirfd);
	}
	else
	{
		if(lstat(arg->path, &filestat) == 0)
		{
			printstat(arg->path, filestat);
		}
		else
		{
			perror ("");
		}
	}
}
