NAME = philo
CC = cc -g

OBJDIR = ./objs
SRCDIR = ./srcs

SRCS = main.c ft_atoi.c philo_log.c fork_log.c ft_types.c validation.c pinfo.c create_mutex.c create_threads.c putils.c ft_strjoin.c ft_strlen.c ft_ltoa.c ft_itoa.c lock_fork.c philo_routines.c philo_loop.c create_log_msg.c common_state.c create_philo_args.c tv_utils.c ft_strnstr.c ft_strncmp.c ft_log_utils.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

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

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)
	rm -fr $(OBJDIR)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus 