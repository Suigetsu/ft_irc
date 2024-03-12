# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlagrini <mlagrini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 10:37:04 by mlagrini          #+#    #+#              #
#    Updated: 2024/03/11 12:43:34 by mlagrini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/commands/Command.cpp \
			srcs/User.cpp srcs/commands/Pass.cpp srcs/commands/Nick.cpp \
			srcs/commands/Quit.cpp srcs/commands/UserCmd.cpp srcs/commands/Ping.cpp \
			srcs/commands/Pong.cpp srcs/commands/Join.cpp srcs/Channel.cpp srcs/commands/Mode.cpp
OBJ		=	${SRC:.cpp=.o}
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98
NAME	=	ircserv
RM		=	rm -rf

all: ${NAME}

%.o:%.cpp srcs/includes/Server.hpp
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re