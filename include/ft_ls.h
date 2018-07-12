/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/31 03:27:14 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:59:14 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/include/libft.h"
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/acl.h>
# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>

size_t					g_flag[6];

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_read
{
	DIR					*dir;
	t_dirent			*ent;
	t_stat				stat;
	t_passwd			*user;
	t_group				*grp;
}						t_read;

typedef struct			s_file
{
	char				*uid;
	char				*array[9];
	size_t				time;
	struct s_file		*next;
}						t_file;

typedef struct			s_path
{
	char				*uid;
	size_t				len[9];
	size_t				time;
	blkcnt_t			size;
	struct s_file		*lstfile;
	struct s_path		*subpath;
	struct s_path		*next;
}						t_path;

int						ft_false(int n, const char *str, const char c);
int						ft_formsize(t_path **path, t_file *file);
t_path					*ft_init(int ac, const char *av[], t_path *begin,
		size_t *i);
int						ft_solve(t_path *path, size_t count);
t_path					*ft_path_new(const char *path);
void					ft_path_add(t_path **begin, t_path *path);
t_file					*ft_file_new(const char *name, t_path *path);
void					ft_file_add(t_file **begin, t_file *file);
char					*ft_fill_chmod(int mode, char *name);
char					*ft_fill_time(t_stat stat);
char					*ft_is_min_maj(t_stat stat, int param);
void					ft_print(t_file **fil, t_path *path, size_t count);

#endif
