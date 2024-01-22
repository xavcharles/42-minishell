SRC = Source/main.c \
		Source/minishell.c \
		Source/execution.c \
		Source/parse_utils.c \
		Source/pwd.c \
		Source/parse_utils2.c \
		Source/parse_utils3.c \
		Source/sep_check.c \
		Source/redirections.c \
		Source/pipe.c \
		Source/init_cmd.c \
		Source/init_cmd_utils.c \
		Source/init_cmd_utils2.c \
		Source/set_op.c \
		Source/env.c \
		Source/echo.c \
		Source/changedir.c \
		Source/clean.c \
		Source/input_check.c \
		Source/ic_signal.c \
		Source/ft_exit.c \
		Source/exec_utils.c \
		Source/par_builtins.c \
		Source/dollar.c \
		Source/dollar_utils.c \
		Source/dollar_utils2.c \
		Source/dollar_utils3.c \
		Source/dollar_utils4.c \
		Source/input_check2.c \
		Source/builtin_utils.c \
		Source/here_doc.c \
		Source/ft_history.c \
		
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
