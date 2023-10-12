TITLE = listmv
CC ?= clang
VER = c99

build:
	@echo "-------- BUILDING --------"
	@mkdir -p lib
	@$(CC) $(TITLE).c -shared -std=$(VER) -o lib/$(TITLE).so
	@cp $(TITLE).h lib/$(TITLE).h
	@echo "Done."
	@echo "Header and source at ./lib"
	@echo "---------- DONE ----------"

install: # linux-only
	@make build
	@sudo cp lib/$(TITLE).so /usr/lib/$(TITLE).so
	@sudo cp lib/$(TITLE).h /usr/include/$(TITLE).h
	@echo "Library has been installed."

# this is for my personal debugging
test:
	$(CC) examples/list.c listmv.c -I . -o examples/list
