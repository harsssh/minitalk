SERVER_NAME:=bin/minitalk-server
CLIENT_NAME:=bin/minitalk-client

LIBFT:=libft/libft.a

SRC_DIR=.
BUILD_DIR:=build

CFLAGS:=-g -Wall -Wextra -Werror -Ilibft/include
DEPFLAGS=-MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

SERVER_SRC:=server.c
CLIENT_SRC:=client.c
SERVER_OBJ:=$(addprefix $(BUILD_DIR)/,$(SERVER_SRC:.c=.o))
CLIENT_OBJ:=$(addprefix $(BUILD_DIR)/,$(CLIENT_SRC:.c=.o))
DEP:=$(SERVER_OBJ:.o=.d) $(CLIENT_OBJ:.o=.d)

.PHONY: all
all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(LIBFT) $(SERVER_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_NAME): $(LIBFT) $(CLIENT_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

.PHONY: run
run:
	@$(SERVER_NAME)

.PHONY: send
send:
	@$(CLIENT_NAME) $(shell pgrep minitalk-server) $(MSG)

.PHONY: clean
clean:
	make -C libft clean
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ) $(DEP)

.PHONY: fclean
fclean: clean
	make -C libft fclean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME)

.PHONY: re
re: fclean all

-include $(DEP)
