CC = cc
CFLAGS = -MMD -Wall -Wextra -Werror
COMPILE.c = $(CC) $(CFLAGS) -c
OUTPUT_OPTION = -o $@

LDFLAGS = -Llibft
LINK.o = $(CC) $(LDFLAGS)
LDLIBS = -lft

RM = rm -f
RMDIR = rm -rf

NAME = pipex
SRCS_DIR = srcs
SRCS = main.c commands.c utils.c debug.c
BUILD_DIR = build
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:%.c=$(BUILD_DIR)/%.d)

LIBFT = libft.a
LIBFT_DIR = libft


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(LINK.o) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(BUILD_DIR):
	mkdir -p $@

%.d: ;

-include $(DEPS)


clean:
	$(RMDIR) $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT_DIR)/$(LIBFT)

re:	fclean all
