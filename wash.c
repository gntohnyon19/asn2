//This is my code
//<Gilchrist Toh>
//CS366
// C file manipulation calls

#include <sys/types.h>
#include <string.h>
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

void delete(int status, char fileName[100])
{
   status = remove(fileName);

   if(status == 0) 
   {
     printf("File deleted successfully\n");
   }
   else 
   {
     printf("Error: unable to delete the file\n");
   }
   
}

void renameFile(char oldName[100], char fileName[100])
{
   rename(oldName,fileName);
   printf("File was successfully renamed\n");
}

void concatenateFile(char fileName[100])
{
   char buf[MAXLENGTH];

   FILE *fin = fopen(fileName, "r");   // "man fopen" for other modes
   if (fin == NULL)
   {
     perror("fopen");
     exit(-1);
   }

   while (!feof(fin))
   {
     if (fgets(buf, MAXLENGTH, fin) == NULL)
       break;
    printf("%s", buf);
   }
}

void duplicateFile(char fileName[100])
{
   char buffer[MAXLENGTH];
   size_t bytes;

   FILE *outfile = fopen(fileName, "w+");
   if (outfile == NULL)
   {
       perror("fopen");
       exit(-1);
   }
   while (0 < (bytes = fread(buffer, 1, sizeof(buffer), outfile)))
   {
      fwrite(buffer, 1, bytes, outfile);
   }
   fclose(outfile);
}

void truncateFile(char fileName[100])
{
   int fd;

   fd = open(fileName, O_TRUNC, 0);
    if( (fd = open(fileName,O_TRUNC)) < 0) 
    {
	printf("Error opening file\n");
	exit(-1);
    }
    close(fd);
    printf("File was truncated\n");
}

void appendFile(char Oldfile[100], char newFile[100])
{

   FILE *pFile;
   FILE *pFile2;
   char buffer[256];

   pFile = fopen(Oldfile, "r");
   pFile2 = fopen(newFile, "a");
   if(pFile == NULL) {
      perror("Error opening file.");
   }
   else {
     while(fgets(buffer, sizeof(buffer), pFile)) {
	  fprintf(pFile2, "%s", buffer);
     }
     printf("File successfully appended\n");
   }
   fclose(pFile);
   fclose(pFile2);
}

void listFile(char fileName[100])
{
   unsigned char buffer[100];
   FILE *source;
   int x, cx;
   long size;

   source = fopen(fileName, "r");
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

   printf("\n");
}

void chmode(char fileName[100])
{
        char mode[15];
	printf("Here are the commands you can enter: 777, 755, 700, 666, 644, 600\n");
        printf("Type what permission to change: \n");
        scanf("%s", mode);
       
        if(strcmp(mode, "700") == 0)
        {
            chmod(fileName, S_IRUSR | S_IWUSR | S_IXUSR);
            printf("Changed mode.\n");
        }
        else if(strcmp(mode, "644") == 0)
        {
            chmod(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            printf("Changed mode.\n");
        }
        else if(strcmp(mode, "777") == 0)
        {
      	    chmod(fileName, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH); 
            printf("Changed mode.\n");
        }
        else if(strcmp(mode, "666") == 0)
        {
      	    chmod(fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            printf("Changed mode.\n");
        }
        else if(strcmp(mode, "755") == 0)
        {
            chmod(fileName, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
            printf("Changed mode.\n");
        }
        else if(strcmp(mode, "600") == 0)
        {
            chmod(fileName, S_IRUSR | S_IWUSR);
            printf("Changed mode.\n");
        }
        else
        {
      	    printf("Here are the commands you have to enter: 777, 755, 700, 666, 644, 600\n");
        }	
        

}

void curTime(char fileName[100])
{
        struct utimbuf timebuf;
	    struct stat statbuf;
	    int fdr;

	    if(stat(fileName, &statbuf) < 0) 
	    {
		printf("Error getting file stats\n");
		exit(-1);
	    }

	    if( (fdr = open(fileName, O_RDWR | O_TRUNC)) < 0) 
	    {
		printf("Error opening file\n");
		exit(-1);
	    }

	    close(fdr);

	    if(utime(fileName, &timebuf) < 0) 
	    {
		printf("unable to reset time\n");
		exit(-1);
	    }

	    printf("time is %s", ctime(&statbuf.st_ctime));
        

}
int main(int argc, char **argv)
{

  printf("\n		Table of Reference\n");
  printf(" ’c’ list the current file to /dev/tty (cat[1]the current file) \n ’d’ copy the current file (duplicate)\n ’r’ rename the current file \n ’u’ delete (unlink) the current file \n ’t’ zero (length) the current file (i.e.,truncate the current file) \n ’a’ append the current file to another file \n ’l’ display the last 100 bytes of the current file of fewer if fewer exist) (tail) \n ’m’ change the current file’s access permissions (see chmod[1] and chmod[2]) \n ’x’ change the current file’s access time to the current time (see utime[2]) \n ’n’ goto the next name (i.e., the next file) \n ’q’ quit \n");
  printf("\n ");


  if(argc <= 1)
  {
     printf("No files entered !!\n");
     exit(-1);
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

     printf("file %s: ", argv[i]);
     printf("command: ");
     scanf(" %c", &command);


     while(command != 'q')
     {	
      

      if(command == 'c')
      {
          concatenateFile(argv[i]);
      }


      else if(command == 'd')
      {
	char destination[100];
        printf("Enter new destination:\n");
        scanf(" %[^\n]s",destination);
        duplicateFile(destination);
      }


      else if(command == 'r')
      {
        char fileName[100];
        printf("Enter new name:\n");
   	scanf(" %[^\n]s",fileName);
        renameFile(argv[i],fileName);

      }

      
      else if(command == 'u')
      {
        
	int ret = 0;
   	delete(ret,argv[i]);
	break;

      }


      else if(command == 't')
      {
	truncateFile(argv[i]);
      }


      else if(command == 'a')
      {
        char appFile[100];
        printf("Enter a file that you want to append:\n");
        scanf(" %[^\n]s",appFile);
	appendFile(argv[i], appFile);

      }


      else if(command == 'l')
      {
	
	listFile(argv[i]);
      }


      else if(command == 'm')
      {
        chmode(argv[i]);
      }


      else if(command == 'x')
      {
	 curTime(argv[i]);
	    
      }
  
      else if (command == 'n')
      {
        break;
      }
      printf("file %s: ", argv[i]);
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
