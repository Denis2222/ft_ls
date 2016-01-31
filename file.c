#include "ft_ls.h"

t_sfile	*newfile(char *path)
{
	t_sfile	*file;

	file = (t_sfile*)malloc(sizeof(t_sfile));
	file->path = ft_strdup(path);
	file->next = NULL;
	return (file);
}

t_sfile	*addfile(t_sfile **lst, t_sfile *file)
{
	t_sfile	*begin;
	t_sfile *cur;

	begin = *lst;
	cur = begin;
	if (!*lst)
		begin = file;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = file;
	}
	return begin;
}

int	filelen(t_sfile *file)
{
	int	length;
	t_sfile	*cur;

	length = 0;
	cur = file;
	while (cur)
	{
		length++;
		cur = cur->next;
	}
	return (length);
}

t_sfile	*sortfiles(t_sfile *lst, int (*cmp)(char *, char *))
{
	t_sfile	*tmp;
	char	*tmpstr;

	tmp = lst;
	while (tmp->next)
	{
		if ((*cmp)(tmp->path, tmp->next->path) <= 0)
			tmp = tmp->next;
		else
		{
			tmpstr = tmp->path;
			tmp->path = tmp->next->path;
			tmp->next->path = tmpstr;
			tmp = lst;
		}
	}
	return (lst);
}
