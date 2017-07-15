/* Return 1 when any odd bit of x equals 1; 0 otherwise. Assume w=32 */
#include <stdio.h>
int any_odd_one(unsigned x){
	unsigned y = x & 0xaaaaaaaa;
	return y && 1;
}

int main(void) {
	printf("x = %u", any_odd_one(6));
	printf("\n");
	return 0;
}