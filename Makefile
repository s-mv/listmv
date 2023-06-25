TITLE = listmv
CC = clang

build:
	@echo "-------- BUILDING --------"
	@mkdir -p lib
	@$(CC) $(TITLE).c -shared -o lib/$(TITLE).so
	@cp $(TITLE).h lib/$(TITLE).h
	@echo "Done."
	@echo "Header and source at ./lib"
	@echo "---------- DONE ----------"

install: # linux-only
	@make build
	@sudo cp lib/$(TITLE).so /usr/lib/$(TITLE).so
	@sudo cp lib/$(TITLE).h /usr/include/$(TITLE).h
	@echo "Libary has been installed."