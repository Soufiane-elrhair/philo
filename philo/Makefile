# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 15:34:29 by selrhair          #+#    #+#              #
#    Updated: 2023/05/22 17:39:11 by selrhair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc 
HEADER	= -I./inc
CFLAGS	=  -Wall -Wextra -Werror -pthread $(HEADER) #-fsanitize=address -g3
RM		= rm -rf

# colors
NONE	= \033[0m
YALLOW	= \033[1;93m
Green	= \033[1;32m

# src files
SRC		= ft_atoi.c philosophere.c get_time_ms.c ft_usleep.c utils.c


SRCS	= $(addprefix ./src/, $(SRC)) main.c 

# obj files
OBJS	= $(SRCS:.c=.o)

all : $(NAME)

%.o:%.c
	@echo "$(Green)Compaling file $<$(NONE)"
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS) $(LIBFT)
	@echo  "$(YALLOW)\n[$@]$(NONE)"
	$(CC) $(CFLAGS) $(OBJS) -o $@ 
	
clean :
	@echo "$(Green)Cleaning obj files....$(NONE)"
	$(RM) $(OBJS)
	
fclean : clean
	@echo "$(Green)Clean all ....$(NONE)"
	$(RM) $(NAME) 
	
re: fclean all