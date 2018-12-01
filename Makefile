# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchicote <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/11 16:29:33 by cchicote          #+#    #+#              #
#    Updated: 2018/10/11 16:29:36 by cchicote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= ft_malloc

CC 				= gcc
CFLAGS 			= -Wall -Wextra -g #-Werror
LFLAGS 			= -lft
INC 			= -I$(INCLUDE_PATH)

INCLUDE_PATH 	= ./includes
LIBFT_PATH 		= ./libft
SRC_PATH 		= ./src/
OBJ_PATH 		= ./obj/

SRCS 			= ft_malloc.c \
					ft_free.c \
					ft_realloc.c \
					buckets.c \
					utils.c \
					show_alloc_mem.c \
					main.c
OBJS 			= $(SRCS:.c=.o)

SRC 			= $(addprefix $(SRC_PATH), $(SRCS))
OBJ 			= $(addprefix $(OBJ_PATH), $(OBJS))
LIBFT 			= $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@ echo "Compiling libft"
	@ make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJ)
	@ echo "Compiling executable"
	@ $(CC) $(CFLAGS) $(OBJ) -L $(LIBFT_PATH) $(LFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ echo "Compiling objects"
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@ echo "Cleaning .o files"
	@ /bin/rm -Rf $(OBJ_PATH)
	@ echo "Cleaning libft"
	@ make clean -sC $(LIBFT_PATH)

fclean: clean
	@ echo "Cleaning $(NAME)"
	@ /bin/rm -f $(NAME)
	@ echo "Fcleaning libft"
	@ make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY : all clean fclean re
