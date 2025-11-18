#include <stddef.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "../include/sha1.h"

#define BUF_SIZE 4096 // we can make this 4096 that would be better
#define HASH_SIZE 20

int main(){
	printf("Welcom to Incremental Backup\n");

	time_t timestamp = time(NULL); // take the timestamp for version tracking
	FILE* infptr= fopen("./data/testin.txt","rb");
	
	char filename[256];
	snprintf(filename, sizeof(filename),"./data/.tracking/%ld.hash",timestamp);
	FILE* hfptr = fopen(filename,"wb" );
	snprintf(filename, sizeof(filename),"./data/.tracking/%ld.data",timestamp);
	FILE* outfptr= fopen(filename,"wb");

	if(infptr == NULL){
		printf("Error opening file\n");
		exit(1);
	}

	SHA1_CTX sha;
	uint8_t results[HASH_SIZE];
	uint8_t  buf[BUF_SIZE];
	size_t n;
	SHA1Init(&sha);

	// create the .tracking direcotry and save the base file or skip already done.
	if(mkdir("./data/.tracking", 0755) == 0){
		// create the hash and copy original
		while ((n = fread(buf,1,BUF_SIZE, infptr)) > 0) { // fread now read 1 byte by one byte and fread will return when BUF_SIZE if filed or EOF and return read count.. then go inside the loop. in the next iteration if nothing to read it will return 0 then loop will stop.
			SHA1Update(&sha, (uint8_t *)buf,n);
			fwrite(buf, 1, n, outfptr);
		}

		SHA1Final(results, &sha);
		// save hash	
		fwrite(results, HASH_SIZE, 1, hfptr);
		fclose(hfptr);
		fclose(outfptr);
	}else {

	}	
	
	fclose(infptr);
	printf("time is: %ld\n",timestamp);
	printf("0x");
	for (n = 0; n < HASH_SIZE; n++)
		printf("%02x", results[n]);// each byte of the hash as 2 digit hex
	return 0;
}
