NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra 

HFILE = ft_printf.h
FILE = ft_printf.c fonction_arg.c fonction_arg2.c fonction_libft.c fonction_libft2.c 
OBJET = $(FILE:.c=.o)

all : $(NAME)

$(NAME): $(OBJET)
	ar rcs $(NAME) $(OBJET)
clean : 
	rm -f $(OBJET)
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
