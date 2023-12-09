# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 18:25:12 by jo-tan            #+#    #+#              #
#    Updated: 2023/11/14 15:25:27 by jo-tan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# Sources
S_FILES		= src/main.c \
				src/init_envp.c \
				src/check_valid_input.c \
				src/read_cmd.c \
				src/parsing.c \
				src/parsing_quote_utils.c \
				src/parsing_expansion_utils1.c \
				src/parsing_expansion_utils2.c \
				src/check_print.c \
				src/token_list.c
S_DIR		= src

LIBFT		= libft/libft.a
LIBFT_DIR	= libft

# Objects
O_DIR		= obj

O_FILES		= $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.o,$(S_FILES))
D_FILES		= $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.d,$(S_FILES))

# Compilation
CC			= cc
CF			= -Wall -Wextra -Werror #-MMD -MP
INC			= -I inc/ -I $(LIBFT_DIR)

# Cleaning
RM			= rm -rf

all:		$(LIBFT) $(NAME)

$(NAME):	$(O_FILES)
	@$(CC) -o $(NAME) $(O_FILES) -L $(LIBFT_DIR) -lreadline -lft $(INC)
	@echo " [ ok ] | minishell is ready!"

-include $(D_FILES)

$(O_DIR)/%.o: $(S_DIR)/%.c
	@echo "Compiling $<"
	@mkdir -p $(O_DIR) $(D_DIR)
	@$(CC) $(CF) $(INC) -c $< -o $@

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