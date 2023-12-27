#include <stdio.h>

int main(int ac, char **av) {
	printf("param count: %d\nparams: ", ac);
	while (ac--)
		printf("%s,", *av++);
	printf("\n");
}
