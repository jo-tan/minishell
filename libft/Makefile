NAME		= libft.a

SRCS		= ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isspace.c \
			ft_ismeta.c \
			ft_isenvname.c \
			ft_isquote.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strcpy.c \
			ft_strcat.c \
			ft_strncpy.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin_functions.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

B_SRCS		=	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJS		= ${SRCS:.c=.o}

B_OBJS		= ${B_SRCS:.c=.o}

CC			= cc
RM			= rm -f
AR			= ar rc
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME) bonus

$(NAME):	${OBJS}
			@${AR} ${NAME} ${OBJS}
			@${RN} ${NAME}

bonus:	${B_OBJS}
			@${AR} ${NAME} ${B_OBJS}
			@${RN} ${NAME}


clean:
			@${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			@${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
