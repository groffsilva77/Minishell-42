#name of the project
NAME = minishell

#compile and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#include (.h)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#were is everyone
LIBFT_DIR = lib/libft
SRCS_DIR = src

MEMORY_DIR = $(SRCS_DIR)/memory
BUILTINS_DIR = $(SRCS_DIR)/builtins
PARSING_DIR = $(SRCS_DIR)/parsing
TOKEN_DIR = $(SRCS_DIR)/token
EXECUTION_DIR = $(SRCS_DIR)/execution
SIGNAL_DIR = $(SRCS_DIR)/signals 
UTILS_DIR = $(SRCS_DIR)/utils
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/main_utils.c \
	   $(SRCS_DIR)/signals.c \
	   $(wildcard $(MEMORY_DIR)/*.c) \
	   $(wildcard $(UTILS_DIR)/*.c) \
	   $(wildcard $(BUILTINS_DIR)/*.c) \
	   $(wildcard $(PARSING_DIR)/*.c) \
	   $(wildcard $(TOKEN_DIR)/*.c) \
	   $(wildcard $(EXECUTION_DIR)/*.c)

#.c to .o
OBJS = $(SRCS:.c=.o)

#the library we will use (lft is for libft and lreadline is for readline)
LIBS = -L$(LIBFT_DIR) -lft -lreadline

#rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

#compile libft
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

#compile every .c on .o
%.o: %.c
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