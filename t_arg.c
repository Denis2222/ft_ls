/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:44:23 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/27 18:57:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    parseargs(t_ls *ls, char **av, int ac, int start)
{
	while (start < ac)
	{
		ls->args = addarg(&(ls->args), newarg(av[start]));
		start++;
	}
}

t_arg   *newarg(char *str)
{
  t_arg *arg;

  arg = (t_arg*)malloc(sizeof(t_arg));
  arg->path = str;
  arg->next = NULL;
  return (arg);
}

t_arg   *addarg(t_arg **lstarg, t_arg *arg)
{
  t_arg *beginlst;
  t_arg *current;

  beginlst = *lstarg;
  current = beginlst;
  if (!*lstarg)
  {
    beginlst = arg;
  }
  else
  {
    while (current->next)
    {
      current = current->next;
    }
    current->next = arg;
  }
  return (beginlst);
}


void    viewarg(t_arg *arg)
{
  t_arg *marg;
  marg = arg;
  while(marg)
  {
    printf("[arg: %s] ", marg->path);
    marg = marg->next;
  }
}
