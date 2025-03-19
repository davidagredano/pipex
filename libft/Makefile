AR = ar
ARFLAGS = rcs

CC = cc
CFLAGS = -MMD -Wall -Wextra -Werror
COMPILE.c = $(CC) $(CFLAGS) -c
OUTPUT_OPTION = -o $@

RM = rm -f
RMDIR = rm -rf


NAME = libft.a
PRINTF_DIR = printf/
SRCS = ft_isupper.c ft_islower.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_isspace.c ft_strlen.c ft_strnlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strspn.c \
	ft_strcspn.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_strtok.c ft_itoa.c ft_uitoa.c ft_uitoa_caps.c ft_ultoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putstr.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c \
	ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c get_next_line.c $(addprefix $(PRINTF_DIR), \
	ft_printf.c spec_parser.c ft_print_c.c ft_print_s.c ft_print_p.c \
	ft_print_d.c ft_print_u.c ft_print_x.c utils.c)
BUILD_DIR = build
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:%.c=$(BUILD_DIR)/%.d)


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $@/$(PRINTF_DIR)

%.d: ;

-include $(DEPS)


clean:
	$(RMDIR) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
