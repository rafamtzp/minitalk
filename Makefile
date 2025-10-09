NAME_CLIENT = client
NAME_SERVER = server

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ./printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
