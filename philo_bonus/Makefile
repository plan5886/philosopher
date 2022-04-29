NAME	=	philo_bonus
SRCS	=	generate_childs.c\
			generate_semaphores.c\
			daily_routine.c\
			input_to_info.c\
			main.c\
			utils.c\
			ft_atou.c\
			calc_exit_status.c\
			proc_philo.c
INCS	=	constant.h\
			philo.h\
			utils.h

OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Werror -Wextra -fsanitize=thread -g

all : $(NAME)

bonus : $(NAME)

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