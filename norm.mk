# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 02:59:16 by jodufour          #+#    #+#              #
#    Updated: 2023/03/09 11:36:58 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

PHONY: norm
