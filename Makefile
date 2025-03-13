#name of the project
NAME = minishell

#compile and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

#include (.h)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

#were is everyone
LIBFT_DIR = lib/libft
SRCS_DIR = src

MEMORY_DIR = $(SRCS_DIR)/memory
BUILTINS_DIR = $(SRCS_DIR)/builtins
PARSING_DIR = $(SRCS_DIR)/parsing
EXECUTION_DIR = $(SRCS_DIR)/execution
UTILS_DIR = $(SRCS_DIR)/utils
INCLUDE_DIR = include

#the .c (.c is here)
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/main_utils.c \
	   $(SRCS_DIR)/main_utils_2.c \
	   $(SRCS_DIR)/signals.c \
	   $(MEMORY_DIR)/free_commands.c \
	   $(MEMORY_DIR)/free_tokens.c \
	   $(MEMORY_DIR)/ft_free_array.c \
	   $(MEMORY_DIR)/ft_free.c \
	   $(MEMORY_DIR)/fts_malloc.c \
	   $(UTILS_DIR)/ft_realloc_array.c \
	   $(UTILS_DIR)/ft_strcat.c \
	   $(UTILS_DIR)/ft_strcpy.c \
	   $(UTILS_DIR)/fts_strdup.c \
	   $(UTILS_DIR)/fts_strjoin.c \
	   $(UTILS_DIR)/fts_strtrim.c \
	   $(BUILTINS_DIR)/cd.c \
	   $(BUILTINS_DIR)/echo.c \
	   $(BUILTINS_DIR)/env.c \
	   $(BUILTINS_DIR)/exit.c \
	   $(BUILTINS_DIR)/export.c \
	   $(BUILTINS_DIR)/pwd.c \
	   $(BUILTINS_DIR)/unset.c \
	   $(PARSING_DIR)/parser.c \
	   $(PARSING_DIR)/parser_utils.c \
	   $(PARSING_DIR)/tokenizer.c \
	   $(PARSING_DIR)/tokenizer_utils.c \
	   $(PARSING_DIR)/tokenizer_utils_2.c \
	   $(PARSING_DIR)/tokenizer_utils_3.c \
	   $(PARSING_DIR)/var_expansion.c \
	   $(PARSING_DIR)/var_expansion_utils.c \
	   $(PARSING_DIR)/validate_syntax.c \
	   $(EXECUTION_DIR)/exec_builtin.c \
	   $(EXECUTION_DIR)/exec.c \
	   $(EXECUTION_DIR)/find_path.c \
	   $(EXECUTION_DIR)/pipe_utils.c \
	   $(EXECUTION_DIR)/pipe.c \
	   $(EXECUTION_DIR)/redirect.c \
	   $(EXECUTION_DIR)/heredoc.c \

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