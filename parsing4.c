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

int	check_quotes(int i, char *string)
{
	int	quote;

	quote = 0;
	while (string[i])
	{
		if (string[i] == '\'' && quote == 0)
			quote = '\'';
		else if (string[i] == '\'' && quote == '\'')
			quote = 0;
		else if (string[i] == '$' && quote != '\'')
			break ;
		i++;
	}
	return (i);
}

char	*string_env(char *string, char **env)
{
	char	*env_value;
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	i = check_quotes(i, string);
	if (!string[i])
		return (ft_strdup(string));
	i++;
	env_value = get_env_value(string, &i, env);
	if (!env_value)
		return (NULL);
	result = assemble_result(string, env_value, i, &j);
	free(env_value);
	return (result);
}

t_parsing	*init_parsing(int cmd_count)
{
	t_parsing	*parsing;
	int			i;

	parsing = malloc(sizeof(t_parsing) * (cmd_count + 1));
	if (!parsing)
		return (NULL);
	i = -1;
	while (++i <= cmd_count)
	{
		parsing[i].cmd = NULL;
		parsing[i].arg = NULL;
		parsing[i].infile = NULL;
		parsing[i].outfile = NULL;
		parsing[i].append = NULL;
		parsing[i].heredoc = NULL;
		parsing[i].pid = -1;
		parsing[i].fd = -1;
		parsing[i].cmd_path = NULL;
		parsing[i].is_built_in = 0;
		parsing[i].exit_status = 0;
		parsing[i].builtin_code = 0;
		parsing[i].count = 0;
	}
	parsing[cmd_count].cmd = NULL;
	return (parsing);
}

void	allocate_cmd(t_parsing *p, int j, t_count c)
{
	p[j].arg = malloc(sizeof(char *) * (c.arg + 1));
	p[j].infile = malloc(sizeof(char *) * (c.infile + 1));
	p[j].outfile = malloc(sizeof(char *) * (c.outfile + 1));
	p[j].append = malloc(sizeof(char *) * (c.append + 1));
	p[j].heredoc = malloc(sizeof(char *) * (c.heredoc + 1));
	if (p[j].arg)
		p[j].arg[0] = NULL;
	if (p[j].infile)
		p[j].infile[0] = NULL;
	if (p[j].outfile)
		p[j].outfile[0] = NULL;
	if (p[j].append)
		p[j].append[0] = NULL;
	if (p[j].heredoc)
		p[j].heredoc[0] = NULL;
}

void	update_count(t_count *count, int type)
{
	if (type == T_WORD)
		count->arg++;
	else if (type == T_REDIR_IN)
		count->infile++;
	else if (type == T_REDIR_OUT)
		count->outfile++;
	else if (type == T_REDIR_APPEND)
		count->append++;
	else if (type == T_REDIR_HEREDOC)
		count->heredoc++;
}

