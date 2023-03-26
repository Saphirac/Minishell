/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 23:08:53 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/26 03:38:09 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Create a subprocess, apply pipes redirections,
 * 			then apply input and output redirections,
 * 			and execute the given command/builtin.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * @param	node The first node of the token list containing a pipe.
 * @param	fd The file descriptor of the pipe's output.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__subprocess(
	t_shell *const shell,
	t_token const *const node,
	int const fds[2])
{
	int const	pid = fork();

	if (pid == -1)
		return (internal_error("fork()"));
	if (pid)
	{
		if (pid_lst_add_back(&shell->pids, pid))
			return (internal_error("pid_lst_add_back()"));
		return (EXIT_SUCCESS);
	}
	if (close(shell->stdin_backup) || (fds[0] != STDIN_FILENO && close(fds[0])))
		return (internal_error("close()"));
	token_lst_del_range(&shell->tokens, node, NULL);
	if (redirections(&shell->tokens, fds[1]) || run(shell))
		return (EXIT_FAILURE);
	exit(g_exit_code);
}

/**
 * @brief	Execute a pipeline of commands/builtins in subprocesses,
 * 			applying pipe redirections in a first time,
 * 			and input and output redirections in a second time.
 * 			If an error occurs, an error message is output on stderr.
 * 
 * @param	shell The context which contains the program's data.
 * @param	node The first node of the token list containing a pipe.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__pipeline(t_shell *const shell, t_token const *node)
{
	int	fds[2];

	while (node)
	{
		if (pipe(fds))
			return (pid_lst_kill(&shell->pids, SIGTERM),
				internal_error("pipe()"));
		if (__subprocess(shell, node, fds))
			return (close(fds[0]), close(fds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (close(fds[0]), close(fds[1]),
				pid_lst_kill(&shell->pids, SIGTERM), internal_error("dup2()"));
		if (close(fds[0]) || close(fds[1]))
			return (pid_lst_kill(&shell->pids, SIGTERM),
				internal_error("close()"));
		token_lst_del_range(&shell->tokens, shell->tokens.head, node->next);
		node = token_lst_find_first_by_type(&shell->tokens, T_PIPE);
	}
	if (__subprocess(shell, NULL, (int [2]){STDIN_FILENO, STDOUT_FILENO})
		|| pid_lst_wait(&shell->pids))
		return (pid_lst_kill(&shell->pids, SIGTERM), EXIT_FAILURE);
	return (pid_lst_clear(&shell->pids), EXIT_SUCCESS);
}

/**
 * @brief	Execute a builtin with no pipes in the same process as the shell.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
inline static int	__builtin_alone(t_shell *const shell)
{
	size_t	i;

	i = 0LU;
	while (ft_strcmp(g_builtin[i].name, shell->tokens.head->str))
		++i;
	return (g_builtin[i].func(&shell->env, shell->tokens.head->next));
}

/**
 * @brief	Proceed to the execution of the given commands/builtins,
 * 			using subprocess except when running a builtin with no pipes,
 * 			applying input, output, and pipes redirections.
 * 			If an error occurs, an error message is output.
 * 
 * @param	shell The context which contains the program's data.
 * 
 * @return	EXIT_SUCCESS, or EXIT_FAILURE if an error occured.
 */
int	execution(t_shell *const shell)
{
	t_token const *const	node
		= token_lst_find_first_by_type(&shell->tokens, T_PIPE);

	if (node || !token_lst_is_first_builtin(&shell->tokens))
	{
		shell->stdin_backup = dup(STDIN_FILENO);
		if (shell->stdin_backup == -1)
			return (internal_error("dup()"));
		if (__pipeline(shell, node))
			return (dup2(shell->stdin_backup, STDIN_FILENO),
				close(shell->stdin_backup), EXIT_FAILURE);
		if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
			return (close(shell->stdin_backup), internal_error("dup2()"));
		if (close(shell->stdin_backup))
			return (internal_error("close()"));
		return (EXIT_SUCCESS);
	}
	return (__builtin_alone(shell));
}
