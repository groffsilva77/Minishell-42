#name of the project
NAME = minishell

#compile and flags
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#include (.h)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#were is everyone
LIBFT_DIR = lib/libft
SRCS_DIR = src
<<<<<<< HEAD
MEMORY_DIR = $(SRCS_DIR)/memory
BUILTINS_DIR = $(SRCS_DIR)/builtins
PARSIN_DIR = $(SRCS_DIR)/parsin
EXECUTION_DIR = $(SRCS_DIR)/execution
SIGNAL_DIR = $(SRCS_DIR)/signals 
UTILS_DIR = $(SRCS_DIR)/utils
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/main.c \
		$(willdcard $(MEMORY_DIR)/*.c) \
		$(willdcard $(UTILS_DIR)/*.c) \
		$(willdcard $(BUILTINS_DIR)/.c) \
		$(willdcard $(PARSIN_DIR)/.c) \
		$(willdcard $(EXECUTION_DIR)/.c) \
		$(willdcard $(SIGNAL_DIR)/.c)

#.c to .o
OBJS = $(SRCS:.c=.o)
=======
PARS_DIR = parsing
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/main.c
PARS = $(PARS_DIR)/tokenizer.c \
       $(PARS_DIR)/tokenizer_utils.c \
	   $(PARS_DIR)/var_expansion.c

#.c to .o
OBJS = $(SRCS:.c=.o) $(PARS:.c=.o)
>>>>>>> gabriel

#the library we will use (lft is for libft and lreadline is for readline)
LIBS = -L$(LIBFT_DIR) -lft -lreadline

#rules
all: $(NAME)

$(NAME): make_libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

#compile libft
make_libft:
	make -C $(LIBFT_DIR)

<<<<<<< HEAD
#compile every .c on .o																																																																													
%.o: %.c
=======
#compile every .c on .o
%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#compile parsing files
%.o: $(PARS_DIR)/%.c
>>>>>>> gabriel
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