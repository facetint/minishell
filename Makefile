
# Path to the libft.a archive
NAME = minishell
LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
MEMORY_ALLOCATOR_SOURCES = memory-allocator/aborter.c memory-allocator/allocator.c
SOURCES = main.c utils.c lexer.c unquote.c lexer_utils.c parser.c expander.c splitter.c syntax_analyzer.c $(MEMORY_ALLOCATOR_SOURCES)
FLAGS = -Wall -Wextra -Werror -g
OBJECTS = $(SOURCES:.c=.o)

all: minishell

$(LIBFT_PATH):
	make -C $(LIBFT_DIR)

minishell: $(LIBFT_PATH) $(OBJECTS)
	gcc $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_PATH) -L/usr/local/lib -I/usr/local/include -lreadline

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
