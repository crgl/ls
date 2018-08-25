/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 18:13:28 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 18:13:35 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	free_files(t_entryvec *hvec)
{
	t_fdata			*to_free;
	unsigned long	i;

	to_free = (t_fdata *)hvec->e;
	i = 0;
	while (i < hvec->len / sizeof(t_fdata))
	{
		free(to_free[i].group);
		free(to_free[i].mode);
		free(to_free[i].name);
		free(to_free[i].owner);
		free(to_free[i].time);
		i++;
	}
	vecdel(&hvec);
}

void	free_dirs(t_dirvec *dirs)
{
	t_dirdata		*to_free;
	unsigned long	i;

	to_free = (t_dirdata *)dirs->e;
	i = 0;
	while (i < dirs->len / sizeof(t_dirdata))
	{
		free(to_free[i].full_path);
		i++;
	}
	vecdel(&dirs);
}
