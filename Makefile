
# Path to the libft.a archive
NAME = minishell
LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
SOURCES = test.c utils.c char_classification.c lexer.c unquote.c lexer_utils.c parser.c expander.c splitter.c syntax_analyzer.c
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

# PHONY target to clean and rebuild the program
re: clean all
