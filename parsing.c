/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal2.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:38:52 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 16:08:42 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_parsing	*return_null_parsing(t_parsing *parsing, int j)
{
	int	i;

	i = -1;
	if (parsing)
	{
		while (++i < j)
		{
			if (parsing[i].arg)
				free_tab(parsing[i].arg);
			if (parsing[i].infile)
				free_tab(parsing[i].infile);
			if (parsing[i].outfile)
				free_tab(parsing[i].outfile);
			if (parsing[i].append)
				free_tab(parsing[i].append);
			if (parsing[i].heredoc)
				free_tab(parsing[i].heredoc);
			if (parsing[i].cmd)
				free(parsing[i].cmd);
			if (parsing[i].cmd_path)
				free(parsing[i].cmd_path);
		}
		free(parsing);
	}
	return (printf("\n"), NULL);
}

t_count	count_init(void)
{
	t_count	count;

	count.arg = 0;
	count.infile = 0;
	count.outfile = 0;
	count.heredoc = 0;
	count.append = 0;
	return (count);
}

char	*exctract_file_name(char *dir)
{
	char	*file_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dir[i] == '<' || dir[i] == '>' || dir[i] == ' ')
		i++;
	file_name = ft_strdup_quote(&dir[i]);
	return (file_name);
}

char	*extract_env_name(char *string, int *idx)
{
	int		j;
	char	*name;

	j = 0;
	name = malloc(ft_strlen(string) + 1);
	if (!name)
		return (NULL);
	if (string[*idx] == '?')
		name[j++] = string[(*idx)++];
	else
	{
		while (string[*idx] && (ft_isalnum(string[*idx])
				|| string[*idx] == '_'))
			name[j++] = string[(*idx)++];
	}
	name[j] = '\0';
	return (name);
}

int	copy_before_var(char *string, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (string[i])
	{
		if (string[i] == '\'' && quote == 0)
			quote = '\'';
		else if (string[i] == '\'' && quote == '\'')
			quote = 0;
		else if (string[i] == '$' && quote != '\'')
			break ;
		result[j++] = string[i++];
	}
	return (j);
}
