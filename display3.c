/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 13:36:26 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/23 13:36:28 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_date(char *str, char **tab, int i)
{
	char *tmp;

	(void)str;
	//ft_free(str, NULL);
	while (tab[i])
	{
		tmp = tab[i - 1];
		//ft_free(tmp, NULL);
		i++;
	}
	//ft_free(tab[i - 1], tab[i]);
	//ft_free(tab, NULL);
}

void		print_date(t_dir *files, int j)
{
	char	*str;
	time_t	now;
	char	**tab;

	str = ctime(&files->stat->st_mtime);
	now = time(NULL);
	tab = ft_strsplit(str, ' ');
	ft_putstr(tab[1]);
	ft_putchar(' ');
	if ((j = ft_strlen(tab[2])) != 2)
		ft_putchar(' ');
	ft_putstr(tab[2]);
	ft_putchar(' ');
	if ((j = now - files->stat->st_mtime) >= 15778800)
	{
		ft_putchar(' ');
		str = ft_strsub(tab[4], 0, ft_strlen(tab[4]) - 1);
	}
	else
		str = ft_strsub(tab[3], 0, 5);
	ft_putstr(str);
	free_date(str, tab, 1);
	ft_putchar(' ');
}

void	print_sym_link(t_dir *files, t_dir *dir, char *buf)
{
	char *str;
	char *str2;

	if (S_ISLNK(files->stat->st_mode))
	{
		str = ft_strjoin(dir->name, "/");
		str2 = ft_strjoin(str, files->name);
		if (readlink(str2, buf, 199) != -1)
		{
			ft_putstr(" -> ");
			ft_putstr(buf);
		}
		//ft_free(str, str2);
	}
	//ft_free(buf, NULL);
}