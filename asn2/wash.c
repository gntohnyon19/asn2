//This is my code
//<Gilchrist Toh>
//CS366
// C file manipulation calls

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <linux/unistd.h> 
#include <unistd.h>
#include <utime.h>
#include <time.h>

#define MAXLENGTH 100

int main(int argc, char **argv)
{

  printf("\n		Table of Reference\n");
  printf(" ’c’ list the current file to /dev/tty (cat[1]the current file) \n ’d’ copy the current file (duplicate)\n ’r’ rename the current file \n ’u’ delete (unlink) the current file \n ’t’ zero (length) the current file (i.e.,truncate the current file) \n ’a’ append the current file to another file \n ’l’ display the last 100 bytes of the current file of fewer if fewer exist) (tail) \n ’m’ change the current file’s access permissions (see chmod[1] and chmod[2]) \n ’x’ change the current file’s access time to the current time (see utime[2]) \n ’n’ goto the next name (i.e., the next file) \n ’q’ quit \n");
  printf("\n ");

  if(argc <= 1)
  {
     printf("No files entered !!\n");
  }
  for (int i = 1; i < argc; i++)
   {
     FILE *fin = fopen(argv[i], "r");   // "man fopen" for other modes
     if (fin == NULL)
     {
        perror("fopen");
        exit(-1);
     }
     char command;

 
     printf("file : %s ", argv[i]);
     printf("command: ");
     scanf(" %c", &command);

     while(command != 'q')
     {	
      
      if(command == 'c')
      {
         printf("  this is file %s \n", argv[i]);
         
      }

      else if(command == 'd')
      {
	char destination[100];
        printf("Enter new destination:\n");
        scanf(" %[^\n]s",destination);
        char buffer[MAXLENGTH];
	size_t bytes;
	
        FILE *outfile = fopen(destination, "w+");

	while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fin)))
	{
    	   fwrite(buffer, 1, bytes, outfile);
	}
        fclose(outfile);
      }
      else if(command == 'r')
      {
        char newFile[100];
        printf("Enter new name:\n");
        scanf(" %[^\n]s",newFile);
        rename(argv[i],newFile);

      }

      
      else if(command == 'u')
      {
        
	int ret;
   	
	ret = remove(argv[i]);

   	if(ret == 0) 
   	{
      	  printf("File deleted successfully\n");
   	}
   	else 
   	{
      	  printf("Error: unable to delete the file\n");
   	}

      }

      else if(command == 't')
      {
	int fd;

        fd = open(argv[i], O_TRUNC, 0);

	close(fd);
	
      }
      else if(command == 'a')
      {
        char appendFile[100];
        printf("Enter a file that you want to append:\n");
        scanf(" %[^\n]s",appendFile);
        
	FILE *pFile;
	FILE *pFile2;
	char buffer[256];

	pFile=fopen(argv[i], "r");
	pFile2=fopen(appendFile, "a");
	if(pFile == NULL) {
	    perror("Error opening file.");
	}
	else {
	    while(fgets(buffer, sizeof(buffer), pFile2)) {
		fprintf(pFile, "%s", buffer);
	    }
	}
	fclose(pFile);
	fclose(pFile2);
      }
      else if(command == 'l')
      {
	
	unsigned char buffer[100];
	FILE *source;
	int x, cx;
	long size;
	
	source = fopen(argv[i], "r+b");
	fseek(source, 0, SEEK_END); // Set the new position to the end of file
	size = ftell(source); // Get the current position
	fseek(source, size-100, SEEK_SET);

	if(source != NULL)
	{
	   for(x =0; x<100; x++)
	   {
	      cx = fgetc(source);
	      buffer[x] = cx;
	      
	   }
	}
	else
	{
	   printf("file not found. \n");
	}
	fclose(source);
	
	buffer[x] = '\0';
        printf("100 bytes of this file is: \n  ");
	for(x = 0; x < sizeof(buffer); x++)
	{
	   printf("%c", buffer[x]);
	}
      
      
      }
      else if(command == 'm')
      {

      }
      else if(command == 'x')
      {
	    struct utimbuf timebuf;
	    struct stat statbuf;
	    int fdr;

	    if(stat(argv[i], &statbuf) < 0) {
		printf("Error getting file stats\n");
		return -1;
	    }

	    if( (fdr = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
		printf("Error opening file\n");
		return -1;
	    }

	    close(fdr);

	    timebuf.actime = statbuf.st_atime;
	    timebuf.modtime = statbuf.st_mtime;

	    if(utime(argv[i], &timebuf) < 0) {
		printf("unable to reset time\n");
		return -1;
	    }

	    printf("time is %s", ctime(&timebuf.modtime));
      }
  
      else if (command == 'n')
      {
        break;
      }
      printf("file : %s ", argv[1]);
      printf("command: ");
      scanf(" %c", &command);

   }
   if(command == 'q')
   {
     exit(-1);
   }
   
 }

  return 0;
}
