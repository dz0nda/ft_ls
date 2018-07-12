/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls_fill.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/03 03:34:11 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 14:01:55 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static char		ft_fill_chmod_type(int mode, int param, char *name)
{
	char		c;
	acl_t		acl;

	c = '?';
	param == 0 && S_ISREG(mode) ? c = '-' : 0;
	param == 0 && S_ISDIR(mode) ? c = 'd' : 0;
	param == 0 && S_ISCHR(mode) ? c = 'c' : 0;
	param == 0 && S_ISBLK(mode) ? c = 'b' : 0;
	param == 0 && S_ISFIFO(mode) ? c = 'p' : 0;
	param == 0 && S_ISLNK(mode) ? c = 'l' : 0;
	param == 0 && S_ISSOCK(mode) ? c = 's' : 0;
	if (param == 1 && ((acl = acl_get_file(name, ACL_TYPE_EXTENDED)) < 0))
		acl_free(acl);
	param == 1 ? mode = listxattr(name, NULL, 0, XATTR_NOFOLLOW) : 0;
	if (param == 1)
		c = mode > 0 ? '@' : ' ';
	if (param == 1)
		c = acl ? '+' : c;
	param == 1 && acl ? acl_free(acl) : 0;
	return (c);
}

char			*ft_fill_chmod(int mode, char *name)
{
	char		str[12];
	char		*ret;

	str[0] = ft_fill_chmod_type(mode, 0, name);
	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	str[3] = (mode & S_IXUSR) && (mode & S_ISUID) ? 's' : str[3];
	str[3] = str[3] == '-' && (mode & S_ISUID) ? 'S' : str[3];
	str[4] = (mode & S_IRGRP) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	str[6] = (mode & S_IXGRP) && (mode & S_ISGID) ? 's' : str[6];
	str[6] = str[6] == '-' && (mode & S_ISGID) ? 'l' : str[6];
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';
	str[9] = (mode & S_IXOTH) && (mode & S_ISVTX) ? 't' : str[9];
	str[9] = str[9] == '-' && (mode & S_ISVTX) ? 'T' : str[9];
	str[10] = ft_fill_chmod_type(mode, 1, name);
	str[11] = '\0';
	ret = ft_strdup(str);
	return (ret);
}

char			*ft_fill_time(t_stat stat)
{
	char		string[256];
	char		**tab;
	time_t		timer;
	time_t		i;
	char		*str;

	ft_bzero(string, 256);
	if ((tab = ft_strsplit(ctime(&stat.st_mtime), ' ')))
	{
		time(&timer);
		i = stat.st_mtime;
		ft_strcpy(string, tab[1]);
		ft_strlen(tab[2]) == 2 ? ft_strcat(string, " ") :
			ft_strcat(string, "  ");
		ft_strcat(string, tab[2]);
		(timer - i) >= 15778800 ? ft_strcat(string, "  ") :
			ft_strcat(string, " ");
		(timer - i) >= 15778800 ? ft_strncat(string, tab[4], 4) :
		ft_strncat(string, tab[3], 5);
		ft_stradel(&tab);
	}
	str = ft_strdup(string);
	return (str);
}

char			*ft_is_min_maj(t_stat stat, int param)
{
	char		*str;
	char		*tmp;

	str = NULL;
	tmp = NULL;
	if (S_ISCHR(stat.st_mode) || S_ISBLK(stat.st_mode))
	{
		param == 0 ? tmp = ft_itoa(major(stat.st_rdev)) : 0;
		param == 0 ? str = ft_strjoin(tmp, ",") : 0;
		param == 0 ? ft_strdel(&tmp) : 0;
		param == 1 ? str = ft_itoa(minor(stat.st_rdev)) : 0;
	}
	else
	{
		param == 0 ? str = ft_strdup("") : 0;
		param == 1 ? str = ft_itoa(stat.st_size) : 0;
	}
	str == NULL ? str = ft_strdup(" ") : 0;
	return (str);
}
