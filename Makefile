# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldavids <ldavids@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 15:10:45 by ldavids           #+#    #+#              #
#    Updated: 2021/05/28 19:03:14 by ldavids          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C philo_one_src
	make -C philo_two_src
	make -C philo_three_src

philo_one:
	make -C philo_one_src

philo_two:
	make -C philo_two_src

philo_three:
	make -C  philo_three_src

clean:
	make -C philo_one_src clean
	make -C philo_two_src clean
	make -C philo_three_src clean

fclean:
	make -C philo_one_src fclean
	make -C philo_two_src fclean
	make -C philo_three_src fclean

re: fclean all

.PHONY: all clean fclean re checker philo_one philo_two philo_three
