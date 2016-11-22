/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvenance <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:32:25 by vvenance          #+#    #+#             */
/*   Updated: 2016/11/22 18:32:27 by vvenance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*reverse_sort_t(t_dir *tmp, t_dir *f)
{
	t_dir *curr;
	t_dir *prev;

	curr = f;
	prev = NULL;
	while (curr != NULL && (curr->stat->SEC > tmp->stat->SEC))
	{
		prev = curr;
		curr = curr->next;
	}
	while (curr != NULL && (curr->stat->SEC == tmp->stat->SEC) &&
		curr->stat->NSEC >= tmp->stat->NSEC)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
		f = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;
	return (f);
}

t_dir	*sort_t(t_dir *tmp, t_dir *f, int r)
{
	t_dir *curr;
	t_dir *prev;

	if (r == 1)
		return (reverse_sort_t(tmp, f));
	curr = f;
	prev = NULL;
	while (curr != NULL && (curr->stat->SEC < tmp->stat->SEC))
	{
		prev = curr;
		curr = curr->next;
	}
	while (curr != NULL && (curr->stat->SEC == tmp->stat->SEC) &&
		curr->stat->NSEC <= tmp->stat->NSEC)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
		f = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;
	return (f);
}

t_dir	*reverse_sort_a(t_dir *tmp, t_dir *f)
{
	t_dir *curr;
	t_dir *prev;

	curr = f;
	prev = NULL;
	while (curr != NULL && (ft_strcmp(tmp->name, curr->name) < 0))
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
		f = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;
	return (f);
}

t_dir	*sort_a(t_dir *tmp, t_dir *f, int r)
{
	t_dir *curr;
	t_dir *prev;

	if (r == 1)
		return (reverse_sort_a(tmp, f));
	curr = f;
	prev = NULL;
	while (curr != NULL && (ft_strcmp(tmp->name, curr->name) > 0))
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
		f = tmp;
	else
		prev->next = tmp;
	tmp->next = curr;
	return (f);
}