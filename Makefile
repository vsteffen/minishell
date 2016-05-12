# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/03 17:41:16 by vsteffen          #+#    #+#              #
#    Updated: 2016/05/12 17:16:57 by vsteffen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC =	/usr/bin/clang
RM =	/bin/rm
MAKE =	/usr/bin/make
MKDIR =	/bin/mkdir
AR =	/usr/bin/ar
RANLIB = /usr/bin/ranlib

LIBS = -framework OpenGL \
	   -framework AppKit \
	   $(ROOT)/libft/libft.a

SRC = maintest.c

# OBJ_NAME = $(wildcard $(ROOT)/srcs/$(SRC))

OBJ = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

CFLAGS = -I $(HPATH) -Wall -Wextra -Werror -I $(HPATH)

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/objs
CPATH =		$(ROOT)/srcs
HPATH =		$(ROOT)/include

showStartRule=\t\033[31m\033[4m\033[1m → Starting \"make $(MAKECMDGOALS)\" rule\033[0m
showEndRule=\t\033[31m\033[4m\033[1mEnd of \"make $(MAKECMDGOALS)\" rule\033[0m


.PHONY: all clean fclean re

all: $(OPATH) libft-make $(NAME)

libclean: fclean
	@echo "$(showStartRule) for libraries"
	@$(MAKE) -C miniLibX clean
	@$(MAKE) -C libft fclean
	@echo "\033[32mPersonal libraries clean.\033[0m"
	@echo "$(showEndRule) for libraries"

libft-make:
	@echo "$(showStartRule) for libft"
	@$(MAKE) -C libft
	@echo "$(showEndRule) for libft"

libft-clean:
	@echo "$(showStartRule) for libft"
	@$(MAKE) -C libft clean
	@echo "$(showEndRule) for libft"

libft-fclean:
	@echo "$(showStartRule) for libft"
	@$(MAKE) -C libft fclean
	@echo "$(showEndRule) for libft"

libft-re:
	@echo "$(showStartRule) for libft"
	@$(MAKE) -C libft re
	@echo "$(showEndRule) for libft"


$(NAME): $(OBJ)
	@echo " \033[33m\033[4m\033[1m → Make rule \033[0m"
	@echo "Creating OBJ files if they do not exist"
	@echo "Building $@"
	@$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBS)
	@echo "\033[32m ╔════════════════╗"
	@echo " ║  All is done ! ║"
	@echo " ╚════════════════╝\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@echo " \033[33m\033[4m\033[1m → Pre Make rule \033[0m"
	@echo "Creating "objs" directory."
	$(MKDIR) $@
	@echo "\033[32mOBJS directory created.\033[0m\n"

clean:
	@echo " \033[33m\033[4m\033[1m → Clean rule \033[0m"
	@echo "Deleting OBJS."
	$(RM) -Rf $(OPATH)
	@echo "\033[32mOBJS deleted.\033[0m\n"

fclean: clean
	@echo " \033[33m\033[4m\033[1m → Fclean rule \033[0m"
	@echo "Deleting $(NAME)."
	$(RM) -f $(NAME)
	@echo "\033[32m$(NAME) deleted.\033[0m\n"

re: fclean all
