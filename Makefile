# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 18:25:12 by jo-tan            #+#    #+#              #
#    Updated: 2023/12/19 12:43:06 by aauthier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# Sources
S_FILES		=	main.c \
				check_valid_input.c \
				parsing_read_cmd.c \
				check_print.c \
				token_list.c \
				parsing_quote_utils.c \
				child.c \
				error.c \
				execution.c \
				dummy_builtins.c \
				path_finding.c
S_DIR		= src

LIBFT		= libft/libft.a
LIBFT_DIR	= libft

# Objects
O_DIR		= obj

O_FILES		= $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.o,$(S_FILES))

# Compilation
CC			= clang
CF			= -Wall -Wextra -Werror
INC			= -I inc/ -I $(LIBFT_DIR)

# Cleaning
RM			= rm -rf

all:		$(LIBFT) $(NAME)

$(NAME):	$(O_FILES)
	@$(CC) -L $(LIBFT_DIR) -L /usr/local/Cellar/readline/8.2.1/lib -o $(NAME) $(O_FILES) -lreadline -lft $(INC)
	@echo " [ ok ] | minishell is ready!"

$(O_DIR)/%.o: $(S_DIR)/%.c
	@echo "Compiling $<"
	@mkdir -p $(O_DIR) $(D_DIR)
	@$(CC) $(CF) -I/usr/local/Cellar/readline/8.2.1/include $(INC) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "libft is ready."

clean:
	@$(RM) $(O_DIR)
	@make --no-print-directory -C libft fclean
	@echo "Objects and dependend files removed."

fclean:	clean
	@$(RM) $(NAME)
	@make --no-print-directory -C libft fclean
	@echo "Binary files removed."

re:		fclean all

.PHONY:	all clean fclean re