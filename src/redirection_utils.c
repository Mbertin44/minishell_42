/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:53:07 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/31 10:54:36 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ajouter des free et message d'erreur au exit
char	*clean_the_chevron(t_vault *data, char *str, int i, int j)
{
	char	*temp;
	int		clean;

	clean = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str));
	if (!temp)
	{
		free (temp);
		g_error_code = 12;
		error_message(data);
		exit (EXIT_FAILURE);
	}
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == data->flag->chevron && clean == 0)
		{
			clean = 1;
			i++;
			while (str[i] == ' ')
				i++;
		}
		else if (str[i])
			temp[j++] = str[i++];
	}
	if (temp[j - 1] == ' ')
		temp[j - 1] = '\0';
	free (str);
	return (temp);
}

int	flag_in_str(char *str)
{
	if (ft_strchr(str, '>') != NULL || ft_strchr(str, '<') != NULL
		|| ft_strchr(str, '|') != NULL)
		return (TRUE);
	return (FALSE);
}

int	while_is_not_flag(char *str, int i)
{
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ' ')
		i++;
	return (i);
}

int	len_in_quote(t_vault *data, char *str, int *i)
{
	int	len;

	len = 0;
	data->quote->quote_priority = str[*i];
	(*i)++;
	while (str[*i] != data->quote->quote_priority)
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	while_quote(t_vault *data, char *str, int i)
{
	data->quote->quote_priority = str[i];
	i++;
	while (str[i] != data->quote->quote_priority)
		i++;
	i++;
	return (i);
}
