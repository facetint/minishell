#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
     int
     gettimeofday(struct timeval *restrict tp, void *restrict tzp);

void print_hex(unsigned long num) {
	if (num >= 16) {
		print_hex(num / 16);
	}
	write(1, &"0123456789abcdef"[num % 16], 1);
}

void print_ptr(char *msg, void *ptr) {
	while (*msg) {
		if (msg[0] == '%' && msg[1] == 'p') {
			print_hex((unsigned long) ptr);
			msg += 2;
			continue;
		}
		write(1, msg, 1);
		msg++;
	}
}

void *fake_malloc(int size) {
	static int seed = -1; 

	if (seed < 0) {
		struct timeval time;
		gettimeofday(&time, NULL);
		seed = (int) (time.tv_usec + time.tv_sec);
		srand(seed);
	}

	int chance = rand() % 10;

	if (chance < 1){
		return NULL;
	} else { 
		void *ptr = malloc(size);
		print_ptr("MALLOC %p\n", ptr);
		return ptr;
	}
}

void fake_free(void *ptr) {
	print_ptr("FREE %p\n", ptr);
	free(ptr);
}

void test() {
	int **test = (int **) safe_malloc(50 * sizeof(int *));
	if (test == NULL) {
		print_ptr("PROGRAM LEVEL malloc failed\n", 0);
		return;
	}
	for (int i = 0; i < 50; i++) {
		test[i] = safe_malloc(sizeof(int) * i);
		if (test[i] == NULL) {
			print_ptr("PROGRAM LEVEL malloc(2) failed\n", 0);
			return;
		}
	}
	
	abort_memory();
}

void test2() {
	if (!safe_malloc(10)) return;
	if (!safe_malloc(10)) return;
	void *ptr = safe_malloc(10);
	if (!ptr) return;
	safe_free(ptr);
	if (!safe_malloc(10)) return;
	
	void *ptr2 = safe_malloc(10);
	if (!ptr2) return;
	safe_free(ptr2);

	abort_memory();
}

void abort_start_func() {
	print_ptr("PROGRAM LEVEL i know that memory of my program started to being aborted\n", 0);
}

void abort_stop_func() {
	print_ptr("PROGRAM LEVEL i know that memory of my program completely aborted.\n", 0);
	// exit() will fit here perfectly
}


int main() {
	register_pre_abort_func(abort_start_func);
	register_post_abort_func(abort_stop_func);
    //test();
	write(1, "test2\n", 6);
	test2();
    return 0;
}
