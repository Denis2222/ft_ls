/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 22:43:35 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/12 23:35:45 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	readopts(int ac, char **av, char *opts)
{
	int	i;
	const char *args = "lRart";

	i = 1;
	while (i < ac)
	{
		if (*av[i] == '-')
		{
			av[i]++;
			if (*av[i] == '\0')
				return (i);
			while (strchr(args, *av[i]) && *av[i] != '\0')
				opts[*(av[i]++)] = 1;
			if (*av[i] == '-')
				return (++i);
			if (*av[i] != '\0')
				error("ls: illegal option -- ", *av[i]);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
