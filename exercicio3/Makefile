MAIN = Main.c
BINARY = main
NAME = ex3
HANDLER = FileHandler.c 
STUDENT = Student.c
BTREE = btree.c
CRUD = CRUD.c

#adicionar todos os .c que serão compilados ao lado do $(MAIN)
all:
	gcc -g $(MAIN) $(BTREE) $(STUDENT) $(HANDLER) $(CRUD) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o