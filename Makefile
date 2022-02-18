# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hverda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 15:24:39 by hverda            #+#    #+#              #
#    Updated: 2021/12/16 15:55:57 by hverda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = minishell

CORE =	src/ft_add_node_back.c		src/ft_dell_from_list.c		src/ft_get_some_dir.c			src/ft_putstr.c \
		src/ft_strlcpy.c			src/ft_atoi.c				src/ft_env_list_creation.c		src/ft_init_node.c \
		src/ft_split.c				src/ft_strlen.c				src/ft_bash_layer.c				src/ft_export_list_creation.c \
		src/ft_isalpha.c			src/ft_str_comparison.c		src/ft_change_value.c			src/ft_itoa.c \
		src/ft_strdup.c				src/ft_char_inside_str.c	src/ft_free_list.c				src/ft_new_value.c \
		src/ft_strjoin.c			src/ft_substr.c				src/ft_check_key.c				src/ft_isdigit.c \
		src/ft_add_node_back_exe.c 	src/ft_init_node_exe.c		src/ft_free_list_exe.c			src/ft_getcwd.c \
		src/ft_up.c					pipe/ft_free.c				pipe/ft_error.c					pipe/ft_cycle_pipes.c \
		pipe/ft_here_doc.c			pipe/ft_mistake.c			pipe/ft_path.c					pipe/ft_execv_i.c \
		pipe/ft_get_next_line.c		pipe/ft_init.c				pipe/ft_multiple_pipe.c			pipe/ft_execv_commands.c \
		builtins/cd.c				builtins/echo.c				builtins/env.c					builtins/exit.c	\
		builtins/export.c			builtins/ft_update_oldpwd.c	builtins/pwd.c					builtins/unset.c \
		builtins/ft_standard_exit.c	pars/signal.c				pars/dollar.c					pars/dollar_utilite.c \
		pars/redirect_pipe.c		pars/dollar2.c				pars/quote.c					pars/quote_utilite.c \
		pars/quote_utilite2.c		pars/pars.c					pars/dollar2_utilite.c			pars/pars_utilite.c \
		minishell.c					pipe/ft_copy_from_list.c	pars/dollar2_utilite2.c			pars/quote_utilite3.c \

LIST_H = minishell.h

OBJ = $(patsubst %.c,%.o,$(CORE))

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(CORE)  -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -lreadline -o $(NAME)

%.o : %.c Makefile $(LIST_H)
	gcc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
