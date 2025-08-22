NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = 	ft_printf.c \
		printstr.c \
		printint.c \
		printunsigned.c \
		printaddress.c \
		printhex.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $@ $^

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re