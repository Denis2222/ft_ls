#include "ft_ls.h"

void	print_files(t_ls *ls)
{
	t_ent	*files;

	if (ls->files)
	{
		files = sortents(ls->files, &ft_strasc);
		while (files)
		{
			if (files->name)
			{
				ft_putstr(files->name);
				ft_putchar('\n');
				if (!files->next)
					ft_putchar('\n');
				files = files->next;
			}
		}
	}
}

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
	char	**tab;
	char	**tabh;

	tab = ft_strsplit(time, ' ');
	tabh = ft_strsplit(tab[3], ':');
	str = (char *)malloc(sizeof(char) * 20);
	str = ft_strcat(str, tab[2]);
	str = ft_strcat(str, " ");
	str = ft_strcat(str, tab[1]);
	str = ft_strcat(str, " ");
	str = ft_strcat(str, tabh[0]);
	str = ft_strcat(str, ":");
	str = ft_strcat(str, tabh[1]);
	return (str);
}

void	print_ents(char *path, t_ent *ent, t_ls *ls)
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
			ft_putstr("total ");
			ft_putnbr(col.block);
			ft_putendl("");
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
					ft_putstrn(ctimetols(ctime(&filestat.st_mtimespec.tv_sec)), 12, 1);
					ft_putchar(' ');
					ft_putstr(ent->name);
					ft_putchar('\n');
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
