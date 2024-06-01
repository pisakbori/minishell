CC      = cc
CFLAGS	= -Wall -Werror -Wextra
RM      = rm -rf
NAME	= libft.a
SRC		= ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isalpha.c ft_isdigit.c\
		ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
		 ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_strchr.c ft_strrchr.c ft_strlcat.c ft_split.c\
		ft_toupper.c ft_tolower.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
		ft_strnstr.c ft_calloc.c ft_strdup.c ft_strmapi.c ft_striteri.c\
		ft_atoi.c ft_itoa.c ft_putnbr_fd.c ft_strlcpy.c\
		get_next_line.c get_next_line_utils.c ft_free.c\
		ft_csprint.c print_reverse.c ft_dxprint.c ft_printf.c ft_ulprint.c\
		ft_arr_len.c
B_SRC	= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
		ft_lstmap_bonus.c 

OBJS	= $(SRC:.c=.o)

B_OBJS	= $(B_SRC:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(B_OBJS)
	ar -rcs $(NAME) $(OBJS) $(B_OBJS)

clean:
	rm -rf $(OBJS) $(B_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean bonus re fclean
