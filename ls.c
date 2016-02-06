#include "ft_ls.h"

t_ls *newls(void)
{
	t_ls *ls;

	ls = (t_ls*)malloc(sizeof(t_ls));
	ls->opts = NULL;
	ls->args = NULL;
	ls->files = NULL;
	ls->sort_alpha = &ft_strasc;
	ls->sort_time = NULL;
	ls->nbarg = 0;
	ls->out = 0;
	return (ls);
}

void	setupls(t_ls *ls, char **av, int ac)
{
	int start;

	ls->opts = ft_memalloc('z');
	start = readopts(ac, av, ls->opts);
	if (start == ac)
		ls->args = addarg(&(ls->args), newarg("."));
	while (start < ac)
	{
		ls->args = addarg(&(ls->args), newarg(av[start]));
		start++;
	}
	ls->nbarg = arglen(ls->args);
	if (ls->opts['t'])
	{
		ls->sort_time = &ft_timedec;
	}
	if (ls->opts['r'])
	{
		ls->sort_alpha = &ft_strdec;
	}
}
