/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:37:00 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 11:37:01 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fts_open(int argc, char **argv)
{
	int i;

	i = 0;
	while (++i != argc)
	{
		if (!ft_strcmp(argv[i], ""))
		{
			ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
			exit(1);
		}
	}
}

char	*can_be_opened(char *name)
{
	DIR	*ptr;

	ptr = NULL;
	if (!(ptr = opendir(name)))
		return (ft_strdup(strerror(errno)));
	closedir(ptr);
	return (NULL);
}

void	*ft_stat_dup(void *s, size_t size)
{
	void	*tmp;
	size_t	i;

	tmp = NULL;
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*((unsigned char*)tmp + i) = *((unsigned char*)s + i);
		i++;
	}
	return (tmp);
}

void	ft_free(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
		free(p1);
	p1 = NULL;
	if (p2)
		free(p2);
	p2 = NULL;
	if (p3)
		free(p3);
	p3 = NULL;
	if (p4)
		free(p4);
	p4 = NULL;
}

// void	ft_free(int nb, ...)
// {
// 	va_list	ap;
// 	void	*tmp;

// 	va_start(ap, nb);
// 	while(nb--)
// 	{
// 		if((tmp = va_arg(ap, void *)))
// 		{
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 	}
// 	va_end(ap);
// }