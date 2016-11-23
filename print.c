/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 10:25:49 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/23 10:25:51 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(t_base *base)
{
	t_dir *prev;

	prev = NULL;
	while(base->error)
	{
		ft_putstr_fd("ls: ", 2);
		if (base->error->name && ft_strcmp(base->error->name, "\0"))
			ft_putstr_fd(base->error->name, 2);
		else
			ft_putstr_fd("fts_open", 2);
		ft_putstr_fd(": ", 2);
		if (!base->error->strerr)
			ft_putstr_fd("No such file or directory\n", 2);
		else
			ft_putendl_fd(base->error->strerr, 2);
		prev = base->error;
		base->error = base->error->next;
		//ft_free((void **)prev->name, (void **)prev->strerr, (void **)prev, NULL);
	}
	//ft_free((void **)base->error, NULL, NULL, NULL);
	if (base->solo_files || base->dir)
		ft_putstr("\n");
}

static void	display_name_and_total(t_dir *dir, t_opt *opt)
{
	if (dir->disp_name)
	{
		ft_putstr(dir->name);
		ft_putstr(":\n");
	}
	if (dir->disp_total && dir->files && opt->l)
	{
		ft_putstr("total ");
		ft_putnbr(dir->total);
		ft_putstr("\n");
	}
}

static void print_files(t_dir *dir, t_opt *opt)
{
	t_dir *prev;

	prev = NULL;
	while(dir->files)
	{
		if (opt->l)
		{
			print_type(dir->files);
			print_perm(dir->files);
			print_extended(dir, dir->files);
			print_links(dir->files, dir);
			print_own(dir->files, dir, opt);
			print_size(dir, dir->files, 0, 0);
		}
		ft_putstr(dir->files->name);
		if (opt->l)
			print_sym_link(dir, dir->files, ft_memalloc(200));
		prev = dir->files;
		dir->files = dir->files->next;
		if (dir->files)
			ft_putstr("\n");
		//ft_free(prev->name, prev->stat, prev, NULL);
	}
}

static void	display_dir(t_dir *dir, t_opt *opt)
{
	t_dir	*prev;

	prev = NULL;
	while (dir)
	{
		display_name_and_total(dir, opt);
		if (dir->files)
			print_files(dir, opt);
		else if (dir->strerr)
			ft_putendl(dir->strerr);
		//ft_free(dir->strerr, NULL, NULL, NULL);
		if (dir->sdir)
		{
			ft_putstr("\n");
			display_dir(dir->sdir, opt);
		}
		prev = dir;
		dir = dir->next;
		//ft_free(prev->stat, prev->name, prev->path_name, prev);
	}
}

void	display(t_base *base, t_opt* opt)
{
	//t_dir *prev;

	if (base->solo_files)
	{
		print_files(base->solo_files, opt);
		if (base->dir)
			ft_putstr("\n");
	}
	if (base->dir)
		display_dir(base->dir, opt);
}