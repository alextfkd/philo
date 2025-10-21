NAME = philo
NAME_TS = philo_ts
CC = cc -g
CC_TS = $(CC) -O1 -fsanitize=thread -Wall -Wextra -Werror -Wno-unused-result

OBJDIR = ./objs
OBJDIR_TS = ./objs_ts
SRCDIR = ./srcs

SRCS = main.c ft_atoi.c philo_log.c ft_types.c validation.c pinfo.c create_mutex.c create_threads.c putils.c ft_strjoin.c ft_strlen.c ft_ltoa.c ft_itoa.c lock_fork.c philo_routines.c philo_loop.c create_log_msg.c common_state.c create_philo_args.c tv_utils.c ft_strnstr.c ft_strncmp.c ft_log_utils.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJS_TS = $(addprefix $(OBJDIR_TS)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes

VPATH = $(SRCDIR)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

ts: $(OBJDIR_TS) $(NAME_TS)

$(OBJDIR_TS):
	mkdir -p $(OBJDIR_TS)

$(NAME_TS): $(OBJS_TS)
	$(CC_TS) $(IFLAGS) $(OBJS_TS) -o $@

$(OBJDIR_TS)/%.o: %.c
	mkdir -p $(OBJDIR_TS)
	$(CC_TS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -fr $(OBJDIR)
	rm -fr $(OBJDIR_TS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TS)

re: fclean all

test: re
	echo "ODD TEST (DIE)"
	./philo 1 800 200 200 10 | grep died | wc -l

	echo "ODD TEST (SURVIVE)"
	./philo 3 800 200 200 10 | grep died | wc -l
	./philo 5 800 200 200 10 | grep died | wc -l
	./philo 11 800 200 200 10 | grep died | wc -l
	./philo 101 800 200 200 10 | grep died | wc -l
	./philo 199 800 200 200 10 | grep died | wc -l

	echo "EVEN TEST (SURVIVE)"
	./philo 4 600 200 200 10 | grep died | wc -l
	./philo 6 600 200 200 10 | grep died | wc -l
	./philo 12 600 200 200 10 | grep died | wc -l
	./philo 102 600 200 200 10 | grep died | wc -l
	./philo 200 600 200 200 10 | grep died | wc -l

.PHONY: all clean fclean re bonus ts
