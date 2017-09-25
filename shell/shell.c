include <unistd.h>
include <mytoc.h>

#define BUFLEN 1000

/*Function to compare two strings for equality*/
int strEq(char* str1, char* str2)
{
  char* iterator;
  char* iterator2 = str2;
  for(iterator = str1; *iterator != '\0'; iterator++)
    {
      if(*iterator == *iterator2){
	iterator2++;
      }
      else{
	return 0;
      }
    }
  return 1;
}

char* findPath(char* cmd, char* path)
{
  int i;
  char** paths = mytoc(path,':');
  char* iterator;
  char* iterator2;
  char** directories;
  char* directory;
  for(iterator = path; iterator ; iterator = iterator++)
    {
      directories = mytoc(iterator,'/'); 
      for(iterator2 = directories; iterator2 ; iterator2++)
	{
	  directory = iterator2;
	  if(strEq(directory,cmd)
	    {
	      return iterator;
	    }
	}
    }
      return "0";
}


int main(int argc, char **argv, char **envp)
{
  int pid;
  int status;
  char buf[BUFLEN];
  char s[2];
  char err[36]
  char **command;
  char* path
  char error[18]
  while(1)
    {
      error = "Command not found."
      err = "Program terminated with exit code";
      s[0] = '$';
      s[1] = ' ';
      write(1,s,2);
      amtRead = read(0,buf, BUFLEN);
      for(i = 0; i < amtRead; i++)
	{
	 command =  mytoc(buf," ");
	 if(strEq(command[0],"exit"))
	   {
	     break;
	   }
	 path = findPath(command[0]);
	 if(*path == '0')
	   {
	     write(1,error,18);
	     continue;
	   }
	 pid = fork();
	 if(pid == 0)
	   {
	     status = execve(path,command,envp);
	     if(status < 0)
	       {
	        write(1, err, 36);
	       }
	   }
	 else
	   {
	     wait();
	   }
	}
    }
}
