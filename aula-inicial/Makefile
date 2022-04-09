STREAM = StudentStreamFileHandler.c
MAIN = Main.c
BINARY = main
NAME = FILES

all:
	gcc -Wall -g $(STREAM) $(MAIN) -o $(BINARY)

run:
	./$(BINARY)

zip: 
	@zip -r $(NAME).zip *