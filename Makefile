NAME = minishell
CC = cc
CF = -Wall -Wextra -Werror -MMD -MP
INC = inc/
LIBFT = libft.a
LIB_DIR = libft/
S_DIR = src
O_DIR = obj
S_FILES = src/main.c

O_FILES = $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.o,$(S_FILES))
D_FILES = $(patsubst $(S_DIR)/%.c,$(O_DIR)/%.d,$(S_FILES))

RM = rm -rf

all: $(LIBFT) $(NAME)

$(NAME): $(O_FILES)
	@$(CC) -I $(INC) -lreadline -L $(LIB_DIR) -lft $(O_FILES) -o $(NAME)
	@echo " [ ok ] | minishell is ready!"

-include $(D_FILES)

$(O_DIR)/%.o: $(S_DIR)/%.c
	@echo "Compiling $<"
	@mkdir -p $(O_DIR) $(D_DIR)
	@$(CC) $(CF) -I $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_DIR)
	@echo "libft is ready."

clean:
	@$(RM) $(O_DIR)
	@echo "object and dependend files removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "binary file removed."

re: fclean all

.PHONY: all clean fclean re