NAME = minishell

CC = cc

CFLAG = -Wall -Wextra -Werror -g3

LINKFLAG = -lreadline -L/usr/include

SRCS =	parsing/minishell.c\
		parsing/get_path.c\
		parsing/parsing_minishell.c\
		parsing/struct_utils.c\
		parsing/get_type_enum.c\
		parsing/remove_things.c\
		parsing/get_node.c\
		parsing/clean_list.c\
		parsing/add_pipe.c\
		parsing/check_quote_file.c\
		parsing/fill_var_node.c\
		parsing/fill_quote_node.c\
		parsing/strange_cmd.c\
		exec/exec_start.c\
		exec/t_exec_continue.c\
		exec/t_apply_exec.c\
		exec/change_std.c\
		exec/utils_exec.c\
		exec/t_exec_utils.c\
		exec/print_return_value.c\
		exec/t_stdin_out_gestion.c \
		exec/builtins/is_builtin.c\
		exec/builtins/ft_export.c\
		exec/builtins/cd/ft_cd.c\
		exec/builtins/cd/cd_utils.c\
		exec/builtins/cd/cd_oldpwd_utils.c\
		exec/builtins/ft_pwd.c\
		exec/builtins/echo/ft_echo.c\
		exec/builtins/echo/echo_utils.c\
		exec/builtins/ft_exit.c\
		exec/builtins/ft_env.c\
		exec/builtins/ft_unset.c\
		exec/special_env_var.c\
		utils/error_message.c\
		utils/free_tab.c\
		utils/free_all.c\
		utils/exit_fonctions.c\
		utils/t_struct_utils.c\
		utils/swap_lst_char.c\
		utils/ft_lstcpy.c\
		signals/signals.c\
		signals/signals_here_doc.c\
		here_doc/here_doc.c\

INCLUDE = minishell.h

OBJS = $(SRCS:%.c=$(PATH_OBJS)%.o)

LIBFT_A = libft/libft.a
LIBFT_H = libft/libft.h

PATH_SRCS = src/

PATH_INCLUDE = include/

PATH_OBJS = obj/

PATH_LIBFT = libft/

# ------------------------------------make----------------------------------

all: $(NAME)

$(NAME) : $(PATH_OBJS) $(OBJS) $(PATH_INCLUDE)$(INCLUDE) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME) $(LINKFLAG)


$(OBJS)	: $(PATH_OBJS)%.o: $(PATH_SRCS)%.c $(PATH_INCLUDE)$(INCLUDE) $(LIBFT_H)
				$(CC) $(CFLAG) -I$(PATH_INCLUDE) -I$(PATH_LIBFT) -c $< -o $@

# ----------------------------------utils------------------------------------

$(PATH_OBJS) :
				mkdir -p $(PATH_OBJS)
				mkdir -p $(PATH_OBJS)/parsing
				mkdir -p $(PATH_OBJS)/exec
				mkdir -p $(PATH_OBJS)/exec/builtins
				mkdir -p $(PATH_OBJS)/exec/builtins/cd
				mkdir -p $(PATH_OBJS)/exec/builtins/echo
				mkdir -p $(PATH_OBJS)/utils
				mkdir -p $(PATH_OBJS)/signals
				mkdir -p $(PATH_OBJS)/here_doc

# $(PATH_OBJS_BONUS) :
# 				mkdir -p $(PATH_OBJS_BONUS) 

$(LIBFT_A)	:	FORCE
				make all -C $(PATH_LIBFT)


# --------------------------------Removing readline leaks---------------------

leaks            :    all
				echo "{" > valgrind_ignore_leaks.txt
				echo "leak readline" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:readline" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				echo "{" >> valgrind_ignore_leaks.txt
				echo "    leak add_history" >> valgrind_ignore_leaks.txt
				echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
				echo "    ..." >> valgrind_ignore_leaks.txt
				echo "    fun:add_history" >> valgrind_ignore_leaks.txt
				echo "}" >> valgrind_ignore_leaks.txt
				valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
					--show-leak-kinds=all --track-fds=yes \
					--show-mismatched-frees=yes --read-var-info=yes \
					-s ./${NAME}
					#--log-file=valgrind.txt \

envleaks            :    all
				env -i valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
					--show-leak-kinds=all --track-fds=yes \
					--show-mismatched-frees=yes --read-var-info=yes \
					-s ./${NAME}

# ----------------------------------commands---------------------------------

clean:
	rm -rf ${OBJS} $(PATH_OBJS)
	rm -rf valgrind_ignore_leaks.txt
	@make clean -C $(PATH_LIBFT)

fclean: clean
	rm -rf $(NAME)
	rm -rf valgrind_ignore_leaks.txt
	@make fclean -C $(PATH_LIBFT)

re: fclean all

FORCE: 

.PHONY: all re bonus clean fclean