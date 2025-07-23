/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:11:05 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:11:06 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**split_path(char **envp)
{
	int			i;
	char		**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char **envp, char *str)
{
	int		i;
	char	**paths;
	char	*part_path;
	char	*path;

	if (!str)
		return (NULL);
	paths = split_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, str);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_array(paths), path);
		free(path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

int	is_direct_path(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '/')
			return (1);
		j++;
	}
	return (0);
}

int	exec(t_parsing *parsing, t_env *envp)
{
	if (prepare_commands(parsing, envp) == -1)
		return (-1);
	exec_cmd(parsing, envp);
	return (1);
}
