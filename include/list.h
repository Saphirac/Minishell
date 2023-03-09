/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:23:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 20:37:35 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stddef.h>

typedef struct s_token		t_token;
typedef struct s_token_lst	t_token_lst;
typedef struct s_env		t_env;
typedef struct s_env_lst	t_env_lst;



struct s_token_lst
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
};

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
	t_token	*prev;
};

struct s_env_lst
{
	t_env	*head;
	t_env	*tail;
	size_t	size;
};

struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
	t_env	*prev;
};

/* lst functions for token_lst and token nodes */

void	token_lst_clear(t_token_lst *const list)
		__attribute__((nonnull));
void	list_del_one(t_token_lst *const list, t_token *const node)
		__attribute__((nonnull));
void	list_push_back(t_token_lst *const list, t_token *const node)
		__attribute__((nonnull));
void	list_push_front(t_token_lst *const list, t_token *const node)
		__attribute__((nonnull));
int		list_add_back(t_token_lst *const list, int const type, char *const str)
		__attribute__((nonnull));
int		list_add_front(t_token_lst *const list, int const type, char *const str)
		__attribute__((nonnull));

t_token	*token_new(int const type, char *const str);

#endif