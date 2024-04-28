build:
	gcc -Wall -Wextra -g -o tema2 tema2.c
clean:
	rm -f tema2
pack:
	zip -FSr 312CC_Abăhnencei_Alin_Andrei.zip README Makefile tema2.c