/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 19:47:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/02/07 20:41:49 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(void)
{
	ft_putstr("usage: ft_ls [-lRart] [file ...]");
}

void	error(char *str, char c)
{
	ft_putstr(str);
	if (c)
		ft_putchar(c);
	ft_putchar('\n');
	usage();
	exit(EXIT_FAILURE);
}

void	erroremptyarg(void)
{
	ft_putendl("ft_ls: fts_open: No such file or directory");
	exit(EXIT_FAILURE);
}
