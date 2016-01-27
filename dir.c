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

int	printstat(struct stat filestat)
{
	printf("st_dev:%d st_uid:%d \n", filestat.st_dev, filestat.st_uid);
	return (0);
}

void    listdir(char *dirpath)
{
	DIR				*dirfd;
	struct dirent	*ent;
	struct stat		filestat;

	dirfd = opendir(dirpath);
	if (dirfd != NULL)
	{
		while ((ent = readdir (dirfd)))
		{
			ft_putstr(ent->d_name);
			ft_putstr("(");
			ft_putnbr(ent->d_type);
			ft_putstr(")");
			if (ent->d_type == 8)
			{
				//lstat(ft_strjoin(av[firstpath], ent->d_name), &filestat);
				//printstat(filestat);
			}
			ft_putendl(" ");
		}
		ft_putendl("");
		(void) closedir (dirfd);
	}
	else
    {
        if(lstat(dirpath, &filestat) == 0)
	{
          printstat(filestat);
        }
        else
        {
          perror ("");
        }
    }
}
