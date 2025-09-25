NAME = philo
CC = cc -g
GCC = gcc -g

OBJDIR = ./objs
SRCDIR = ./srcs

SRCS = main.c ft_atoi.c ft_log.c ft_types.c validation.c pinfo.c create_mutex.c create_threads.c putils.c ft_strjoin.c ft_strlen.c ft_ltoa.c

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincludes

#VPATH = $(SRCDIR):$(SRCDIR)/ft_cdlst:$(SRCDIR)/ps_wrap:$(SRCDIR)/stacks:$(SRCDIR)/ps_utils:$(SRCDIR)/sort
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

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus objs 