/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 20:22:32 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/18 20:22:41 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		secret_strcmp(void *e1, void *e2)
{
	const char	**s1;
	const char	**s2;

	s1 = (const char **)e1;
	s2 = (const char **)e2;
	return (ft_strcmp(*s1, *s2));
}

int		dd_cmp_f(void *e1, void *e2)
{
	t_dirdata	*tmp1;
	t_dirdata	*tmp2;

	tmp1 = (t_dirdata *)e1;
	tmp2 = (t_dirdata *)e2;
	return (ft_strcmp(tmp1->full_path, tmp2->full_path));
}

int		dd_cmp_r(void *e1, void *e2)
{
	t_dirdata	*tmp1;
	t_dirdata	*tmp2;

	tmp1 = (t_dirdata *)e1;
	tmp2 = (t_dirdata *)e2;
	return (ft_strcmp(tmp2->full_path, tmp1->full_path));
}

int		dd_cmp_ft(void *e1, void *e2)
{
	t_dirdata	*tmp1;
	t_dirdata	*tmp2;

	tmp1 = (t_dirdata *)e1;
	tmp2 = (t_dirdata *)e2;
	if (tmp1->acc_time < tmp2->acc_time)
		return (1);
	else if (tmp1->acc_time > tmp2->acc_time)
		return (-1);
	if (tmp1->nsec == tmp2->nsec)
		return (ft_strcmp(tmp1->full_path, tmp2->full_path));
	return (tmp2->nsec - tmp1->nsec);
}

int		dd_cmp_rt(void *e1, void *e2)
{
	t_dirdata	*tmp1;
	t_dirdata	*tmp2;

	tmp1 = (t_dirdata *)e1;
	tmp2 = (t_dirdata *)e2;
	if (tmp1->acc_time < tmp2->acc_time)
		return (-1);
	else if (tmp1->acc_time > tmp2->acc_time)
		return (1);
	if (tmp1->nsec == tmp2->nsec)
		return (ft_strcmp(tmp2->full_path, tmp1->full_path));
	return (tmp1->nsec - tmp2->nsec);
}
