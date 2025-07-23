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

int	any_word(t_token *lexer)
{
	int	i;

	i = -1;
	while (lexer[++i].string != NULL)
		if (lexer[i].type == T_WORD)
			return (1);
	return (0);
}

void	free_parsing(t_parsing *parsing)
{
	int	i;

	i = -1;
	if (!parsing)
		return ;
	while (++i < parsing[0].count)
	{
		if (parsing[i].cmd)
			free(parsing[i].cmd);
		if (parsing[i].arg)
			free_array(parsing[i].arg);
		if (parsing[i].infile)
			free_array(parsing[i].infile);
		if (parsing[i].outfile)
			free_array(parsing[i].outfile);
		if (parsing[i].append)
			free_array(parsing[i].append);
		if (parsing[i].heredoc)
			free_array(parsing[i].heredoc);
		if (parsing[i].cmd_path)
			free(parsing[i].cmd_path);
	}
	free(parsing);
}

pid_t	g_child_pid = 0;

int	free_and_exit(t_env *env)
{
	if (env->env)
		free_tab(env->env);
	if (env->export)
		free_tab(env->export);
	free(env);
	printf("exit\n");
	close(0);
	close(1);
	close(2);
	return (EXIT_SUCCESS);
}

void	process_input(char *input, t_env *env)
{
	char		**split;
	t_token		*lexer;
	t_parsing	*parsing;
	int			i;

	add_history(input);
	split = ft_split_readline(input, ' ');
	if (!split)
		return ;
	lexer = ft_lexer(split);
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	parsing = ft_parsing(lexer, env->env);
	i = -1;
	while (lexer[++i].type != T_EOF)
		free(lexer[i].string);
	free(lexer);
	if (!parsing)
		return ;
	exec(parsing, env);
	ft_export_questionmark(env, parsing[0].exit_status);
	g_child_pid = 0;
	free_parsing(parsing);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	ft_export_questionmark(env, 0);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_child_pid = 0;
		input = readline("Minishell> ");
		if (!input)
			exit(free_and_exit(env));
		if (g_child_pid == 130)
			ft_export_questionmark(env, 130);
		if (ft_strcmp(input, "") != 0)
			process_input(input, env);
		free(input);
	}
	return (0);
}
