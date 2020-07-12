#include <stdint.h>
#include <stdio.h>


uint32_t my_htonl(uint32_t n)
{
	uint32_t n1=(n & 0xFF000000) >> 24;
	uint32_t n2=(n & 0x00FF0000) >> 8;
	uint32_t n3=(n & 0x0000FF00) << 8;
	uint32_t n4=(n & 0x000000FF) << 24;
	return n1 | n2 | n3 | n4;
}

int main(int argc, char *argv[])
{	
	// error handling
	if (argc!=3){
		printf("Usage: %s <filename1> <filename2>\n", argv[0]);
		return 0;
	}

	// input: network byte order
	uint8_t network_buffer1[4];
	uint8_t network_buffer2[4];

	// file open
	FILE *file1=fopen(argv[1], "rb");
	FILE *file2=fopen(argv[2], "rb");

	// file read
	fread(network_buffer1, 1, sizeof(uint8_t)*4, file1);
	uint32_t* p1=reinterpret_cast<uint32_t*>(network_buffer1);


	fread(network_buffer2, 1, sizeof(uint8_t)*4, file2);
	uint32_t* p2=reinterpret_cast<uint32_t*>(network_buffer2);
	
	// invert byte order
	uint32_t n1=my_htonl(*p1);
	uint32_t n2=my_htonl(*p2);

	// result print
	printf("%d(0x%x)", n1, n1);
	printf(" + ");
	printf("%d(0x%x)", n2, n2);
	printf(" = ");
	printf("%d(0x%x)\n", n1+n2, n1+n2);

	// file close
	fclose(file2);
	fclose(file1);

	return 0;
}
