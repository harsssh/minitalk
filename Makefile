SERVER_NAME:=server
CLIENT_NAME:=client

LIBFT:=libft/libft.a

SRC_DIR=.
BUILD_DIR:=build

CFLAGS:=-Wall -Wextra -Werror -Ilibft/include

SERVER_SRC:=server.c
CLIENT_SRC:=client.c
SERVER_OBJ:=$(addprefix $(BUILD_DIR)/,$(SERVER_SRC:.c=.o))
CLIENT_OBJ:=$(addprefix $(BUILD_DIR)/,$(CLIENT_SRC:.c=.o))

.PHONY: all
all: $(SERVER_NAME) $(CLIENT_NAME)

.PHONY: bonus
bonus: all

$(SERVER_NAME): $(LIBFT) $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_NAME): $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

.PHONY: run
run:
	@./$(SERVER_NAME)

.PHONY: send
send:
	@./$(CLIENT_NAME) $(shell pgrep -x $(SERVER_NAME)) $(MSG)

.PHONY: clean
clean:
	make -C libft clean
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY: fclean
fclean: clean
	make -C libft fclean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)

.PHONY: re
re: fclean all
