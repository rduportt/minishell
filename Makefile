# Variables
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
LIBFT		= libft/libft.a
PRINTF		= printf/libftprintf.a

# Sources - Ajoutez tous vos fichiers .c ici
SRCS		= minishell.c signaux.c \
			  built_in.c built_in2.c \
			  env.c env2.c env3.c env4.c env5.c\
			  exec.c exec2.c exec3.c exec4.c exec5.c exec6.c exec7.c\
			  lexer.c lexer2.c lexer3.c \
			  parsing.c parsing2.c parsing3.c parsing4.c parsing5.c

OBJS = $(SRCS:.c=.o)

# Règles
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C printf

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C printf

re: fclean all

.PHONY: all clean fclean re