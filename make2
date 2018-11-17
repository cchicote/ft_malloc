NAME = ft_malloc

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INCLUDE_PATH = ./includes

LIBFT_PATH = ./libft

SRC_PATH = ./src/

SRCS = malloc.c \

SRC = $(addprefix $(SRC_PATH), $(SRCS))

all:
	@ echo "Compiling libft"
	@ make -sC $(LIBFT_PATH)

malloc:
	@ make -sC $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) $(SRC) -I$(INCLUDE_PATH) -o ft_malloc -L ./libft/ -lft 
	@ ./ft_malloc

clean:
	@ echo "Cleaning libft"
	@ make clean -sC $(LIBFT_PATH)

fclean:
	@ echo "Fcleaning libft"
	@ make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY : all clean fclean re