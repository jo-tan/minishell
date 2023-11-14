# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 23:41:20 by aauthier          #+#    #+#              #
#    Updated: 2022/02/01 20:22:08 by aauthier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

# Sources
SRCS_LIST		=	main.c \
					path.c \
					child.c \
					utils.c \
					utils_bis.c \
					error.c \
					strjoin_functions.c \
					ft_split.c \
					ft_calloc.c

SRCS_FOLDER		=	./srcs/
SRCS			=	$(addprefix $(SRCS_FOLDER), $(SRCS_LIST))

# Compilation
CC				=	cc
CFLAGS			+=	-Wall -Wextra -Werror
INCLUDE			=	-I include

# Cleaning
RM				=	rm -rf

# Linking
OBJS			=	${SRCS:.c=.o}


all:	$(NAME)

$(NAME): ${OBJS}
		${CC} -o ${NAME} ${OBJS} $(INCLUDE)

%.o:	%.c
		${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@

run:	all
		./$(NAME)

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY = all $(NAME) run clean fclean re 
