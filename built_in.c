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

int	actual_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("no path found");
		return (-1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

int	is_valid_option(char *s)
{
	int	i;

	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i - 1] == 'n' && s[i] == '\0')
		return (1);
	return (0);
}

int	print_echo(char **para, int i)
{
	while (para[i])
	{
		ft_putstr_fd(para[i], 1);
		if (para[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (0);
}

int	echo(char **para)
{
	int	option;
	int	i;

	i = 1;
	option = 0;
	if (!para)
		return (printf("\n\n"), 0);
	while (is_valid_option(para[i]))
	{
		option = 1;
		i++;
	}
	print_echo(para, i);
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	handle_cd_home(t_cd *cd)
{
	cd->path = getenv("HOME");
	if (!cd->path)
	{
		perror("minishell: cd: HOME not set");
		return (1);
	}
	return (0);
}
