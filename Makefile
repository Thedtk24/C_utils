EXEC = a.out

INCLUDE_DIR = include
SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.c) main.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -g

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	@echo "Compilation terminée : ./$(EXEC)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o *.o $(EXEC)
	@echo "Nettoyage terminé."

re: clean all
