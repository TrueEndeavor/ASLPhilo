# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 15:24:15 by lannur-s          #+#    #+#              #
#    Updated: 2024/04/12 21:09:03 by lannur-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
LIBFTNAME = libft.a

CC = cc
CCFLAGS = -Wall -Werror -Wextra -I./include

AR = ar
ARFLAGS = -rcs

INCLUDES = -I./include

SRCS =	src/main.c \
		src/parsing.c \
		src/initialization.c \
		src/philo_actions.c \
		src/philo_routine.c \
		src/feast_actions.c \
		src/bruce_almighty.c \
		src/destruction.c \
		src/utils.c

OBJS = $(SRCS:%.c=%.o)

${NAME}: ${OBJS}
	cc ${CFLAGS} -o ${NAME} ${OBJS}

%.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@
	
all : ${NAME}

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f ${NAME}

re: fclean
	make

.PHONY: all clean fclean re
