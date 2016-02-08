/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 18:21:46 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/08 18:08:32 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	listfiles(t_arg *arg, t_ls *ls)
{
	DIR				*dirfd;
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
			perror(arg->path);
		}
	}
	else if (errno == 0)
		closedir(dirfd);
}

void	listdiranalyse(t_ls *ls, t_arg *arg, struct dirent *ent)
{
	struct stat		filestat;
	t_ent			*ment;
	char			*lpath;
	char			*lpath2;

	lpath = ft_strjoin("/", ent->d_name);
	lpath2 = ft_strjoin(arg->path, lpath);
	if (lstat(lpath2, &filestat) == 0)
	{
		ment = newent(ent->d_name, &filestat);
		arg->ent = addent(&(arg->ent), ment);
		if (!ft_strequ(ent->d_name, ".") && !ft_strequ(ent->d_name, ".."))
			if (ent->d_type == 4 && ls->opts['R'])
				arg->sub = addarg(&arg->sub, newarg(lpath2));
	}
	ft_strdel(&lpath2);
	ft_strdel(&lpath);
}

void	listdir(t_arg *arg, t_ls *ls)
{
	DIR				*dirfd;
	struct dirent	*ent;
	struct stat		filestat;

	dirfd = opendir(arg->path);
	if (dirfd != NULL)
	{
		if (lstat(arg->path, &filestat) == 0)
			arg->mtime = filestat.st_mtimespec.tv_sec;
		while ((ent = readdir(dirfd)))
		{
			if ((ent->d_name[0] == '.' &&
				ls->opts['a']) || ent->d_name[0] != '.')
				listdiranalyse(ls, arg, ent);
		}
		arg->empty = 0;
		closedir(dirfd);
	}
	else if (errno == EACCES)
		arg->deny = 1;
}

void	timedir(t_arg *arg)
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
