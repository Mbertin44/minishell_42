/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:05:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/27 15:19:28 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_for_pipe(t_vault *data)
{
	int		row;
	int		i;
	int		len;

	row = 0;
	i = 0;
	len = 0;
	while (data->rl_dec[row])
	{
		while (data->rl_dec[row][i])
		{
			if (data->rl_dec[row][i] == '\'' || data->rl_dec[row][i] == '\"')
			{
				data->quote->quote_priority = data->rl_dec[row][i];
				while (data->rl_dec[row] && data->rl_dec[row][i] != data->quote->quote_priority)
					i++;
			}
			else if (data->rl_dec[row][i] == '|')
				len++;
			i++;
		}
		i = 0;
		row++;
	}
	if (len > 0)
		bigger_tab(data, len);
}

void	bigger_tab(t_vault *data, int len)
{
	char	**temp;
	int		i;
	int		row;
	int		j;
	int		k;

	row = 0;
	i = 0;
	temp = NULL;
	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_dec) + len * 2 + 1);
	while (data->rl_dec[row])
	{
		j = 0;
		if (ft_strchr(data->rl_dec[row], '|') == 0)
		{
			temp[i] = ft_strdup(data->rl_dec[row]);
			free (data->rl_dec[row]);
			i++;
		}
		else
		{
			while (data->rl_dec[row][j])
			{
				k = 0;
				if (data->rl_dec[row][j] == '|')
				{
					temp[i] = ft_calloc(sizeof(char), 2);
					temp[i][0] = '|';
					i++;
				}
				else
				{
					temp[i] = ft_calloc(sizeof(char), ft_strlen(data->rl_dec[row]));
					while (data->rl_dec[row][j] && data->rl_dec[row][j] != '|')
					{
						temp[i][k] = data->rl_dec[row][j];
						k++;
						j++;
					}
					i++;
					j--;
				}
				j++;
			}
			free (data->rl_dec[row]);
		}
		row++;
	}
	free(data->rl_dec);
	data->rl_dec = temp;
}

