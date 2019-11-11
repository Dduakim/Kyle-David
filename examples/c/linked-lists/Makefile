ll: ll.c
	gcc -Wall -Wextra -o ll *.c

ll.debug: ll.c
	gcc -g -Wall -Wextra -o ll.debug *.c

check: ll
	valgrind --leak-check=full --show-leak-kinds=all ./ll

debug-check: ll.debug
	valgrind --leak-check=full --show-leak-kinds=all ./ll.debug
