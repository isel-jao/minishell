NAME = minishell

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/
CFLAGS = -I includes/ -I libft/includes/ -I ft_readline/includes/

HEADER = minishell.h



SRCS_DIR	=	./srcs/
OBJ_DIR		=	./objs/
INC_DIR		=	./includes/


SRC = bin.c 
SRC += builtin.c 
SRC += cd.c 
SRC += cd_tools.c 
SRC += echo.c 
SRC += env.c 
SRC += exec.c 
SRC += exit.c 
SRC += expansions.c 
SRC += export.c 
SRC += fd.c 
SRC += get_env.c 
SRC += minishell.c 
SRC += parse.c 
SRC += quotes.c 
SRC += pwd.c 
SRC += redir.c 
SRC += token.c 
SRC += tokens.c 
SRC += tools1.c 
SRC += type.c 
SRC += unset.c 
SRC += signals.c 
SRC += sort_args.c 


OBJ			=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))

INC			=	$(addprefix -I,$(INC_DIR))

LIBFT		=	./libft/libft.a
TERMCAP =	ft_readline/readline -ltermcap  -lncurses

RM			=	/bin/rm -f
RM_DIR		=	/bin/rm -rf

$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(INC_DIR)*.h
	$(CC)  $(CFLAGS) -c $< -o $@


all:
	@mkdir -p $(OBJ_DIR)
	$(MAKE) $(NAME) --no-print-directory

make_libft:
	@make -C libft/
make_readline:
	@make -C ft_readline/

$(NAME): $(OBJ) $(INC_DIR) make_libft make_readline
	@$(CC)  $(OBJ) $(LIBFT) $(TERMCAP) -o $(NAME)

clean:
	@$(RM_DIR) $(OBJ_DIR)
	@$(MAKE) clean -C ft_readline --no-print-directory
	@$(MAKE) clean -C libft/ --no-print-directory

fclean: clean
	@make fclean -C libft/ --no-print-directory
	@make fclean -C ft_readline --no-print-directory
	@rm -f $(NAME)

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)