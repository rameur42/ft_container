SRCS            = main.cpp

CC              = c++
LIB				= ./include/*.hpp
CFLAGS          = -Wall -Wextra -Werror -I $(dir $(LIB)) -std=c++98
NAME            = ft_container

OBJS            = ${SRCS:.c=.o}

all:            $(NAME)

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS) $(LIB)
					${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f *.o

fclean:		clean
				${RM} ${NAME}

re:             fclean all

.PHONY: all clean fclean re