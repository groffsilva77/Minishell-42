#name of the project
NAME = minishell

#compile and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#were is everyone
LIBFT_DIR = lib/libft
SRCS_DIR = src
PARS_DIR = parsing
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/main.c
PARS = $(PARS_DIR)/tokenizer.c \
       $(PARS_DIR)/tokenizer_utils.c \
	   $(PARS_DIR)/var_expansion.c \
	   $(PARS_DIR)/validate_syntax.c

#.c to .o
OBJS = $(SRCS:.c=.o) $(PARS:.c=.o)

#the library we will use (lft is for libft and lreadline is for readline)
LIBS = -L$(LIBFT_DIR) -lft -lreadline

#include (.h)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#rules
all: $(NAME)

$(NAME): make_libft $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

#compile libft
make_libft:
	make -C $(LIBFT_DIR)

#compile every .c on .o
%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#compile parsing files
%.o: $(PARS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#is time to clean
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

#re-compile
re: fclean all

# all this rules do not make a file with this names
.PHONY:	all clean fclean re make_libft