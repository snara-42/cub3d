# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/02 13:59:38 by snara             #+#    #+#              #
#    Updated: 2020/12/15 16:12:48 by snara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_bzero.c ft_memcmp.c ft_memchr.c \
ft_isascii.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isprint.c ft_tolower.c ft_toupper.c \
ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strlen.c \
ft_calloc.c ft_atoi.c ft_itoa.c \
ft_strmapi.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_strdup.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_swap.c \
ft_lstadd_back.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstsize.c \
ft_lstadd_front.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c

OBJS = ${SRCS:.c=.o}
B_SRCS =
B_OBJS = ${B_SRCS:%.c=%.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
AR = ar rc

all:	$(NAME)

$(NAME):	$(OBJS)  ${B_OBJS}
		${AR} ${NAME} ${OBJS} ${B_OBJS}

.c.o:
		${CC} ${CFLAGS} -c $< -o $@ 

clean:
		rm -f ${OBJS} ${B_OBJS}

fclean: clean
		rm -f ${NAME}

tclean: 
		rm -f ${T_SRCS} ${T_RES} a.out

re: fclean all


noodle:
	@clear
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo "	              (    )    ("
	@echo ""
	@echo ""
	@echo "                        =(=)=(===================="
	@echo "                        ==)=(=)==================="
	@echo "               ___...----())))(---....___"
	@echo '         ..-""         ) (((( )          ""-..'
	@echo "        |-._         ( ( (  ( ( (          _.-|"
	@echo '        |   `""----.................----""`   |'
	@echo "        |                                     |"
	@echo "        |                                     |"
	@echo "         \                                   /"
	@echo "          \                                 /"
	@echo "           \                               /"
	@echo "            \                             /"
	@echo "             \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._               '"--...___...--"'              _.'"
	@echo '   \""--..__                             __..--"" /'
	@echo "     '._     """----.....______.....----"""          _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "	              (    )    ("
	@echo ""
	@echo "                        =(=)=(===================="
	@echo "                        ==)=(=)==================="
	@echo "                         ())))("
	@echo "                         )(((()"
	@echo "                         ())))("
	@echo "                         )(((()"
	@echo "               ___...----())))(---....___"
	@echo '         ..-""         ) (((( )          ""-..'
	@echo "        |-._         ( ( (  ( ( (          _.-|"
	@echo '        |   `""----.................----""`   |'
	@echo "        |                                     |"
	@echo "        |                                     |"
	@echo "         \                                   /"
	@echo "          \                                 /"
	@echo "           \                               /"
	@echo "            \                             /"
	@echo "             \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._               '"--...___...--"'              _.'"
	@echo '   \""--..__                             __..--"" /'
	@echo "     '._     """----.....______.....----"""          _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5


.PHONY: all clean fclean tclean re bonus test noodle
