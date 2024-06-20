CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./structs -I./builtin -I./
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
NAME			= minishell
LIBFT			= libft/libft.a
BLTIN_NAMES		= builtin_exec exit utils export unset env echo cd_utils cd pwd  
BUILTINS		= $(patsubst %, builtin/%, $(BLTIN_NAMES))
FILES			= utils state path_utils free_utils split_utils syntax_check\
				   execution execute_utils prompt env_utils expand\
				   str_utils1 str_utils2 state_utils \
				   str_arr_utils expand_utils error\
				   redirection redir_utils\
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