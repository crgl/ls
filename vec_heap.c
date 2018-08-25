/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:40:50 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/19 17:40:57 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_vector_args(char *name, t_vec *hvec, t_vec *dirvec, int *fb)
{
	struct stat	buf;
	char		*fmode;
	t_fdata		*entry;

	if (lstat(name, &buf) == -1)
	{
		perror("Failed to inspect file");
		return ;
	}
	fmode = ft_mode_check(buf.st_mode);
	if ((name = link_processor(name, name, fmode[0])) == NULL)
		return ;
	if (fmode[0] != 'd')
	{
		*fb = 1;
		entry = entry_initializer(&buf, name, fmode);
		veccat(hvec, entry, sizeof(t_fdata));
		free(entry);
	}
	else
	{
		free(fmode);
		veccat(dirvec, &((t_dirdata){name, name, buf.st_mtime,
			buf.st_mtimespec.tv_nsec}), sizeof(t_dirdata));
	}
}

void	ft_add_to_vec(char *path, char *name, t_vec *hvec, t_vec *dirvec)
{
	struct stat	buf;
	char		*fmode;
	char		*full_path;
	t_fdata		*entry;

	full_path = ft_strjoin(path, name);
	if (lstat(full_path, &buf) == -1)
	{
		perror("Failed to inspect file");
		return ;
	}
	fmode = ft_mode_check(buf.st_mode);
	name = link_processor(name, full_path, fmode[0]);
	if (name == NULL)
		return ;
	entry = entry_initializer(&buf, name, fmode);
	veccat(hvec, entry, sizeof(t_fdata));
	if (fmode[0] == 'd' && dirvec && ft_strcmp(name, ".") &&
		ft_strcmp(name, ".."))
		veccat(dirvec, &((t_dirdata){full_path, name, buf.st_mtime,
			buf.st_mtimespec.tv_nsec}), sizeof(t_dirdata));
	else
		free(full_path);
	free(entry);
}

void	heap_repair(void **array, int ind, int n, t_cmp cmp)
{
	int			lind;
	int			rind;
	int			maxind;
	void		*tmp;

	lind = 2 * ind + 1;
	rind = 2 * ind + 2;
	maxind = ind;
	if (lind < n)
		if (cmp(array[lind], array[maxind]) > 0)
			maxind = lind;
	if (rind < n)
		if (cmp(array[rind], array[maxind]) > 0)
			maxind = rind;
	if (maxind != ind)
	{
		tmp = array[ind];
		array[ind] = array[maxind];
		array[maxind] = tmp;
		heap_repair(array, maxind, n, cmp);
	}
}

void	**vec_sort(t_vec *hvec, size_t sz, t_cmp cmp)
{
	void			**out;
	char			*loc;
	unsigned long	i;
	void			*tmp;

	out = (void **)ft_memalloc((hvec->len / sz + 1) * sizeof(void *));
	loc = (char *)hvec->e;
	i = 0;
	while (i < hvec->len / sz)
	{
		out[i] = (void *)(loc + i * sz);
		i++;
	}
	i = hvec->len / (2 * sz) + 1;
	while (i--)
		heap_repair(out, i, hvec->len / sz, cmp);
	i = hvec->len / sz;
	while (i--)
	{
		tmp = out[i];
		out[i] = out[0];
		out[0] = tmp;
		heap_repair(out, 0, i, cmp);
	}
	return (out);
}

void	ft_print_heap(t_entryvec *hvec)
{
	t_fdata			**tmp;
	long			n;

	if (g_opts & MODTIME)
	{
		if (g_opts & REVERSE)
			tmp = (t_fdata **)vec_sort(hvec, sizeof(t_fdata), &fd_cmp_rt);
		else
			tmp = (t_fdata **)vec_sort(hvec, sizeof(t_fdata), &fd_cmp_ft);
	}
	else
	{
		if (g_opts & REVERSE)
			tmp = (t_fdata **)vec_sort(hvec, sizeof(t_fdata), &fd_cmp_r);
		else
			tmp = (t_fdata **)vec_sort(hvec, sizeof(t_fdata), &fd_cmp_f);
	}
	n = hvec->len / sizeof(t_fdata);
	if (g_opts & LONG)
		ft_print_long(tmp, n);
	else
		ft_print_short(tmp, n);
	free_files(hvec);
	free(tmp);
}
