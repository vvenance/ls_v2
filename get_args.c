/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 12:35:35 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 12:35:38 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_base	*ft_add_err(t_base *base, char *avi, char *strerr)
{
	t_dir	*error;
	t_dir	*tmp;

	error = init_dir(avi, NULL);
	if (strerr)
		error->strerr = ft_strdup(strerr);
	if (!base->error)
		base->error = error;
	else
	{
		tmp = base->error;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = error;
	}
	return (base);
}

static t_base	*get_args2(t_opt *opt, char *avi, t_base *base)
{
	struct stat	stat;
	char		*strerr;

	err = NULL;
	if (lstat(avi, &stat) != -1)
	{
		if (S_ISLNK(stat.st_mode))
			stat(avi, &stat);
		if (S_ISDIR(stat.st_mode) && !(strerr = (can_be_opened(avi))))
			base->dir = add_dir(avi, opt, base->dir, &stat);
		else if (S_ISREG(stat.st_mode) || S_ISCHR(stat.st_mode) ||
			S_ISBLK(stat.st_mode) || S_ISFIFO(stat.st_mode) ||
			S_ISLNK(stat.st_mode) || S_ISSOCK(stat.st_mode))
			base->solo_files->files = add_file(avi, opt, base->solo_files, &stat);
		else
			base = ft_add_err(base, avi, strerr);
	}
	else
		base = ft_add_err(base, avi, NULL);
	return (base);
}

t_base		*get_args(t_opt *opt, char **av, int ac, t_base *base)
{
	if (ac == opt->index && av)
	{
		base = get_args2(opt, ".", p);
		if (base->dir)
			base->dir->disp_name = 0;
	}
	if (opt->index + 1 == ac)
	{
		base = get_args2(opt, av[opt->index], p);
		if (base->dir)
			base->dir->disp_name = 0;
	}
	else
	{
		opt->index -= 1;
		while (++opt->index != ac)
			base = get_args2(opt, av[opt->index], base);
	}
	return (base);
}