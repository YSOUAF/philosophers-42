CC     = cc
CFLAGS = -Wall -Werror -Wextra

NAME   = philo

SRCS   = actions.c check.args.c ft_atoi.c \
         ft_error.c init.c \
         main.c monitor.c one_philo.c \
         routine.c threads.c time_functions.c check_arg2.c

OBJS   = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
