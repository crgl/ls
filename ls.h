/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgleason <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 22:49:25 by cgleason          #+#    #+#             */
/*   Updated: 2018/08/14 22:57:16 by cgleason         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define LONG		(1 << 0)
# define RECURSIVE	(1 << 1)
# define FT_ALL		(1 << 2)
# define REVERSE	(1 << 3)
# define MODTIME	(1 << 4)
# define ONE		(1 << 5)

typedef t_vec	t_entryvec;

typedef t_vec	t_dirvec;

typedef t_vec	t_svec;

typedef int	(*t_cmp)(void *, void *);

enum			e_maxes
{
	nlinkslen,
	uidlen,
	gidlen,
	sizelen,
	namelen,
	majlen,
	minlen,
};

enum			e_totals
{
	files,
	blocks,
};

enum			e_dims
{
	row,
	col,
};

typedef struct	s_fdata
{
	char			*name;
	char			*mode;
	char			*owner;
	char			*group;
	char			*time;
	time_t			acc_time;
	long			nsec;
	unsigned long	size;
	unsigned int	nlinks;
	unsigned int	majnum;
	unsigned int	minnum;
}				t_fdata;

typedef struct	s_dirdata
{
	char			*full_path;
	char			*name;
	time_t			acc_time;
	long			nsec;
}				t_dirdata;

long			ft_max(long num1, long num2);
unsigned int	num_digits(unsigned int n);
char			*ft_mode_check(mode_t mode);
char			ft_1chr_ftype(mode_t mode);
void			print_usage(void);

void			ft_vector_args(char *name, t_vec *hvec, t_vec *dirvec,
					int *fb);
t_fdata			*entry_initializer(struct stat *buf, char *name, char *fmode);
void			ft_add_to_vec(char *path, char *name, t_vec *hvec,
					t_vec *dirvec);
void			heap_repair(void **array, int ind, int n, t_cmp cmp);
void			**vec_sort(t_vec *hvec, size_t sz, t_cmp cmp);
void			ft_print_heap(t_entryvec *hvec);

char			*link_processor(char *name, char *full_path, char c);
char			*ft_time_parse(time_t raw_time);
void			ft_parse_opts(char *opt_list);
void			ft_order_args(int argc, char **argv, t_svec *dirs,
					t_entryvec *files);

long			set_ind_newlines(long *dims, long i, long n, long *newbool);
void			ft_recurse(t_dirvec *dirs);

int				secret_strcmp(void *e1, void *e2);
int				dd_cmp_f(void *e1, void *e2);
int				dd_cmp_r(void *e1, void *e2);
int				dd_cmp_ft(void *e1, void *e2);
int				dd_cmp_rt(void *e1, void *e2);
int				fd_cmp_f(void *e1, void *e2);
int				fd_cmp_r(void *e1, void *e2);
int				fd_cmp_ft(void *e1, void *e2);
int				fd_cmp_rt(void *e1, void *e2);

void			ft_print_long(t_fdata **arr, unsigned long n);
void			ft_print_short(t_fdata **arr, long n);
void			ft_list_dir(const char *dir_name);

void			free_files(t_entryvec *hvec);
void			free_dirs(t_dirvec *dirs);

unsigned int	g_opts;
unsigned int	g_max[7];
unsigned int	g_total[2];

#endif
