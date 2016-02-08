/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:10:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/08 22:08:06 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	seekcolumnsizefile(struct stat *filestat, t_column *col)
{
	char	*tmp;

	col->block += filestat->st_blocks;
	tmp = ft_itoa(filestat->st_nlink);
	if (ft_strlen(tmp) > col->link)
		col->link = ft_strlen(tmp);
	if (getpwuid(filestat->st_uid))
	{
		if (ft_strlen(getpwuid(filestat->st_uid)->pw_name) > col->user)
			col->user = ft_strlen(getpwuid(filestat->st_uid)->pw_name);
	}
	else
	{
		tmp = ft_itoa(filestat->st_uid);
		if (ft_strlen(tmp) > col->user)
			col->user = ft_strlen(tmp);
	}
	if (getgrgid(filestat->st_gid))
		if (ft_strlen(getgrgid(filestat->st_gid)->gr_name) > col->group)
			col->group = ft_strlen(getgrgid(filestat->st_gid)->gr_name);
	if ((filestat->st_mode & S_IFMT) == S_IFBLK || (filestat->st_mode & S_IFMT) == S_IFCHR)
	{
		tmp = majorminor(filestat->st_dev);
		if (ft_strlen(tmp) > col->size)
			col->size = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		tmp = ft_itoa(filestat->st_size);
		if (ft_strlen(tmp) > col->size)
			col->size = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
}

void	seekcolumnsize(t_ent *ent, char *path, t_column *col)
{
	struct stat	filestat;
	char		*lpath;
	char		*lpath2;

	while (ent)
	{
		lpath = ft_strjoin("/", ent->name);
		lpath2 = ft_strjoin(path, lpath);
		if (lstat(lpath2, &filestat) == 0)
		{
			seekcolumnsizefile(&filestat, col);
		}
		ft_strdel(&lpath);
		ft_strdel(&lpath2);
		ent = ent->next;
	}
}

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

void	printcolumn(struct stat *filestat, t_column *col, t_ent *ent)
{
	ft_putstrfree(modetostr(filestat->st_mode));
	ft_putchar(' ');
	ft_putstrnfree(ft_itoa(filestat->st_nlink), col->link + 1, 1);
	ft_putchar(' ');
	if (getpwuid(filestat->st_uid))
		ft_putstrn(getpwuid(filestat->st_uid)->pw_name, col->user + 1, 0);
	else
		ft_putstrnfree(ft_itoa(filestat->st_uid), col->user + 1, 0);
	ft_putchar(' ');
	if (getgrgid(filestat->st_gid))
		ft_putstrn(getgrgid(filestat->st_gid)->gr_name, col->group + 1, 0);
	else
		ft_putstrnfree(ft_itoa(filestat->st_gid), col->user + 4, 1);
	ft_putchar(' ');
	if ((filestat->st_mode & S_IFMT) == S_IFBLK || (filestat->st_mode & S_IFMT) == S_IFCHR)
	{
		ft_putstrnfree(majorminor(filestat->st_rdev), col->size, 1);
	}
	else
	{
		ft_putstrnfree(ft_itoa(filestat->st_size), col->size, 1);
	}
	ft_putchar(' ');
	ft_putstrnfree(ctimetols(ctime(&filestat->st_mtimespec.tv_sec)), 11, 1);
	ft_putchar(' ');
	ft_putstr(ent->name);
	ft_putchar('\n');
}

void	printcolumns(t_ent *ent, t_column *col, char *path)
{
	struct stat	filestat;
	char		*lpath;
	char		*lpath2;

	while (ent)
	{
		lpath = ft_strjoin("/", ent->name);
		lpath2 = ft_strjoin(path, lpath);
		if (lstat(lpath2, &filestat) == 0)
		{
			printcolumn(&filestat, col, ent);
		}
		ft_strdel(&lpath);
		ft_strdel(&lpath2);
		ent = ent->next;
	}
}

void	print_ents(char *path, t_ent *ent, t_ls *ls, int type)
{
	t_ent		*sent;
	t_column	col;

	col.link = 0;
	col.user = 0;
	col.group = 0;
	col.size = 0;
	col.block = 0;
	if (ent)
	{
		if (type == 0)
			ls->out++;
		if (!ls->opts['l'])
		{
			while (ent)
			{
				ft_putstr(ent->name);
				ft_putchar('\n');
				ent = ent->next;
			}
		}
		else
		{
			sent = ent;
			seekcolumnsize(ent, path, &col);
			if (type)
			{
				ft_putstr("total ");
				ft_putnbr(col.block);
				ft_putendl("");
			}
			ent = sent;
			printcolumns(ent, &col, path);
		}
	}
}

void	print_args(t_arg *args, t_ls *ls)
{
	t_arg *arg;

	arg = args;
	while (arg)
	{
		if (arg->deny)
		{
			if (ls->out > 0)
				ft_putendl("");
			if ((arglen(ls->args) > 1 || ls->out > 0))
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
			ft_putstr_fd("ls :", 2);
			ft_putstr_fd(arg->path, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("Permission denied", 2);
		}
		else if (arg->ent)
		{
			if (ls->out > 0)
				ft_putendl("");
			if ((arglen(ls->args) > 1 || ls->out > 0))
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
			sortents(arg->ent, ls->sort_alpha);
			if (ls->sort_time)
				sortentstime(arg->ent, ls->sort_time);
			print_ents(arg->path, arg->ent, ls, 1);
		}
		else if (!arg->empty)
		{
			if (ls->out > 0)
			{
				ft_putendl("");
			}
			if ((arglen(ls->args) > 1 || ls->out > 0))
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
		}
		if (arg->sub)
			print_args(arg->sub, ls);
		arg = arg->next;
		ls->out++;
	}
}
