# Değişkenler
CC = gcc
CFLAGS = -Wall -O2
SRC_DIR = test
BUILD_DIR = build
TARGET = $(BUILD_DIR)/my_program
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o

# Varsayılan hedef
all: $(TARGET)

#Hedef dosya
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo $?
	@echo $@

# Nesne dosyalarının nasıl üretileceğini tanımlar
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Temizlik hedefi
clean:
	@rm -rf $(BUILD_DIR)
# Bağımsız hedefler
.PHONY: all clean
