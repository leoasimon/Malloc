# ================ MAKEFILE: libft_malloc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

.PHONY: all, clean, fclean, re

NAME		= libft_malloc_$(HOSTTYPE).so

CC 			:= gcc

SRC			+= malloc.c
SRC			+= realloc.c
SRC			+= free.c
SRC			+= show_alloc_mem.c

SRC			+= allocate.c
SRC			+= handle_large.c
SRC			+= init.c

SRC			+= util_mem.c
SRC			+= util_str.c

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
	@$(CC) -shared -fPIC -o $(NAME) $(OBJ)
	@ln -s $(NAME) libft_malloc.so
	@echo "[MALLOC compiled.]\n"

all: $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@rm -f libft_malloc.so

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)