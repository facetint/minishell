NAME = minishell

LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

MEMORY_ALLOCATOR_SOURCES = memory-allocator/aborter.c memory-allocator/allocator.c
SOURCES = expander/expander_nonvariables.c utils.c handler.c lexer.c unquote.c lexer_utils.c parser.c execute.c expander.c splitter.c syntax_analyzer.c $(MEMORY_ALLOCATOR_SOURCES)

MINISHELL_SOURCES = main.c $(SOURCES)
MINISHELL_OBJECTS = $(MINISHELL_SOURCES:.c=.o)

TEST_PATH = tests
TEST_SOURCES = $(wildcard $(TEST_PATH)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(NAME)

$(TEST_PATH):
	mkdir $(TEST_PATH)

test: $(TEST_PATH) $(NAME)
	$(CC) $(SOURCES:.c=.o) $(LIBFT_PATH) $(TEST_SOURCES) -o $(TEST_PATH)/tests -lcriterion -L/usr/local/lib -I/usr/local/include -lreadline
	./$(TEST_PATH)/tests

$(LIBFT_PATH):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_PATH) $(MINISHELL_OBJECTS)
	$(CC) $(FLAGS) -o $(NAME) $(MINISHELL_OBJECTS) $(LIBFT_PATH) -L/usr/local/lib -I/usr/local/include -lreadline

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(MINISHELL_OBJECTS)

fclean: clean
	rm -f $(NAME) $(TEST_PATH)/tests

re: fclean all
