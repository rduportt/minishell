/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:04:10 by rduport           #+#    #+#             */
/*   Updated: 2025/05/13 17:35:41 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	handle_cd_path(t_cd *cd, char **args)
{
	if (!getcwd(cd->old_pwd, PATH_MAX))
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (handle_cd_home(cd))
			return (1);
	}
	else
		cd->path = ft_strdup(args[1]);
	return (0);
}

int	update_pwd_vars(t_cd *cd, t_env *env, t_parsing *parsing)
{
	char	**tmp_tab;

	cd->temp = ft_strjoin("OLDPWD=", cd->old_pwd);
	if (!cd->temp)
		return (1);
	tmp_tab = malloc(sizeof (char *) * 2);
	tmp_tab[0] = ft_strdup(cd->temp);
	tmp_tab[1] = NULL;
	ft_export(env, tmp_tab, parsing);
	free(cd->temp);
	free_tab(tmp_tab);
	tmp_tab = NULL;
	cd->temp = ft_strjoin("PWD=", cd->new_pwd);
	if (!cd->temp)
		return (1);
	tmp_tab = malloc(sizeof (char *) * 2);
	tmp_tab[0] = ft_strdup(cd->temp);
	tmp_tab[1] = NULL;
	ft_export(env, tmp_tab, parsing);
	free(cd->temp);
	free_tab(tmp_tab);
	return (0);
}

int	exec_cd(char **args, t_env *env, t_parsing *parsing)
{
	t_cd	cd;
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (!args || !args[0] || i > 2)
	{
		perror("minishell: cd: too many arguments");
		return (1);
	}
	if (handle_cd_path(&cd, args))
		return (1);
	cd.ret = chdir(cd.path);
	free(cd.path);
	if (cd.ret != 0)
		return (perror("minishell: cd"), 1);
	if (!getcwd(cd.new_pwd, PATH_MAX))
		return (perror("minishell: cd: getcwd"), 1);
	if (update_pwd_vars(&cd, env, parsing))
		return (1);
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_env *env, int (*pipes)[2], t_parsing *parsing, char **param)
{
	int	code;

	printf("exit\n");
	if (!param || !param[0])
	{
		free_all(parsing, env, pipes);
		exit(0);
	}
	if (is_numeric(param[0]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", param[0]);
		free_all(parsing, env, pipes);
		exit(2);
	}
	if (param[1])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	code = ft_atoi(param[0]);
	free_all(parsing, env, pipes);
	exit(code % 256);
}
