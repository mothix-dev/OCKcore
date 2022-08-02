CFLAGS :=-Wshadow -Wall -Wextra -Wpedantic -Wstrict-overflow -Wfatal-errors -std=c17
BUILD_DIR := build
SRCS := src/main.c

all: textutils fileutils shutils

textutils: cat
shutils: yes false tty whoami uname echo pwd
fileutils: link

cat: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/cat cat.c $(CFLAGS)

echo: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/echo echo.c $(CFLAGS)

false: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/false false.c $(CFLAGS)

head: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/head head.c $(CFLAGS)

link: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/link link.c $(CFLAGS)

true: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/true true.c $(CFLAGS)

pwd: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/pwd pwd.c $(CFLAGS)

tty: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/tty tty.c $(CFLAGS)

uname: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/uname uname.c $(CFLAGS)

whoami: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/whoami whoami.c $(CFLAGS)

yes: |$(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/yes yes.c $(CFLAGS)

$(BUILD_DIR):
	@echo "Folder $(BUILD_DIR) does not exist, creating it..."
	mkdir -p $@
