CC				= cc
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./structs -I./builtin -I./
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
NAME			= minishell
LIBFT			= libft/libft.a
BLTIN_NAMES		= builtin_exec builtin_u exit export export_u unset env echo cd pwd
BUILTINS		= $(patsubst %, builtin/%, $(BLTIN_NAMES))
FILES			=   main state execution signal parse\
					path_utils free_utils split_utils\
					syntax_redirs syntax_quotes syntax_pipes\
					execute_utils1 execute_utils2 env_utils state_utils\
					str_utils1 str_utils2 str_utils3 str_arr_utils1\
					expand expand_utils error\
					heredoc heredoc_utils\
					redirection redir_utils2 redir_utils1\
					malloc_safe_u\
					$(BUILTINS)
SRC				= $(patsubst %, %.c, $(FILES))
OBJS			= $(patsubst %.c, %.o, $(SRC))


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDR_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(HDR_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LFLAGS)


$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean re fclean