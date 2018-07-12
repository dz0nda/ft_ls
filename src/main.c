/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 15:36:41 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 14:00:02 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int				ft_false(int n, const char *str, const char c)
{
	char		*ret;

	ret = NULL;
	if (n == 1)
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putendl("\nusage: ls [-Raflrt1] [file ...]");
	}
	if (n == 2 || n == 3)
	{
		n == 2 ? ft_putstr("ls: ") : 0;
		ft_putstr(str);
		n == 3 ? ft_putendl(":") : 0;
		n == 3 ? ft_putstr("ls :") : 0;
		n == 3 ? ft_putstr(str) : 0;
		perror(" ");
	}
	if (ret)
		ft_strdel(&ret);
	return (0);
}

static size_t	ft_init_flags(const char *argv[])
{
	size_t		i;
	size_t		j;
	int			k;
	char		*flags;

	i = 0;
	flags = "Ralrt1";
	while (argv[++i])
	{
		j = 0;
		if (argv[i][j] != '-' || (ft_strcmp(argv[i], "--") == 0) ||
				(ft_strcmp(argv[i], "-") == 0))
			break ;
		while (argv[i][++j])
		{
			k = -1;
			while (++k < (int)(ft_strlen(flags) + 1) &&
					(flags[k] != argv[i][j]))
				if (flags[k] == '\0')
					return (ft_false(1, "", argv[i][j]));
			g_flag[k] = 1;
		}
	}
	return (i);
}

int				ft_formsize(t_path **path, t_file *file)
{
	int i;

	i = 0;
	while (++i < 9)
		if ((*path)->len[i] < ft_strlen(file->array[i]))
			(*path)->len[i] = ft_strlen(file->array[i]);
	return (1);
}

int				main(int argc, const char *argv[])
{
	t_path		*path;
	size_t		count;

	path = NULL;
	if ((count = ft_init_flags(argv)) == 0)
		return (0);
	if ((path = ft_init(argc, argv, path, &count)))
	{
		path->next != NULL ? ++count : 0;
		ft_solve(path, count);
	}
	return (0);
}
