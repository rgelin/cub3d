#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)
	@cp $(NOM) ../

clean:
	@echo "$(RED)Cleaning minilibx...\n$(NO_COLOR)"
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) all --no-print-directory
