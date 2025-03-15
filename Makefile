NAME = minishell

LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

MEMORY_ALLOCATOR_SOURCES = memory-allocator/aborter.c memory-allocator/allocator.c
SOURCES = src/execute/execute_utils.c src/builtin/cd.c src/builtin/exit.c src/builtin/export.c src/builtin/export_utils.c \
 src/builtin/env.c src/builtin/pwd.c src/builtin/echo.c src/builtin/builtin.c src/builtin/unset.c src/expander/expander_nonvariables.c \
 src/env/env_utils.c src/lexer/utils.c src/handler.c src/env/env.c\
 src/lexer/lexer.c src/lexer/unquote.c src/lexer/lexer_utils.c src/execute/execute.c \
 src/lexer/lexer_error_message.c src/lexer/is_valid.c src/execute/error_message.c src/execute/fd_utils.c \
 src/parser/parser.c src/parser/parser_state.c src/parser/parser_utils.c src/execute/heredoc.c \
 src/expander/expander.c src/lexer/syntax_analyzer.c src/signal.c $(MEMORY_ALLOCATOR_SOURCES) \
 src/redirections/redirections.c src/env/global_env.c src/utils/unsafe_utils.c src/utils/char_classification.c src/utils/string_utils.c \
 src/utils/quote_classification.c src/expander/expander_2.c

MINISHELL_SOURCES = src/main.c $(SOURCES)
MINISHELL_OBJECTS = $(MINISHELL_SOURCES:.c=.o)

TEST_PATH = tests
TEST_SOURCES = $(wildcard $(TEST_PATH)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(NAME)

$(TEST_PATH):
	@mkdir $(TEST_PATH)

test: $(TEST_PATH) $(NAME)
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)[Tests compiling]$(BLUE_COLOR) : $(PURPLE_COLOR)$<$(NO_COLOR)"
	@$(CC) $(FLAGS) $(SOURCES:.c=.o) $(LIBFT_PATH) $(TEST_SOURCES) -o $(TEST_PATH)/tests -lcriterion -L/usr/local/lib -I/usr/local/include -lreadline
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)Tests running right now. Please wait.\n$(BLUE_COLOR)$(NO_COLOR)"
	@./$(TEST_PATH)/tests ; export TEST_RESULT=$$? ; rm -f __test_file* | exit $$TEST_RESULT 

$(LIBFT_PATH):
	@make bonus -C $(LIBFT_DIR) FLAGS="$(FLAGS)"

$(LIBFT_PATH):
	@make bonus -C $(LIBFT_DIR) FLAGS="$(FLAGS)"

$(NAME): $(LIBFT_PATH) $(MINISHELL_OBJECTS)
	@$(CC) $(FLAGS) -o $(NAME) $(MINISHELL_OBJECTS) $(LIBFT_PATH)
	@sleep 0.2
	@echo "$(CLEAN_CAR)$(GREEN_COLOR)Minishell compiled!$(NO_COLOR)"

%.o: %.c
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)[Minishell compiling]$(BLUE_COLOR) : $(PURPLE_COLOR)$<$(NO_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)All object files removed.$(NO_COLOR)"
	@rm -f $(MINISHELL_OBJECTS)
	@make -C libft clean

fclean:
	@printf "$(CLEAN_CAR)$(GREEN_COLOR)All object and executable files removed.$(NO_COLOR)"
	@rm -f $(MINISHELL_OBJECTS)
	@rm -f $(NAME) $(TEST_PATH)/tests
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re test

NO_COLOR		=	\x1b[0m
GREEN_COLOR		=	\x1b[32;01m
RED_COLOR		=	\x1b[31;01m
PURPLE_COLOR	=	\x1b[35m
BLUE_COLOR		=	\x1b[34;01m
CLEAN_CAR		=	\033[2K\r


OK_STRING		=	$(GREEN_COLOR)[OK]$(NO_COLOR)
ERROR_STRING	=	$(RED_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING		=	$(PURPLE_COLOR)[WARNINGS]$(NO_COLOR)
