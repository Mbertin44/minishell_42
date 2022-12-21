/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:24:04 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/21 11:04:30 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc(t_vault *data)
{
	char	*str;

	data->flag->heredoc_fd = open("temp_heredoc", O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
	while (data->flag->heredoc_delimiter == FALSE)
	{
		str = readline("HEREDOC> ");
		if (str == NULL)
		{
			free (str);
			break ;
		}
		if (ft_strncmp(str, data->flag->output,
				ft_strlen(data->flag->output)) == 0
			&& ft_strlen(str) == ft_strlen(data->flag->output))
			data->flag->heredoc_delimiter = TRUE;
		else
			ft_putstr_fd(str, data->flag->heredoc_fd);
		free(str);
	}
	close (data->flag->heredoc_fd);
	if (dup2(data->flag->heredoc_fd, STDIN_FILENO) == -1)
		printf("Problème avec dup2 sur heredoc\n");
}