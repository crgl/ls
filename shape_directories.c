/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_directories.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:47:04 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 17:47:09 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

long	set_ind_newlines(long *dims, long i, long n, long *newbool)
{
	long	adj;
	long	ind;

	if (n % dims[row])
	{
		adj = ft_max((i - (n % dims[row]) * dims[col]) / (dims[col] - 1), 0);
		ind = (i + adj) / dims[col] + ((i + adj) % dims[col]) * dims[row];
		*newbool = ((i + 1 + ft_max(i / dims[col] + 1 - (n % dims[row]), 0))
			% dims[col] == 0 || i == n - 1);
	}
	else
	{
		ind = i / dims[col] + (i % dims[col]) * dims[row];
		*newbool = ((i + 1) % dims[col] == 0 || i == n - 1);
	}
	if (g_opts & ONE)
	{
		ind = i;
		*newbool = 1;
	}
	return (ind);
}

void	ft_recurse(t_dirvec *dirs)
{
	t_dirdata		**tmp;
	unsigned long	i;

	if (g_opts & MODTIME)
	{
		if (g_opts & REVERSE)
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_rt);
		else
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_ft);
	}
	else
	{
		if (g_opts & REVERSE)
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_r);
		else
			tmp = (t_dirdata **)vec_sort(dirs, sizeof(t_dirdata), &dd_cmp_f);
	}
	i = 0;
	while (i < dirs->len / sizeof(t_dirdata))
	{
		ft_printf("\n%s:\n", tmp[i]->full_path);
		ft_list_dir(tmp[i++]->full_path);
	}
	free_dirs(dirs);
	free(tmp);
}

void	ft_handle_dirs(t_dirvec *dirvec)
{
	if (g_opts & RECURSIVE)
		ft_recurse(dirvec);
	else
		free_dirs(dirvec);
}

void	ft_list_dir(const char *dir_name)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*path;
	t_entryvec		*hvec;
	t_dirvec		*dirvec;

	ft_memset(g_max, 0, 5 * sizeof(unsigned int));
	ft_memset(g_total, 0, 2 * sizeof(unsigned int));
	if ((dirp = opendir(dir_name)) == NULL)
		perror("Failed to open directory");
	if (dirp == NULL)
		return ;
	path = ft_strjoin(dir_name, "/");
	hvec = (t_entryvec *)vecnew(NULL, sizeof(t_fdata));
	dirvec = (t_dirvec *)vecnew(NULL, sizeof(char *));
	while ((dp = readdir(dirp)) != NULL)
		if (dp->d_namlen >= 1 && (dp->d_name[0] != '.' || g_opts & FT_ALL))
			ft_add_to_vec(path, dp->d_name, hvec, dirvec);
	if (g_opts & LONG && g_total[files] > 0)
		ft_printf("total %u\n", g_total[blocks]);
	ft_print_heap(hvec);
	ft_handle_dirs(dirvec);
	closedir(dirp);
	free(path);
}
