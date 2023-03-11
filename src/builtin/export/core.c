/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:35:47 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/10 19:48:56 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

/**
 * @brief	Add environment variables.
 * 			No options are supported.
 * 			If any are given, current environment variables are kept unchanged,
 * 			and an error is output.
 * 
 * @param	env The linked list containing the environment variables.
 * @param	token The first node of the linked list containing the arguments. 
 * 
 * @return	The updated exit status.
 */
int	builtin_export(t_env_lst *const env, t_token const *const token)
{
	(void)env;
	(void)token;
	return (EXIT_SUCCESS);
}