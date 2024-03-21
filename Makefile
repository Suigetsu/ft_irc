SRC		=	srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/commands/Command.cpp \
			srcs/User.cpp srcs/commands/Pass.cpp srcs/commands/Nick.cpp \
			srcs/commands/Quit.cpp srcs/commands/UserCmd.cpp srcs/commands/Ping.cpp \
			srcs/commands/Pong.cpp srcs/commands/Join.cpp srcs/Channel.cpp srcs/commands/Mode.cpp \
			srcs/commands/Topic.cpp srcs/commands/Who.cpp srcs/commands/WhoIs.cpp srcs/commands/Motd.cpp \
			srcs/commands/Privmsg.cpp srcs/commands/Invite.cpp srcs/commands/Part.cpp srcs/commands/Kick.cpp
OBJ		=	${SRC:.cpp=.o}
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
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