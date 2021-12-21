# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    valgrind.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 15:19:04 by jodufour          #+#    #+#              #
#    Updated: 2021/12/10 15:19:50 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VG_OPT			=	--suppressions=ignoreliberror
VG_OPT			+=	--leak-check=full
VG_OPT			+=	--show-leak-kinds=all

valgrind: ${NAME}
	$@ ${VG_OPT} ./$<

.PHONY: valgrind
