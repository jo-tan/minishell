NAME		= minishell

# Sources
S_FILES		= src/main.c src/parsing_read_cmd.c src/check_print.c
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