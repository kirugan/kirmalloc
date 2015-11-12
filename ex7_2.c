/**
 * Implement malloc and free functions
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* head = 0;
char* tail = 0;

void *kirmalloc(size_t size){
	size_t* ptr = sbrk((intptr_t) (size + sizeof(size_t)));
	// in case of error
	if((int) ptr == -1){
		return NULL;
	}

	printf("Sbrk %p, request to allocate %d bytes (+%d hidden bytes)\n", ptr, size, sizeof(size_t));
	*ptr = size;

	return ++(ptr);
}

void kirfree(void* ptr){
	size_t block_len = *(((int *) ptr) - 1);
	printf("Request to free block of %d bytes\nPointer %p\n", block_len, ptr);
	tail = ptr;
}

int main(int argc, char** argv){
	printf("Initial sbrk %p\n", sbrk(0));
	char* str = kirmalloc(10);
	kirfree(str);

	printf("FINISH");

	return 0;

	strcpy(str, "12");
	printf("Kirmalloc result %p\n", str);
	printf("Result string '%s'\n", str);
}