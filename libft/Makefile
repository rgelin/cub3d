# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 12:26:15 by rgelin            #+#    #+#              #
#    Updated: 2022/03/10 03:20:09 by rgelin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          =       gcc

CFLAGS      =       -Wall -Wextra -Werror

SRCS        =       ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c 
					
BSRCS		=		ft_lstadd_back.c \
					ft_lstadd_front.c \
					ft_lstclear.c \
					ft_lstdelone.c \
					ft_lstiter.c \
					ft_lstlast.c \
					ft_lstmap.c \
					ft_lstnew.c \
					ft_lstsize.c 

GNL			=		./get_next_line/get_next_line.c \
					./get_next_line/get_next_line_utils.c 
					
OBJS        =       $(SRCS:%.c=%.o)

BOBJS		=		$(BSRCS:%.c=%.o)

GNL_OBJS	=		$(GNL:%.c=%.o)

REMOVE		=		rm -f

NAME        =       libft.a

#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------

.c.o:
			@printf "$(YELLOW)Generating libft objects... %-33.33s\r$(NO_COLOR)" $@
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			
all:		$(NAME)

$(NAME):	$(OBJS) $(GNL_OBJS)
			@echo "$(GREEN)\n\nCompiling libft...$(NO_COLOR)"
			@ar rc  $(NAME) $(OBJS) $(GNL_OBJS)
			@ranlib $(NAME)

clean:
			@echo "$(RED)Cleaning libft...\n$(NO_COLOR)"
			@$(REMOVE) $(OBJS) $(BOBJS) $(GNL_OBJS)

fclean:		clean
			@$(REMOVE) $(NAME)

re:			fclean all

bonus:		$(OBJS) $(BOBJS) $(GNL_OBJS)
			@ar rc $(NAME) $(OBJS) $(BOBJS) $(GNL_OBJS)
			@ranlib $(NAME)

.PHONY: 	all clean fclean re bonus .c.o
