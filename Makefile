NAME = minishell

LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
MEMORY_ALLOCATOR_SOURCES = memory-allocator/aborter.c memory-allocator/allocator.c
SOURCES = execute/find_path.c builtin/echo.c builtin/builtin.c get_next_line/get_next_line.c expander/expander_nonvariables.c env/env_utils.c utils.c handler.c env/env.c lexer.c unquote.c lexer_utils.c parser.c execute/execute.c expander/expander.c splitter.c syntax_analyzer.c $(MEMORY_ALLOCATOR_SOURCES)

MINISHELL_SOURCES = main.c $(SOURCES)
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
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_PATH) $(MINISHELL_OBJECTS)
	@$(CC) $(FLAGS) -o $(NAME) $(MINISHELL_OBJECTS) $(LIBFT_PATH) -L/usr/local/lib -I/usr/local/include -lreadline
	@sleep 0.2
	@echo "$(CLEAN_CAR)$(GREEN_COLOR)Minishell Compiled!$(NO_COLOR)"

%.o: %.c
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)[minishell Compiling]$(BLUE_COLOR) : $(PURPLE_COLOR)$<$(NO_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@

	
clean:
	rm -f $(MINISHELL_OBJECTS)
<<<<<<< Updated upstream

fclean: clean
	rm -f $(NAME) $(TEST_PATH)/tests
=======
	make -fclean -C libft/Makefile
	@echo "$(RED_COLOR)Dependencies and objects removed$(NO_COLOR)"


fclean: clean
	rm -f $(NAME) $(TEST_PATH)/tests $(LIBFT_PATH)
	@echo "$(RED_COLOR)$(NAME) removed$(NO_COLOR)"

>>>>>>> Stashed changes

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
