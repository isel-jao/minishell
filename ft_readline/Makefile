NAME = readline

CC = gcc
CFLAGS =  -I includes/ -I ../libft/includes/ 
# CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

AR      = ar rcs

LIBFT = -L ../libft -lft
TERMCAP = -ltermcap  -lncurses

HEADER = readline.h

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR		=	./includes/

SRC =	readline.c 
SRC	+=	terminal_setup.c 
SRC	+=	cursor_motions.c 
SRC	+=	history.c 
SRC	+=	input.c key.c 
SRC	+=	h_list.c 
SRC	+=	history_file.c 

SRCS = $(addprefix srcs/, $(SRC))


OBJS = $(addprefix objs/, $(SRC:c=o))


all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(NAME) --no-print-directory


$(NAME): $(OBJS)
	@make -C ../libft/ --no-print-directory
	$(AR) $(NAME) $? 

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC_DIR)*.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C ../libft/
	@echo "\nRemoving binaries..."
	@rm -rf /objs
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C ../libft/
	@echo "\nDeleting objects..."
	@rm -rf $(OBJ_DIR)
	@echo "\nDeleting redline libray..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	$(CC) main.c $(NAME) -o test $(CFLAGS) $(LIBFT) $(TERMCAP)
	./test

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm
