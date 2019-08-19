# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amerrouc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/09 15:04:16 by amerrouc          #+#    #+#              #
#    Updated: 2019/07/03 08:38:57 by amerrouc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRC = reader.c read_rooms.c read_connec.c routes.c check_map.c bfs.c test.c	\
	  order_routes.c chose_route.c move_ants.c

OBJ = $(SRC:.c=.o)

FLAG = 

INC = -Iincludes/ -ILibft/includes

LIB = Libft/libft.a

DOT_H = ./includes/filler.h

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(FLAG) $(INC) -o $@ -c $<

$(LIB):
	make -C ./libft/

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
