# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/10 15:37:27 by ldavids           #+#    #+#              #
#    Updated: 2021/06/01 14:53:04 by ldavids          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of binary file
NAME = philo_two

# Name of directory
PATH_INC = ../includes/
PATH_SRC = ./
PATH_OBJ = objs/
#PATH_LIBFT = ../libft

# List of sources
SRCS = main.c utils.c utils2.c launch.c display.c actions.c init.c threads.c utils3.c
OBJS = ${addprefix ${PATH_OBJ}, ${SRCS:.c=.o}}
INCS = ${addprefix ${PATH_INC}, header_two.h}

# Commands of compilation
COMP = gcc
COMP_FLAG = -Wall -Wextra -Werror -pthread
COMP_INC = -I ${PATH_INC}

# Others command
RM = /bin/rm

# Color and template code
#YELLOW = \e[38;5;184m
#GREEN = \e[38;5;46m
#RESET = \e[0m
#INFO = [${YELLOW}INFO${RESET}]
#SUCCESS = [${GREEN}OK${RESET}]

# Functions
all :	init ${NAME}
#		@echo "${INFO} Compilation of ${NAME} ${SUCCESS}"

init :
#		@echo "${INFO} Init ${NAME}"
		@${shell mkdir -p ${PATH_OBJ}}
		#@make -C

sub:	init2 ${NAME}

init2 :
#		@echo "${INFO} Init ${NAME}"
		@${shell mkdir -p ${PATH_OBJ}}

${NAME} : ${OBJS} ${INCS}
		@${CC} ${COMP_FLAG} -o ${NAME} ${OBJS}

${PATH_OBJ}%.o : ${PATH_SRC}%.c
		@${COMP} ${COMP_FLAG} ${COMP_INC} -c $< -o $@
		@echo "${INFO} Compilation of $* ${SUCCESS}"

clean :
		@${RM} -rf ${PATH_OBJ}
#		@make -C $(PATH_LIBFT) clean;
		@echo "${INFO} Deleted files and directory"

fclean : clean
		@${RM} -rf ${NAME}
#		@make -C ${PATH_LIBFT} fclean

re : fclean all

.PHONY : all clean fclean re sub
