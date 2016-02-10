#include "ft_ls.h"

static void	printcolumni(struct stat *filestat, t_ent *ent, char *path)
{
	int		r;
	char	*tmp;

	tmp = NULL;
	ft_putchar(' ');
	ft_putstrnfree(ctimetols(&filestat->st_mtimespec), 11, 1);
	ft_putchar(' ');
	ft_putstr(ent->name);
	if ((filestat->st_mode & S_IFMT) == S_IFLNK)
	{
		tmp = malloc(filestat->st_size + 1);
		r = readlink(path, tmp, filestat->st_size + 1);
		tmp[r] = '\0';
		ft_putstr(" -> ");
		ft_putstr(tmp);
	}
	ft_putchar('\n');
}

static void	printcolumn(struct stat *filestat, t_column *col, t_ent *ent, char *path)
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
	if ((filestat->st_mode & S_IFMT) == S_IFBLK ||
		(filestat->st_mode & S_IFMT) == S_IFCHR)
		ft_putstrnfree(majorminor(filestat->st_rdev), col->size, 1);
	else
		ft_putstrnfree(ft_itoa(filestat->st_size), col->size, 1);
	printcolumni(filestat, ent, path);
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
			printcolumn(&filestat, col, ent, lpath2);
		}
		ft_strdel(&lpath);
		ft_strdel(&lpath2);
		ent = ent->next;
	}
}
