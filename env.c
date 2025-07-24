/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:27:00 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:27:01 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

t_env	*init_env_i(t_env *env)
{
	char	pwd[32768];

	env->env = malloc(sizeof(char *) * 4);
	env->export = malloc(sizeof(char *) * 4);
	getcwd(pwd, 32768);
	env->env[0] = ft_strjoin("PWD=", pwd);
	env->export[0] = ft_strjoin("declare -x PWD=", pwd);
	env->env[1] = ft_strdup("SHLVL=1");
	env->export[1] = ft_strdup_export("SHLVL=1");
	env->env[2] = ft_strdup("_=./minishell");
	env->export[2] = ft_strdup_export("_=./minishell");
	env->env[3] = NULL;
	env->export[3] = NULL;
	return (env);
}

t_env	*fill_env(t_env *env, int count, char **envp)
{
	int	i;

	i = 0;
	while (i < count)
	{
		env->export[i] = ft_strdup_export(envp[i]);
		env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	env->export[count] = NULL;
	env->env[count] = NULL;
	sort_ascii(env->export);
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		count;

	count = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (envp == NULL || *envp == NULL)
		return (init_env_i(env));
	while (envp[count])
		count++;
	env->env = malloc (sizeof(char *) * (count + 2));
	if (!env->env)
		return (NULL);
	env->export = malloc (sizeof(char *) * (count + 1));
	if (!env->export)
	{
		free_tab(env->env);
		return (NULL);
	}
	env = fill_env(env, count, envp);
	return (env);
}

int	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "?=", 2) != 0)
		{
			write(STDOUT_FILENO, env[i], strlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (0);
}
