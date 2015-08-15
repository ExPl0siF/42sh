##
## Makefile for  in /home/casell_t/rendu/Piscine_C_J13
##
## Made by Theo Caselli
## Login   <casell_t@epitech.net>
##
## Started on  Mon Oct 20 08:57:51 2014 Theo Caselli
## Last update Sun May 24 17:19:45 2015 Loic Robin
##

RM			= rm -rf

NAME			= 42sh

CPPFLAGS		+= -Iinclude
CPPFLAGS		+= -D_DEFAULT_SOURCE -D_GNU_SOURCE

CFLAGS			+= -W -Wall -Wextra
CFLAGS			+= -ansi -pedantic

LDFLAGS			+= -Llib
LDLIBS			+= -lmy -lncurses

SRC			= src/minishell/main.c \
			src/minishell/init.c \
			src/minishell/gere_path.c \
			src/minishell/config.c \
			src/minishell/prompt.c \
			src/minishell/lex_cmd.c \
			src/minishell/surlex_cmd.c \
			src/minishell/clean_word.c \
			src/minishell/error_aff.c \
			src/minishell/error.c \
			src/minishell/built_echo.c \
			src/minishell/built.c \
			src/minishell/built2.c \
			src/minishell/cd.c \
			src/minishell/lexem.c \
			src/minishell/gere_sig.c \
			src/minishell/process.c \
			src/minishell/process2.c \
			src/minishell/process_builtin.c \
			src/minishell/get_out.c \
			src/minishell/chev.c \
			src/minishell/set_in.c \
			src/minishell/set_in_fct.c \
			src/minishell/next_operator.c \
			src/minishell/parse_fct.c \
			src/minishell/parse.c \
			src/minishell/pars_list_fct.c \
			src/minishell/load_command_tab.c \
			src/minishell/get_path.c \
			src/minishell/list/destruct_list.c \
			src/minishell/list/env_list.c \
			src/minishell/list/init_show.c \
			src/minishell/list/insert.c \
			src/minishell/list/push_be.c \
			src/history/list.c \
			src/history/get_next_line.c \
			src/history/history.c \
			src/history/find_history.c \
			src/tcaps/tcaps.c \
			src/tcaps/arrow.c \
			src/tcaps/auto.c \
			src/tcaps/print_auto.c \
			src/tcaps/str.c \
			src/tcaps/get_caps.c \
			src/auto/chaines.c \
			src/auto/utils.c \
			src/auto/ls_dir.c \
			src/auto/ls_bin.c \
			src/auto/folder.c \
			src/auto/global.c \
			src/config/parse.c \
			src/config/load.c \
			src/config/is.c \
			src/config/check.c \
			src/config/libmy/my_strinit.c \
			src/config/libmy/my_tablen.c \
			src/config/libmy/my_str_isalnum.c \
			src/config/libmy/my_free_wordtab.c \
			src/config/libmy/list_pushbot.c \
			src/my_strstr.c \
			src/my_strdup.c

OBJ			= $(SRC:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) -c -MMD -o $@ $(CPPFLAGS) $(CFLAGS) $<

clean:
	$(RM) $(OBJ) obj/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
