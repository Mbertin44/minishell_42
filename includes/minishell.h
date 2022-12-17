/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/16 20:58:10 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <curses.h>
# include "../libft/includes/libft.h"
# include "../librl/readline.h"
# include "../librl/history.h"

# define TRUE 1
# define FALSE 0

# define INTRO "\
#/bin/bash \n\
bash pretty/intro_minishell.sh \n\
"

/***** STRUTURE *****/

typedef struct s_builtins
{
	char	**env_unset;
	char	**env_export;
	char	**env_ord;
	char	*unset_arg;
	char	*exp_arg;
	char	*export_var;
	char	*order_var;
	char	*echo_var;
	char	echo_priority;
	int		echo_first;
	int		echo_flag_n;
	int		minus_n;
	int		echo_dble_q;
	int		echo_sgle_q;
	int		forget_minus;
	int		dont_do_minus;
	int		first_word;
}	t_builtins;

typedef struct s_flag
{
	char	*output;
	int		output_count;
	int		chevron_count;
	int		input_count;
	int		pipe_count;
	int		*fd_out;
	int		stdout_backup;
	int		stdin_backup;
	int		var_not_found;
	char	chevron;
}	t_flag;

typedef struct s_quote
{
	int		double_quote_count;
	int		simple_quote_count;
	int		len_of_replacement;
	int		begin;
	char	quote_priority;
	char	temp_priority;
}	t_quote;

typedef struct s_vault
{
	int			spc_count;
	char		*read_line;
	char		*env_path;
	char		**env;
	char		**clean_decomposer;
	char		**rl_decomp;
	char		*test;
	t_builtins	*b_in;
	t_quote		*quote;
	t_flag		*flag;
	int			activate_var; //suppression a confirmer
	char		*dollar_var;
	int			dollar_var_len;
	char		**split; //suppression a confirmer
	char		*buffer;
	int			pos;
}	t_vault;

/***** minishell.c *****/
void	init_data(t_vault *data);
void	reinit_data(t_vault *data);

/***** explore_readline.c *****/
void	explore_readline(t_vault *data);
void	built_in(t_vault *data);

/***** meta_analyzis.c *****/
int		rl_prio_n_qty(t_vault *data, int i, char c);
void	flag_count(t_vault *data, int i, int j);

/***** redirection_management.c *****/
void	execute_redirection(t_vault *data);
void	output_in_next_array(t_vault *data, int i, int *j, char c);
void	find_output_in_next_array(t_vault *data, char *rl_decomp_array);
void	find_output_in_same_array(t_vault *data, char *rl_decomp_array);
void	stdout_redirection(t_vault *data, char *redirection);
char	*clean_the_chevron(t_vault *data, char *str);
void	output_in_same_array(t_vault *data, int i, int *j, char c);
int		while_is_not_flag(char *str, int i);
int		flag_in_str(char *str);
void	clean_output(t_vault *data, int i);
void	clean_output_next_array(t_vault *data, int i);
int		len_without_output(t_vault *data, int i, int temp, int *begin);

/***** double_quote_management.c *****/
void	find_str_quote(t_vault *data);
void	find_decomposer_array_to_replace(t_vault *data, int end);
void	replace_decomposer_array(t_vault *data, int end, int *i);
void	find_decomposer_to_switch(t_vault *data, int to_switch);
void	switch_decomposer(t_vault *data, int *next_array, int *actual_array);
void	len_of_replacement(t_vault *data, int *i);

/***** built_in.c *****/
void	ft_cd(t_vault *data, int row);
void	ft_pwd(t_vault *data, int row);
void	ft_exit(t_vault *data);
void	ft_env(t_vault *data, int env);
void	ft_echo(t_vault *data, int row);

/***** parsing_utils ******/
int		check_next_char(t_vault *data, int row, int i);
void	quote_priority(t_vault *data, int row);
void	parse_row(t_vault *data, int row);
int		echo_sgle_quote(t_vault *data, int row, int i);
int		echo_dble_quote(t_vault *data, int row, int i);

/***** built_in2.c *****/
void	ft_unset(t_vault *data, int row);
void	remove_line_env(t_vault *data, int i);
void	ft_export(t_vault *data, int row);
void	add_line_env(t_vault *data);
void	order_env(t_vault *data);
void	export_only_format(t_vault *data, char *buff2, char **temp, int i);
void	copy_env(t_vault *data, char **temp, int i);

/***** personnal_fonction.c *****/
int		check_if_inside_quote(char *str, char c);
void	print_double_array(char **array);
int		dbl_array_len(char **array);

/***** error_mgmnt.c *****/
int		check_error(t_vault *data, int row);

/***** minishell_utils.c *****/
void	print_row(t_vault *data, int row);
int		ft_isinset(char c);
void	row_parsing(t_vault *data);

/***** built_in_utils.c *****/
void	join_unset(t_vault *data, int row);
void	swap_lines(t_vault *data, int rows);
void	dup_env(t_vault *data);
void	var_prep(t_vault *data, int row);

/***** dollar_utils.c *****/
int		dollar_var_to_extract(t_vault *data, int row, int i);
char	*var_extract(t_vault *data, int row, int position);
char	*does_var_exist(t_vault *data);
char	*expand_var(t_vault *data, int row_var);

//void	clean_quote(t_vault *data, int row);
//int		insert_row(int pos, int count, char **dest, char **source);
//void	split_on_char(t_vault *data, int row, char c);
//void	change_tab(t_vault *data, int row);

/***** minus_utils. *****/
void	parse_minus(t_vault *data);
void	recreate_arg_tab(t_vault *data, char **tab);
char	**create_temp_swap(t_vault *data, int row);
void	check_minus_validity(t_vault *data, int row, int i);

/***** PRETTY *****/
/***** pretty_intro_mini.c *****/
void	intro_minishell(void);
void	intro_minishell_p2(void);
void	intro_minishell_p3(void);

/***** pretty_colors.c *****/
void	lred(void);
void	lcyan(void);
void	lyellow(void);
void	reset(void);

#endif