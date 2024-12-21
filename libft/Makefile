NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = \
	ft_toupper.c ft_tolower.c ft_substr.c  ft_strrchr.c ft_strchr.c ft_strnstr.c ft_putstr_fd.c\
	ft_strlen.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strjoin.c ft_strdup.c ft_split.c ft_putnbr_fd.c\
	ft_memmove.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_itoa.c ft_isprint.c ft_isdigit.c ft_striteri.c ft_putendl_fd.c\
	ft_isalpha.c ft_isalnum.c ft_calloc.c ft_bzero.c ft_atoi.c ft_memset.c ft_isascii.c ft_strmapi.c ft_putstr.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	ar -rc $@  $^

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
