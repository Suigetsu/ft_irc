# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:04 by mlagrini          #+#    #+#              #
#    Updated: 2024/02/08 18:09:27 by mlagrini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= ./srcs/main.cpp ./srcs/IRCServer.cpp 
OBJ		= ${SRC:.cpp=.o}
CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98
NAME	= ircserv
RM		= rm -rf

all: ${NAME}

%.o:%.cpp ./srcs/IRCServer.hpp
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re