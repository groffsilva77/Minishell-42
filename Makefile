#name of the project
NAME = minishell

#compile and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

#were is everyone
LIBFT_DIR = lib
SRCS_DIR = src
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/ main.c \

#.c to .o
OBJS = $(SRCS:.c=.o)

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
%.o: $(SRCS_DIR)/%.C
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