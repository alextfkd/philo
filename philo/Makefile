NAME = philo
NAME_TS = philo_ts
CC = cc
CC_TS = $(CC) -O1 -fsanitize=thread -Wall -Wextra -Werror -Wno-unused-result

OBJDIR = ./objs
OBJDIR_TS = ./objs_ts
SRCDIR = ./srcs

SRCS = main.c ft_atoi.c philo_log.c ft_types.c validation.c pinfo.c create_mutex.c create_threads.c putils.c ft_strjoin.c ft_strlen.c ft_ltoa.c ft_itoa.c lock_fork.c philo_routines.c philo_loop.c create_log_msg.c common_state.c create_philo_args.c tv_utils.c ft_strnstr.c ft_strncmp.c ft_log_utils.c putils2.c

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

	echo "ODD TEST n 800 200 10 (SURVIVE)"
	./philo 3 800 200 200 10 | grep died | wc -l
	./philo 5 800 200 200 10 | grep died | wc -l
	./philo 11 800 200 200 10 | grep died | wc -l
	./philo 51 800 200 200 10 | grep died | wc -l
	./philo 101 800 200 200 10 | grep died | wc -l
	./philo 151 800 200 200 10 | grep died | wc -l
	./philo 199 800 200 200 10 | grep died | wc -l

	echo "ODD TEST n 850 300 100 10 (SURVIVE)"
	./philo 5 850 300 100 10 | grep died | wc -l
	./philo 11 850 300 100 10 | grep died | wc -l
	./philo 51 850 300 100 10 | grep died | wc -l
	./philo 101 850 300 100 10 | grep died | wc -l
	./philo 151 850 300 100 10 | grep died | wc -l

	echo "ODD TEST n 900 300 100 10 (SURVIVE)"
	./philo 199 900 300 100 10 | grep died | wc -l

	echo "EVEN TEST n 600 200 200 10 (SURVIVE)"
	./philo 4 600 200 200 10 | grep died | wc -l
	./philo 6 600 200 200 10 | grep died | wc -l
	./philo 10 600 200 200 10 | grep died | wc -l
	./philo 50 600 200 200 10 | grep died | wc -l
	./philo 150 600 200 200 10 | grep died | wc -l
	echo "EVEN TEST n 650 200 200 10 (SURVIVE)"
	./philo 200 650 200 200 10 | grep died | wc -l

	echo "EVEN TEST n 700 300 100 10 (SURVIVE)"
	./philo 4 700 300 100 10 | grep died | wc -l
	./philo 6 700 300 100 10 | grep died | wc -l
	./philo 10 700 300 100 10 | grep died | wc -l
	./philo 50 700 300 100 10 | grep died | wc -l

	echo "EVEN TEST n 800 300 100 10 (SURVIVE)"
	./philo 100 800 300 100 10 | grep died | wc -l

	echo "EVEN TEST n 900 300 100 10 (SURVIVE)"
	./philo 200 900 300 100 10 | grep died | wc -l

	echo "EVEN TEST 2 130 60 60 10 (SURVIVE)"
	./philo 2 130 60 60 100 | grep died | wc -l

.PHONY: all clean fclean re bonus ts
