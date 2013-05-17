#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getKey(char usrKey[], unsigned char ** keys);

int main(int argc, char * argv[])
{
	FILE * fd;
	FILE * out;
	unsigned char tmp;
	char * outname;
	unsigned char * keys;
	int size, index = 0;
	int totalKeys = 0;

	if(argc < 3)
	{
		printf("Usage: %s <file> <4 byte hex key>\n", argv[0]);
		printf("   ex: %s pic.jpg deadbeef\n", argv[0]);
		return -1;
	}
	else
		printf("Reading file: %s\n", argv[1]);

	size = strlen(argv[1]) + 6;
	outname = (char *)malloc(size);
	if(outname != NULL)
	{
		strcpy(outname, argv[1]);
		strcat(outname, ".enc");
		printf("Writing to  : %s\n", outname);
	}

	fd = fopen(argv[1], "rb");
	out = fopen(outname, "wb");
	
	totalKeys = getKey(argv[2], &keys);
	
	if(fd != NULL && out != NULL && totalKeys != -1)
	{
		while(fread(&tmp, sizeof(char), 1, fd) != 0)
		{
			if(index % totalKeys == 0)
				index = 0;
			
			tmp ^= *(keys + index);		// *(keys + index) == keys[index]
			index++;
			if(fwrite(&tmp, 1, sizeof(char), out) == 0)
			{
				printf("problem writing to file\n");
				return -1;
			}
			
		}
	}

	fclose(fd);
	fclose(out);
	free(outname);
	
	if(totalKeys != -1)
		free(keys);

	return 0;
}

int getKey(char usrKey[], unsigned char ** keys)
{
	int size = strlen(usrKey);
	int numKeys = size / 2;
	int i = 0, tmp = 0;
	unsigned char * tkp;

	if(size % 2 == 1)	//error!
	{
		keys = NULL;
		return -1;
	}

	*keys = (unsigned char *)malloc(sizeof(unsigned char) * numKeys);
	tkp = *keys;

	while(usrKey[i] != '\0')
	{
		switch(usrKey[i])
		{
			case '0':
				if(i % 2 == 0)
					tmp |= 0x00;
				else
					tmp |= 0x00;
				break;
			case '1':
				if(i % 2 == 0)
					tmp |= 0x10;
				else
					tmp |= 0x01;
				break;
			case '2':
				if(i % 2 == 0)
					tmp |= 0x20;
				else
					tmp |= 0x02;
				break;
			case '3':
				if(i % 2 == 0)
					tmp |= 0x30;
				else
					tmp |= 0x03;
				break;
			case '4':
				if(i % 2 == 0)
					tmp |= 0x40;
				else
					tmp |= 0x04;
				break;
			case '5':
				if(i % 2 == 0)
					tmp |= 0x50;
				else
					tmp |= 0x05;
				break;
			case '6':
				if(i % 2 == 0)
					tmp |= 0x60;
				else
					tmp |= 0x06;
				break;
			case '7':
				if(i % 2 == 0)
					tmp |= 0x70;
				else
					tmp |= 0x07;
				break;
			case '8':
				if(i % 2 == 0)
					tmp |= 0x80;
				else
					tmp |= 0x08;
				break;
			case '9':
				if(i % 2 == 0)
					tmp |= 0x90;
				else
					tmp |= 0x09;
				break;
			case 'a':
			case 'A':
				if(i % 2 == 0)
					tmp |= 0xa0;
				else
					tmp |= 0x0a;
				break;
			case 'b':
			case 'B':
				if(i % 2 == 0)
					tmp |= 0xb0;
				else
					tmp |= 0x0b;
				break;
			case 'c':
			case 'C':
				if(i % 2 == 0)
					tmp |= 0xc0;
				else
					tmp |= 0x0c;
				break;
			case 'd':
			case 'D':
				if(i % 2 == 0)
					tmp |= 0xd0;
				else
					tmp |= 0x0d;
				break;
			case 'e':
			case 'E':
				if(i % 2 == 0)
					tmp |= 0xe0;
				else
					tmp |= 0x0e;
				break;
			case 'f':
			case 'F':
				if(i % 2 == 0)
					tmp |= 0xf0;
				else
					tmp |= 0x0f;
				break;
			default:		//error!
				free(*keys);
				return -1;
		}
		
		if(i % 2 == 1)
		{
			*tkp++ = (unsigned char)tmp;
			tmp = 0;
		}
		
		i++;
	}
	
	return numKeys;
}
