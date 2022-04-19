NAME	=	philo
SRCS	=	generate_philos.c\
			generate_monitors.c\
			daily_routine.c\
			main.c\
			utils.c\
			input_to_info.c\
			ft_atou.c
INCS	=	constant.h\
			philo.h\
			utils.h

OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean :
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

reclean:
	$(MAKE) re
	$(MAKE) clean

.PHONY: clean fclean re reclean all