
# Path to the libft.a archive
NAME = minishell_demo
LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
SOURCES = test.c utils.c parser.c char_classification.c lexer.c expander.c syntax_analyzer.c
OBJECTS = $(SOURCES:.c=.o)

# Target rule
all: test

# Add a target to build libft.a
$(LIBFT_PATH):
	make -C $(LIBFT_DIR)

# Rule to build the program
test: $(LIBFT_PATH) $(OBJECTS)
	gcc -g -o $(NAME) $(OBJECTS) $(LIBFT_PATH) -L/usr/local/lib -I/usr/local/include -lreadline

# Rule to compile source files
%.o: %.c
	gcc -g -c $< -o $@

# Clean rule
clean:
	rm -f $(NAME) $(OBJECTS)

# PHONY target to clean and rebuild the program
re: clean all
