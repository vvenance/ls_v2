/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:12:48 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 11:12:50 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_o(char *str, t_opt *opt, int i)
{
	while (str[++i] != '\0')
	{
		if (str[i] == 't')
			opt->t = 1;
		else if (str[i] == 'a')
			opt->a = 1;
		else if (str[i] == 'l')
			opt->l = 1;
		else if (str[i] == 'r')
			opt->r = 1;
		else if (str[i] == 'R')
			opt->br = 1;
		else if (str[i] == '1')
			;
		else if (str[i] == 'n')
			opt->n = 1;
		else if (str[i] == 'o')
			opt->o = 1;
		else
		{
			opt->index = (int)str[i];
			return (-1);
		}
	}
	return (0);
}

t_opt	*get_opt(t_opt *opt, char **av, int ac, int i)
{
	while (i != ac && av[i][0] == '-')
	{
		if (ft_strlen(av[i]) == 1 || !ft_strcmp(av[i], "--"))
		{
			if (!ft_strcmp(av[i], "--"))
				opt->index = i + 1;
			else
				opt->index = i;
			return (opt);
		}
		else if (get_o(av[i], opt, 0) == -1)
		{
			ft_putstr_fd("/bin/ls: illegal option -- ", 2);
			ft_putchar_fd(opt->index, 2);
			ft_putstr_fd("\nusage: ls [-lRrat] [file ...]\n", 2);
			free((void *)(opt));
			exit(1);
		}
		i++;
	}
	opt->index = i;
	return (opt);
}