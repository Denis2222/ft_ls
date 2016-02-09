/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:47:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/09 17:16:31 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(void)
{
	ft_putendl_fd("usage: ls [-1Rlart] [file ...]", 2);
}

void	error(char *str, char c)
{
	ft_putstr_fd(str, 2);
	if (c)
		ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	usage();
	exit(EXIT_FAILURE);
}

void	erroremptyarg(void)
{
	ft_putendl_fd("ls: fts_open: No such file or directory", 2);
	exit(EXIT_FAILURE);
}
