# ----------------------------------------------------------------------------
# COLORES |
# ----------------------------------------------------------------------------
 RESET=\033[0m
 DARK=\033[132m
 RED=\033[31m
 GREEN=\033[32m
 YELLOW=\033[33m
 BLUE=\033[34m
 MAGENTA=\033[35m
 CYAN=\033[36m
 WHITE=\033[37m
 BOLDBLACK=\033[1m\033[30m
 BOLDRED=\033[1m\033[31m
 BOLDWHITE=\033[1m\033[37m

# ----------------------------------------------------------------------------
# VARIABLES |
# ----------------------------------------------------------------------------


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

.PHONY: all, clean, fclean, re

NAME		= libft_malloc_$(HOSTTYPE).so

CC 			:= gcc

SRC			+= malloc.c
SRC			+= init.c
SRC			+= show_alloc_mem.c
SRC			+= free.c
SRC			+= realloc.c

OBJ_PATH 	= ./obj/
OBJ_NAME 	= $(SRC:.c=.o)
OBJ 		= $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CFLAGS		:= -Wall -Wextra -Werror

# To make .o files (-c) in another folder
# -O0: Optimized for compilation time
# -g:  generate debugger info
$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g
	@echo -n .

# Make shared library from object files
# symlink to simplified library name
$(NAME): $(OBJ)
	@$(CC) -shared -fPIC -o $(NAME) $(OBJ) -L libft -lft
	@ln -s $(NAME) libft_malloc.so
	@echo "[MALLOC compiled.]\n"

all: $(NAME)

libft:
	@make -C libft/ all

test: cleantests
	@echo "\n${MAGENTA} SCHOOL TESTS ${RESET}"
	@sh ./test/run.sh
	@python ./test/test.py
	@echo "\n${GREEN} SANDBOX ${RESET}"
	@cp $(NAME) ./sandbox/
	@python ./sandbox/test.py

cleantests:
	@rm -rf test/bin
	@rm -rf sandbox/bin
	@rm -f ./sandbox/$(NAME)
	@rm -f ./sandbox/libft_malloc.so

clean: cleantests
	@rm -rf $(OBJ_PATH)
	@rm -f libft_malloc.so

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: test