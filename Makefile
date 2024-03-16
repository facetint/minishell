NAME = minishell

LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a

CC = gcc
FLAGS = -g -Wall -Wextra -Werror -fsanitize=address

MEMORY_ALLOCATOR_SOURCES = memory-allocator/aborter.c memory-allocator/allocator.c
SOURCES = src/execute/execute_utils.c src/builtin/cd.c src/builtin/exit.c src/builtin/export.c src/builtin/echo.c \
 src/builtin/env.c src/builtin/pwd.c  src/builtin/builtin.c get_next_line/get_next_line.c \
 src/expander/expander_nonvariables.c src/env/env_utils.c src/lexer/utils.c src/handler.c src/env/env.c\
 src/lexer/lexer.c src/lexer/unquote.c src/lexer/lexer_utils.c src/parser.c src/execute/execute.c \
 src/execute/redirections.c src/expander/expander.c src/splitter.c src/lexer/syntax_analyzer.c src/signal.c $(MEMORY_ALLOCATOR_SOURCES)

MINISHELL_SOURCES = src/main.c $(SOURCES)
MINISHELL_OBJECTS = $(MINISHELL_SOURCES:.c=.o)

TEST_PATH = tests
TEST_SOURCES = $(wildcard $(TEST_PATH)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(NAME)

$(TEST_PATH):
	@mkdir $(TEST_PATH)

test: $(TEST_PATH) $(NAME)
	$(CC) $(SOURCES:.c=.o) $(LIBFT_PATH) $(TEST_SOURCES) -o $(TEST_PATH)/tests -lcriterion -L/usr/local/lib -I/usr/local/include -lreadline
	./$(TEST_PATH)/tests

$(LIBFT_PATH):
	@make bonus -C $(LIBFT_DIR)

$(NAME): $(LIBFT_PATH) $(MINISHELL_OBJECTS)
	@$(CC) $(FLAGS) -o $(NAME) $(MINISHELL_OBJECTS) $(LIBFT_PATH) -L/usr/local/lib -I/usr/local/include -lreadline
	@sleep 0.2
	@echo "$(CLEAN_CAR)$(GREEN_COLOR)Minishell Compiled!$(NO_COLOR)"

%.o: %.c
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)[minishell Compiling]$(BLUE_COLOR) : $(PURPLE_COLOR)$<$(NO_COLOR)\n"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(MINISHELL_OBJECTS)
	make -f libft/Makefile clean

fclean: clean
	rm -f $(NAME) $(TEST_PATH)/tests $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re

NO_COLOR		=	\x1b[0m
GREEN_COLOR		=	\x1b[32;01m
RED_COLOR		=	\x1b[31;01m
PURPLE_COLOR	=	\x1b[35m
BLUE_COLOR		=	\x1b[34;01m
CLEAN_CAR		=	\033[2K\r


OK_STRING		=	$(GREEN_COLOR)[OK]$(NO_COLOR)
ERROR_STRING	=	$(RED_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING		=	$(PURPLE_COLOR)[WARNINGS]$(NO_COLOR)
