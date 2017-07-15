/* Addition that saturates to TMin or TMax */

#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y) {
	//printf("\n");
	int w1 = sizeof(x) << 3; 
	int w2 = sizeof(y) << 3; 

	unsigned a = x >> (w1 - 1);
	unsigned b = y >> (w2 - 1);
	/*if (a && b)
		printf("both negative\n");
	else if (~a && ~b)
		printf("both positive\n");
	if (-((a^b) && 1)){
		printf("exclusive\n");
	}
	else 
		printf("not exclusive\n");*/
	int sum = (x + y); // diff signs 
	int w3 = sizeof(sum) << 3;
	unsigned c  = sum >> (w3 - 1);
	
	int negO = -(a && b) & -(~c && 1); // 1 if negative overflow
	int posO = -(~a && ~b) & -(c && 1); // 1 if positive overflow
	
	negO && (sum = INT_MIN);
	posO && (sum = INT_MAX);
	
	/*printf("sum "); printf("%d", sum); printf("\n");
	int neg = (INT_MIN & -(a && b)) & -(~c && 1); // both negative 
	printf("neg "); printf("%d", neg); printf("\n");
	int pos = (INT_MAX & -(~a && ~b)) & -(c && 1); // both positive
	printf("pos "); printf("%d", pos); printf("\n");
	return sum + neg + pos;*/
	return sum;
}

int main()
{
	for (int i = -2; i < 3; ++i)
		for (int j = -2; j < 3; ++j)
			printf("%d + %d = %d\n", i, j, saturating_add(i, j));
	printf("%d + %d = %d\n", INT_MIN, INT_MIN, saturating_add(INT_MIN, INT_MIN));
	printf("%d + %d = %d\n", -3, INT_MIN, saturating_add(-3, INT_MIN));
	printf("%d + %d = %d\n", INT_MIN, -3, saturating_add(INT_MIN, -3));
	printf("%d + %d = %d\n", INT_MIN, 0, saturating_add(INT_MIN, 0));
	printf("%d + %d = %d\n", 0, INT_MIN, saturating_add(0, INT_MIN));
	printf("%d + %d = %d\n", INT_MAX, INT_MAX, saturating_add(INT_MAX, INT_MAX));
	printf("%d + %d = %d\n", 3, INT_MAX, saturating_add(3, INT_MAX));
	printf("%d + %d = %d\n", INT_MAX, 3, saturating_add(INT_MAX, 3));
	printf("%d + %d = %d\n", INT_MAX, 0, saturating_add(INT_MAX, 0));
	printf("%d + %d = %d\n", 0, INT_MAX, saturating_add(0, INT_MAX));
	printf("%d + %d = %d\n", INT_MAX, -3, saturating_add(INT_MAX, -3));
	printf("%d + %d = %d\n", -3, INT_MAX, saturating_add(-3, INT_MAX));
	return 0;
}