/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:23:06 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/29 22:49:31 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_links(t_dir *files, t_dir *dir)
{
	int i;
	int ctrl;
	int j;

	i = 0;
	ctrl = dir->maxlk;
	while (ctrl > 9 && ++i)
		ctrl = ctrl / 10;
	ctrl = files->stat->st_nlink;
	j = 0;
	while (ctrl > 9 && ++j)
		ctrl = ctrl / 10;
	while (j != i)
	{
		ft_putchar(' ');
		i--;
	}
	ft_putnbr(files->stat->st_nlink);
	ft_putchar(' ');
}

void		print_own(t_dir *files, t_dir *dir, t_opt *opt)
{
	int dif;

	dif = dir->maxown - (int)ft_strlen(files->pswd->pw_name);
	ft_putstr(files->pswd->pw_name);
	dif += 1;
	while (--dif)
		ft_putchar(' ');
	ft_putstr("  ");
	if (!opt->o)
	{
		dif = dir->maxgrp - (int)ft_strlen(files->grp->gr_name);
		ft_putstr(files->grp->gr_name);
		dif += 1;
		while (--dif)
			ft_putchar(' ');
		ft_putstr("  ");
	}
}

static void	print_min(t_dir *files, t_dir *dir, int i, int j)
{
	int min;
	int ctrl;

	min = minor(files->stat->st_rdev);
	ctrl = dir->maxfsz;
	i = 0;
	j = 0;
	while (ctrl > 9 && ++i)
		ctrl = ctrl / 10;
	ctrl = min;
	while (ctrl > 9 && ++j)
		ctrl = ctrl / 10;
	i += 1;
	while (j != --i)
		ft_putchar(' ');
	ft_putnbr(min);
}

static void	print_regular_size(t_dir *files, t_dir *dir, int i, int j)
{
	int tmp;

	if (dir->maxmin)
	{
		tmp = dir->maxmin;
		while (tmp > 9)
		{
			ft_putchar(' ');
			tmp = tmp / 10;
		}
		ft_putstr("   ");
	}
	tmp = dir->maxfsz;
	while (tmp > 9 && ++i)
		tmp = tmp / 10;
	tmp = files->stat->st_size;
	while (tmp > 9 && ++j)
		tmp = tmp / 10;
	i += 1;
	while (j != --i)
		ft_putchar(' ');
	ft_putnbr(files->stat->st_size);
}

void		print_size(t_dir *files, t_dir *dir, int i, int j)
{
	int min;
	int ctrl;

	if (S_ISBLK(files->stat->st_mode) || S_ISCHR(files->stat->st_mode))
	{
		min = major(files->stat->st_rdev);
		ctrl = dir->maxmin;
		while (ctrl > 9 && ++i)
			ctrl = ctrl / 10;
		ctrl = min;
		while (ctrl > 9 && ++j)
			ctrl = ctrl / 10;
		i += 1;
		while (j != --i)
			ft_putchar(' ');
		ft_putnbr(min);
		ft_putstr(", ");
		print_min(files, dir, 0, 0);
	}
	else
		print_regular_size(files, dir, 0, 0);
	ft_putchar(' ');
	print_date(files, 0);
}
