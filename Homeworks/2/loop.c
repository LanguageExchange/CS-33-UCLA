/*
A.	x - %rdi
	n - %esi
	mask - %edx
B.	result == 0
	mask == 1
C.	mask != 0
D.	left shifted by whatever amount is in the least significant 8 bits of n
E.	an | operation with (x masked with the latest version of mask)
*/

long loop(long x, long n){
	long result = 0;
	long mask;
	for (mask = 1; mask != 0; mask = mask << (n & 0xff)){
		result |= (x & mask);
	}
	return result;
}