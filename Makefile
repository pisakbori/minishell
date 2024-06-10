CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./structs
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
NAME			= minishell
LIBFT			= libft/libft.a
FILES			= utils path_utils free_utils ./structs/str_arr execution prompt
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

.PHONY: all clean bonus re fclean