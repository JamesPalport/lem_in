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

SRCFILES = reader.c read_rooms.c read_connec.c routes.c check_map.c bfs.c test.c	\
	  order_routes.c chose_route.c move_ants.c

SRCDIR = src/

SRC = $(addprefix $(SRCDIR), $(SRCFILES))

OBJDIR = ./obj/

OBJ = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

DOT_H = includes/reader.h

FLAG = -g 

INC = -Iincludes/ -ILibft/includes/

LIB = Libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc $(OBJ) $(LIB) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(DOT_H)
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
