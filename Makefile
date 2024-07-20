.DEFAULT_GOAL := build

BUILD_DIR := build

.PHONY: setup
setup:
	@cmake -S . -B $(BUILD_DIR)

.PHONY: build
build: setup
	@make -C $(BUILD_DIR)

.PHONY: flash
flash: build
	@picotool load kca-pico.uf2
	@picotool reboot

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm kca-pico.uf2
