MAIN = Main.c
#Adicionar variáveis para outros arquivos .c que precisar na compilação
#Ex: STUDENT = Student.chec
#FILEHANDLER = FileHandler.c FixedField.c
BINARY = main
NAME = ex1
HANDLER = FileHandler.c CsvHandler.c
STUDENT = Student.c

#adicionar todos os .c que serão compilados ao lado do $(MAIN)
all:
	gcc -Wall -g $(MAIN) $(HANDLER) $(STUDENT) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o