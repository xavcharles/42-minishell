SRC = Source/pipe.c Source/redirections.c Source/main.c Source/minishell.c Source/execution.c 

NAME = minishell

OBJ = $(SRC:.c=.o)

INC = ./Include

LIB_D =  ./libft

LIB = $(LIB_D)/libft.a

FLAG = -Werror -Wall -Wextra -g3

CC = cc 

all : $(NAME) 

$(NAME) : $(OBJ) | $(LIB) 
	$(CC) $(FLAG) $(OBJ) -L$(LIB_D) -lreadline -l ft -o $(NAME)
	
%.o : %.c
	$(CC) $(FLAG) -I$(INC) -c $< -o $@

$(LIB) :
	@make -C $(LIB_D) 

clean :
	rm -f $(OBJ)
	@make -C libft clean

fclean:
	rm -f $(OBJ) $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY: all clean fclean re
