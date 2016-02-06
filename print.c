/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 12:10:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/06 17:03:20 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ents(char *path, t_ent *ent, t_ls *ls, int type)
{
	struct stat	filestat;
	t_ent		*sent;
	t_column	col;

	col.link = 0;
	col.user = 0;
	col.group = 0;
	col.size = 0;
	col.block = 0;
	
	if (ent)
	{
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
			while(ent)
			{
				if (lstat(ft_strjoin(path, ft_strjoin("/", ent->name)), &filestat) == 0)
				{
					col.block += filestat.st_blocks;
					if (ft_strlen(ft_itoa(filestat.st_nlink)) > col.link)
						col.link = ft_strlen(ft_itoa(filestat.st_nlink));
					if (getpwuid(filestat.st_uid))
					{
						if (ft_strlen(getpwuid(filestat.st_uid)->pw_name) > col.user)
							col.user = ft_strlen(getpwuid(filestat.st_uid)->pw_name);
					}
					else if(ft_strlen(ft_itoa(filestat.st_uid)) > col.user)
						col.user = ft_strlen(ft_itoa(filestat.st_uid));
					if (getgrgid(filestat.st_gid))
						if (ft_strlen(getgrgid(filestat.st_gid)->gr_name) > col.group)
							col.group = ft_strlen(getgrgid(filestat.st_gid)->gr_name);
					if (ft_strlen(ft_itoa(filestat.st_size)) > col.size)
						col.size = ft_strlen(ft_itoa(filestat.st_size));
				}
				ent = ent->next;
			}
			if (type)
			{
				ft_putstr("total ");
				ft_putnbr(col.block);
				ft_putendl("");
			}
			ent = sent;
			while(ent)
			{
				if (lstat(ft_strjoin(path, ft_strjoin("/", ent->name)), &filestat) == 0)
				{
					ft_putstr(modetostr(filestat.st_mode));
					ft_putchar(' ');
					ft_putstrn(ft_itoa(filestat.st_nlink), col.link + 1, 1);
					ft_putchar(' ');
					if (getpwuid(filestat.st_uid))
						ft_putstrn(getpwuid(filestat.st_uid)->pw_name, col.user + 1, 0);
					else
						ft_putstrn(ft_itoa(filestat.st_uid), col.user + 1, 0);
					ft_putchar(' ');
					if (getgrgid(filestat.st_gid))
						ft_putstrn(getgrgid(filestat.st_gid)->gr_name, col.group + 1, 0);
					else
						ft_putstrn(ft_itoa(filestat.st_gid), col.user + 4, 1);
					ft_putchar(' ');
					ft_putstrn(ft_itoa(filestat.st_size), col.size , 1);
					ft_putchar(' ');
					ft_putstrn(ctimetols(ctime(&filestat.st_mtimespec.tv_sec)), 11, 1);
					ft_putchar(' ');
					ft_putstr(ent->name);
					ft_putchar('\n');
				}
				ent = ent->next;
			}
		}
		ls->out++;
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
			print_ents(arg->path, arg->ent, ls, 1);
		}
		else if(!arg->empty)
		{
			if (ls->out > 0)
				ft_putendl("");
			if ((arglen(ls->args) > 1 || ls->out > 0))
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
		}
		if (arg->sub)
			print_args(arg->sub, ls);
		arg = arg->next;
	}
}
