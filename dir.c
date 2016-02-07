/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 18:21:46 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/07 20:19:58 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	listfiles(t_arg *arg, t_ls *ls)
{
	DIR	*dirfd;
	struct stat		filestat;
	t_ent			*file;

	dirfd = opendir(arg->path);
	if (dirfd == NULL && errno != EACCES)
	{
		if (lstat(arg->path, &filestat) == 0)
		{
			file = newent(arg->path, &filestat);
			ls->files = addent(&ls->files, file);
		}
		else
		{
			ft_putstr_fd("ls: ", 2);
			ft_putstr_fd(arg->path, 2);
			ft_putstr_fd(": ", 2);
			perror("");
		}
	}
	else
	{
		if (errno == 0)
			closedir(dirfd);
	}
}

void	listdir(t_arg *arg, t_ls *ls)
{
	DIR				*dirfd;
	struct dirent	*ent;
	struct stat		filestat;
	t_ent			*file;
	t_ent			*ment;

	dirfd = opendir(arg->path);
	if (dirfd != NULL)
	{
		if (lstat(arg->path, &filestat) == 0)
			arg->mtime = filestat.st_mtimespec.tv_sec;
		while ((ent = readdir(dirfd)))
		{
			if ((ent->d_name[0] == '.' && ls->opts['a']) || ent->d_name[0] != '.')
			{
				if (lstat(ft_strjoin(arg->path, ft_strjoin("/", ent->d_name)), &filestat) == 0)
				{
					ment = newent(ent->d_name, &filestat);
					arg->ent = addent(&(arg->ent), ment);
					if (!ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
					{
						if (ent->d_type == 4 && ls->opts['R'])
						{
							arg->sub = addarg(&arg->sub, newarg(ft_strjoin(arg->path, ft_strjoin("/", ment->name))));
						}
					}
				}
			}
		}
		arg->empty = 0;
		closedir(dirfd);
	}
	else
	{
		if (errno == EACCES)
		{
			arg->deny = 1;
		}
	}
}

void	timedir(t_arg *arg, t_ls *ls)
{
	DIR				*dirfd;
	struct stat		filestat;

	dirfd = opendir(arg->path);
	if (dirfd != NULL)
	{
		if (lstat(arg->path, &filestat) == 0)
			arg->mtime = filestat.st_mtimespec.tv_sec;
		closedir(dirfd);
	}
}
