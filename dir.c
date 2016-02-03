/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 18:21:46 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/03 19:05:13 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	printstat(char *filepath, struct stat filestat)
{
	//printf("%s st_dev:%d st_uid:%d \n", filepath, filestat.st_dev, filestat.st_uid);
	ft_putstr(filepath);
	ft_putstr("\n");
	return (0);
}

void	listdir(t_arg *arg, t_ls *ls)
{
	DIR				*dirfd;
	struct dirent	*ent;
	struct stat		filestat;
	t_sfile			*file;
	t_ent			*ment;

	dirfd = opendir(arg->path);
	if (dirfd != NULL)
	{
		while ((ent = readdir(dirfd)))
		{
			if ((ent->d_name[0] == '.' && ls->opts['a']) || ent->d_name[0] != '.')
			{
				if (lstat(ft_strjoin(arg->path, ft_strjoin("/", ent->d_name)), &filestat) == 0)
				{
					ment = newent(ent, &filestat);
					arg->ent = addent(&(arg->ent), ment);
					if (!ft_strequ(ent->d_name,".") && !ft_strequ(ent->d_name,".."))
					{
						if (ent->d_type == 4 && ls->opts['R'])
						{
							arg->sub = addarg(&arg->sub, newarg(ft_strjoin(arg->path,ft_strjoin("/", ment->name))));
						}
					}
				}
			}
		}
		closedir(dirfd);
	}
	else
	{
		if(errno == EACCES)
			ft_putstr("permission denied");
		else if(lstat(arg->path, &filestat) == 0)
		{
			file = newfile(arg->path);
			ls->files = addfile(&ls->files, file);
			//printstat(arg->path, filestat);
		}
		else
			perror ("");
	}
}
