NAME = libft.a

OBJECTS = ft_isalpha.o \
			ft_memchr.o \
			ft_putchar_fd.o \
			ft_strchr.o \
			ft_strlcpy.o \
			ft_strrchr.o \
			ft_atoi.o \
			ft_isascii.o \
			ft_memcmp.o \
			ft_putendl_fd.o \
			ft_strdup.o \
			ft_strlen.o \
			ft_strtrim.o \
			ft_bzero.o \
			ft_isdigit.o \
			ft_memcpy.o \
			ft_putnbr_fd.o \
			ft_striteri.o \
			ft_strmapi.o \
			ft_substr.o \
			ft_calloc.o \
			ft_isprint.o \
			ft_memmove.o \
			ft_putstr_fd.o \
			ft_strjoin.o \
			ft_strncmp.o \
			ft_tolower.o \
			ft_isalnum.o \
			ft_itoa.o \
			ft_memset.o \
			ft_split.o \
			ft_strlcat.o \
			ft_strnstr.o \
			ft_toupper.o \
			get_next_line.o \
			get_next_line_utils.o \
			ft_printf.o \
			ft_putnbrbase_p.o \
			ft_cptputstr.o \

INCLUDES = .libft.h

BONUS = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

%.o: %.c
	gcc -c -Wall -Wextra -Werror -g3 -I$(INCLUDES) $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)
	 
bonus: $(NAME) $(BONUS)
	ar -rcs $(NAME) $(BONUS)

#so:
#	gcc -nostartfiles -shared -o libft.so $(OBJECTS) $(BONUS)

clean: 
	rm -f $(OBJECTS) $(BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
