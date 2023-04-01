/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:53:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/02 01:00:29 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\nminishell $> ", 14);
		g_exit_code = 128 + sig;
	}
}

void	handle_signal_2(int sig)
{
	if (sig == SIGINT)
	{
		//write(STDOUT_FILENO, "\nminishell $> ", 14);
		g_exit_code = 128 + sig;
	}
	if (sig == SIGTSTP)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		g_exit_code = 128 + sig;
	}
}

void	handle_signal_3(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\nminishell $> ", 14);
	}
	if (sig == SIGTSTP)
	{
		write(STDOUT_FILENO, "Here-document at line 2 delimited by end-of-file\n", 50);
	}
}

void	signal_handle_interactive(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handle_non_interactive(void)
{
	signal(SIGINT, &handle_signal_2);
	signal(SIGQUIT, &handle_signal_2);
}

void	signal_handle_heredoc(void)
{
	signal(SIGINT, &handle_signal_3);
	signal(SIGQUIT, &handle_signal_3);
}
