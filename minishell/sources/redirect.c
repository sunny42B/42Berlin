/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:29:59 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 16:31:24 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(t_shell *shell, int i)
{
	size_t	bytes_read;
	char	buffer[1024];

	if (shell->units == 1)
		return ;
	bytes_read = read(shell->end[0], buffer, sizeof(buffer));
	while (bytes_read > 0) 
	{
		write(shell->fd[i], buffer, bytes_read);
		bytes_read = read(shell->end[0], buffer, sizeof(buffer));
	}
	close (shell->fd[i]);
	return ;
}

void	print_here_doc(t_shell *shell)
{
	shell->node = shell->head;
	while (shell->node != NULL)
	{
		printf("%s\n", (char *)shell->node->content);
		shell->node = shell->node->next;
	}
	del_node(&shell->head);
	return ;
}

void	here_doc(t_shell *shell, int i)
{
	char	*doc;

	shell->head = NULL;
	while (1)
	{
		signal_action_here();
		doc = readline("> ");
		if (g_exit_status == 130)
		{
			free(doc);
			doc = NULL;
		}
		if (!doc)
			break ;
		if (ft_strncmp(doc, shell->final[i].exec[1], \
			ft_strlen(shell->final[i].exec[1])) == 0)
			break ;
		add_history(doc);
		ft_lstadd_back(&shell->head, ft_lstnew(doc));
	}
	free(doc);
	rl_clear_history(); 
	return ;
}

void	redirect_in(t_shell *shell, int i)
{
	char	*filename;

	filename = shell->final[i].exec[1];
	if (shell->fd[i] < 0)
	{
		printf("%s: No such file or directory\n", shell->final[i].exec[1]);
		return ;
	}
	test1(shell->fd[i]);
	if (i == shell->units - 1)
		close(shell->fd[i]);
	exit (0);
}

void	redirect_out(t_shell *shell, int i)
{
	size_t	bytes_read;
	char	buffer[1024];
	int		c;

	c = 0;
	if (shell->units == 1)
		return ;
	bytes_read = read(shell->end[0], buffer, sizeof(buffer));
	while (bytes_read > 0) 
	{
		write(shell->fd[i], buffer, bytes_read);
		bytes_read = read(shell->end[0], buffer, sizeof(buffer));
	}
	close(shell->fd[i]);
	return ;
}
