CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
NAME			= microshell
LIBFT			= libft/libft.a
FILES			= main utils
SRC				=  $(patsubst %, %.c, $(FILES))
OBJS			= $(patsubst %.c, %.o, $(SRC))


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDR_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) $(HDR_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) 


$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

.PHONY: all clean bonus re fclean