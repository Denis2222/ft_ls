#include "ft_ls.h"

void	seekcolumnsizefileug(struct stat *filestat, t_column *col)
{
	char	*tmp;

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
		ft_strdel(&tmp);
	}
	if (getgrgid(filestat->st_gid))
		if (ft_strlen(getgrgid(filestat->st_gid)->gr_name) > col->group)
			col->group = ft_strlen(getgrgid(filestat->st_gid)->gr_name);
}

void	seekcolumnsizefile(struct stat *filestat, t_column *col)
{
	char	*tmp;

	col->block += filestat->st_blocks;
	tmp = ft_itoa(filestat->st_nlink);
	if (ft_strlen(tmp) > col->link)
		col->link = ft_strlen(tmp);
	seekcolumnsizefileug(filestat, col);
	if ((filestat->st_mode & S_IFMT) == S_IFBLK ||
		(filestat->st_mode & S_IFMT) == S_IFCHR)
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
			seekcolumnsizefile(&filestat, col);
		ft_strdel(&lpath);
		ft_strdel(&lpath2);
		ent = ent->next;
	}
}
