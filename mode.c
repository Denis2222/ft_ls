#include "ft_ls.h"

char	mode(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else
		return (' ');
}

void	modeusr(mode_t st_mode, char *str)
{
	if (st_mode & S_ISUID)
		str[3] = 'S';
	if (st_mode & S_IRWXU)
	{
		if (st_mode & S_IRUSR)
			str[1] = 'r';
		if (st_mode & S_IWUSR)
			str[2] = 'w';
		if (st_mode & S_IXUSR)
			str[3] = 'x';
		if (st_mode & S_ISUID && st_mode & S_IXUSR)
			str[3] = 's';
	}
}

void	modegrp(mode_t st_mode, char *str)
{
	if (st_mode & S_ISGID)
		str[6] = 'S';
	if (st_mode & S_IRWXG)
	{
		if (st_mode & S_IRGRP)
			str[4] = 'r';
		if (st_mode & S_IWGRP)
			str[5] = 'w';
		if (st_mode & S_IXGRP)
			str[6] = 'x';
		if (st_mode & S_IXGRP && st_mode & S_ISGID)
			str[6] = 's';
	}
}

void	modeoth(mode_t st_mode, char *str)
{
	if (st_mode & S_ISVTX)
		str[9] = 'T';
	if (st_mode & S_IRWXO)
	{
		if (st_mode & S_IROTH)
			str[7] = 'r';
		if (st_mode & S_IWOTH)
			str[8] = 'w';
		if (st_mode & S_IXOTH)
			str[9] = 'x';
		if (st_mode & S_ISVTX && st_mode & S_IXOTH)
			str[9] = 't';
	}
}

char	*modetostr(mode_t st_mode)
{
	char *str;

	str = (char*)malloc(sizeof(char) * 11);
	ft_memset(str, '-', 10);
	str[10] = '\0';
	str[0] = mode(st_mode);
	modeusr(st_mode, str);
	modegrp(st_mode, str);
	modeoth(st_mode, str);
	return (str);
}
