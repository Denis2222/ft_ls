#include "ft_ls.h"

t_ls *newls(void)
{
	t_ls *ls;

	ls = (t_ls*)malloc(sizeof(t_ls));
	ls->opts = NULL;
	ls->args = NULL;
	ls->files = NULL;
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
}
