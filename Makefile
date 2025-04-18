CFLAGS = -Wall -Wextra -Werror

all: annuaire

annuaire: main.o contact.o file.o hashtable.o tree.o
	gcc $(CFLAGS) -o $@ $^

main.o: TP3_VEURRIER_TROGNON_main.c TP3_VEURRIER_TROGNON_main.h
	gcc -c $<
	mv TP3_VEURRIER_TROGNON_main.o $@

contact.o: TP3_VEURRIER_TROGNON_contact.c TP3_VEURRIER_TROGNON_contact.h
	gcc -c $<
	mv TP3_VEURRIER_TROGNON_contact.o $@

file.o: TP3_VEURRIER_TROGNON_file.c TP3_VEURRIER_TROGNON_file.h
	gcc -c $<
	mv TP3_VEURRIER_TROGNON_file.o $@

hashtable.o: TP3_VEURRIER_TROGNON_hashtable.c TP3_VEURRIER_TROGNON_hashtable.h
	gcc -c $<
	mv TP3_VEURRIER_TROGNON_hashtable.o $@

tree.o: TP3_VEURRIER_TROGNON_tree.c TP3_VEURRIER_TROGNON_tree.h
	gcc -c $<
	mv TP3_VEURRIER_TROGNON_tree.o $@

clean:
	rm *.o annuaire