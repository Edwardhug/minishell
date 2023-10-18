
.PHONY:     			all clear mkbuild lib clean fclean re

NAME					= minishell

BUILD_DIR				= build/
	
HEADER_DIR				= include/
HEADER_FILE				= minishell.h
HEADERS_WITH_PATH		= $(addprefix $(HEADER_DIR),$(HEADER_FILE))

DIR						= src/

SRC =	parsing/minishell.c\
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
		exec/special_env_var.c\
		exec/builtins/is_builtin.c\
		exec/builtins/ft_export.c\
		exec/builtins/ft_cd.c\
		exec/builtins/cd_utils.c\
		exec/builtins/ft_pwd.c\
		exec/builtins/ft_echo.c\
		exec/builtins/ft_exit.c\
		exec/builtins/ft_env.c\
		exec/builtins/ft_unset.c\
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


OBJECTS			    	= ${addprefix ${BUILD_DIR},${SRC:.c=.o}}

LIBFT					= libft.a
LIB_DIR					= libft/
	
GCC						= cc
CFLAGS					= -Wall -Wextra -Werror -g3

RM 						= rm -rf
CLEAR					= clear

LINKFLAG = -lreadline -L/usr/include

$(BUILD_DIR)%.o:		$(DIR)%.c ${HEADERS_WITH_PATH} Makefile
						mkdir -p $(@D)
						$(GCC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@


all: 					mkbuild  $(HEADER_DIR)
						$(MAKE) lib
						$(MAKE) $(NAME)

mkbuild:
						mkdir -p build

clear:
						$(CLEAR)

$(NAME): 				$(OBJECTS) lib $(LIB_DIR)$(LIBFT)
						$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) $(LINKFLAG)

lib:
						make FLAGS="-Wall -Wextra -Werror -g3" -C $(LIB_DIR)
						
clean:					
						${RM} $(OBJECTS)
						make clean -C $(LIB_DIR)
						${RM} $(BUILD_DIR)

fclean:					clean
						${RM} ${NAME}
						make fclean -C $(LIB_DIR)

re:						fclean
						$(MAKE) all