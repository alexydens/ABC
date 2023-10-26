# This is the makefile for ABC, my Ansi Base library for C
CFLAGS = -ansi -pedantic -Wall -Wextra -Wno-unused-variable

# Defining the DEBUG macro gives access to logging and assertions, and may also
# have more uses as this grows.
CFLAGS_TEST = -ansi -pedantic -Wall -Wextra -O2 -ffast-math -DDEBUG
LDFLAGS_TEST = -lABC -Wl,--copy-dt-needed-entries

BUILD_DIR=build
SRC_DIR=src

.PHONY: build clean test
.SILENT: build clean test

build: $(SRC_DIR)/base.c $(SRC_DIR)/base.h
		echo "Compiling: base.c..."
	gcc -c $(CFLAGS) $(SRC_DIR)/base.c -o $(BUILD_DIR)/base.o
		echo "Compiling: arena_alloc.c..."
	gcc -c $(CFLAGS) $(SRC_DIR)/arena_alloc.c -o $(BUILD_DIR)/arena_alloc.o
		echo "Compiling: file_io.c..."
	gcc -c $(CFLAGS) $(SRC_DIR)/file_io.c -o $(BUILD_DIR)/file_io.o
		echo "Creating lib..."
	ar -cvq $(BUILD_DIR)/libABC.a $(BUILD_DIR)/*.o
		echo "Copying: base.h to /usr/include/base.h..."
	rm -rf /usr/include/ABC/base.h
	cp $(SRC_DIR)/base.h /usr/include/ABC/base.h
		echo "Copying: arena_alloc.h to /usr/include/arena_alloc.h..."
	rm -rf /usr/include/ABC/arena_alloc.h
	cp $(SRC_DIR)/arena_alloc.h /usr/include/ABC/arena_alloc.h
		echo "Copying: file_io.h to /usr/include/file_io.h..."
	rm -rf /usr/include/ABC/file_io.h
	cp $(SRC_DIR)/file_io.h /usr/include/ABC/file_io.h
		echo "Copying: libABC.a to /usr/lib/x86_64-linux-gnu/libABC.a"
	rm -rf /usr/lib/x86_64-linux-gnu/libABC.a
	cp $(BUILD_DIR)/libABC.a /usr/lib/x86_64-linux-gnu/libABC.a

clean:
	rm -rf $(BUILD_DIR)/*

test: $(SRC_DIR)/test.c
	gcc $(CFLAGS_TEST) $(SRC_DIR)/test.c -o $(BUILD_DIR)/test $(LDFLAGS_TEST)
	$(BUILD_DIR)/test
	rm -rf $(BUILD_DIR)/test
