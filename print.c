#include "ft_ls.h"

void	print_files(t_ls *ls)
{
	t_sfile	*files;

	if (ls->files)
	{
		files = sortfiles(ls->files, &ft_strasc);
		while (files)
		{
			if (files->path)
			{
				ft_putstr(files->path);
				ft_putchar('\n');
				if (!files->next)
					ft_putchar('\n');
				files = files->next;
			}
		}
	}
}

char *modetostr(mode_t st_mode)
{
	char *str;

	str = (char*)malloc(sizeof(char) * 12);
	ft_memset(str, ' ', 12);
	ft_memset(str, '-', 12);
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

void	print_ents(char *path, t_ent *ent, t_ls *ls)
{
	struct stat		filestat;

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
			while(ent)
			{
				if (lstat(ft_strjoin(path, ft_strjoin("/", ent->name)), &filestat) == 0)
				{
					ft_putstr(ent->name);
					ft_putchar(':');
					ft_putstr(" size:");
					ft_putnbr(filestat.st_size);
					ft_putstr(" user:");
					ft_putstr(getpwuid(filestat.st_uid)->pw_name);
					ft_putstr(" group:");
					ft_putstr(getgrgid(filestat.st_gid)->gr_name);
					ft_putstr(" mode:");
						ft_putstr(modetostr(filestat.st_mode));
					ft_putstr("\n");
				}
				ent = ent->next;
			}
		}
	}
}

void	print_args(t_arg *args, t_ls *ls)
{
	t_arg *arg;

	arg = args;
	while (arg)
	{
		if (arg->ent)
		{
			if (arglen(ls->args) > 1)
			{
				ft_putstr(arg->path);
				ft_putstr(":\n");
			}
			sortents(arg->ent, &ft_strasc);
			print_ents(arg->path, arg->ent, ls);
			if (arg->next && arg->next->ent)
				ft_putstr("\n");
		}
		if (arg->sub)
			print_args(arg->sub, ls);
		arg = arg->next;
	}
}
