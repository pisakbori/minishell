CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./structs -I./builtin -I./
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
NAME			= minishell
LIBFT			= libft/libft.a
BLTIN_NAMES		= builtin_exec exit utils export unset env echo cd_utils cd pwd  
BUILTINS		= $(patsubst %, builtin/%, $(BLTIN_NAMES))
FILES			= utils state path_utils free_utils split_utils\
					syntax1 syntax2 syntax3\
					execution execute_utils1 execute_utils2 main env_utils expand\
					str_utils1 str_utils2 str_utils3 state_utils \
					str_arr_utils1 str_arr_utils2 expand_utils error\
					redir redir_utils1 redir_utils2 heredoc heredoc_utils parse\
					signal\
					$(BUILTINS)
SRC				= $(patsubst %, %.c, $(FILES))
OBJS			= $(patsubst %.c, %.o, $(SRC))


all: $(NAME)
	./minishell

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

.PHONY: all clean bonus re fclean