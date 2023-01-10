NAME = philo
SRC = src/main.c src/parse_args.c src/utils.c src/execution.c src/utils2.c src/utils3.c
OBJS = $(SRCS:.c=.o)
FLAGS = -pthread -Wall -Wextra -Werror
DEBUG_THREAD = -fsanitize=thread -g
DEBUG_MEMORY = -fsanitize=address
CLANG = clang

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) $(SRC) -o $(NAME) $(OBJS)
	rm -rf philo.dSYM
# $(DEBUG_THREAD)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all