#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "mytoc.h"
#include <errno.h>

#define BUFLEN 1000

/*Function to concatenate two strings*/
char* concat(char* str1, char* str2)
{
  char* i, *j, *k;
  int len1 = tokenlen(str1,' ');
  int len2 = tokenlen(str2, ' ');
  char* string = (char*)malloc((len1+len2)*sizeof(char));
  k = string;
  for( i = str1; *i != '\0' ; i++, k++)
    {
    *k = *i;
    }
  for( j = str2; *j != '\0' ; j++, k++)
    {
     *k = *j;
    }
  *k = '\0';
  return string;
}

/*finds index for PATH variable in envp*/
int findPathIndex(char** envp){
  char ** courser;
  int counter = 0;
  for(courser = envp; *courser; courser++)
    {
      if(((*courser)[0] == 'P')&&((*courser)[1] == 'A')&&((*courser)[2]=='T')&&((*courser)[3]=='H'))
	{
	  return counter;
	}
      else
	{
	  counter++;
	}
    }
}

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

int is_builtin(char* command)
{
  if(strEq(command, "exit"))
    {
      exit(0);
    }
  else if(strEq(command, "cd"))
    {
      return 1;
    }
  return 0;
}

int execute_command(char** commandLine, char** envp)
{
  int status = 0;
  int index;
  char** pathVar;
  char** path;
  char* commandRead;
  char* pathConcat;
  if(commandLine[0][0] == '/')
    {
      status =  execve(commandLine[0],commandLine,envp);
      if(status == -1){
	return -1;
      }
      else return 0;
    }
  else
    {
      index = findPathIndex(envp);
      pathVar = mytoc(envp[index], '=');
      path = mytoc(pathVar[1], ':');
      commandRead = commandLine[0];
      commandRead = concat("/",commandRead);
      while(*path != '\0')
	{
	  pathConcat = concat(*path,commandRead);
	  commandLine[0] = pathConcat;
	  status = execve(pathConcat, commandLine, envp);
	  if(status !=  -1)
	    {
	      return 0;
	    }
	  path++;
	}
      if(status < 0)
	{
	  return 1;
	}
      }  
}


int main(int argc, char **argv, char **envp)
{
  setenv("PS1", "$ ",0);
  char* PS1 = getenv("PS1");
  int pid;
  int amount_read;
  char buffer[BUFLEN];
  char** commandLine;
  int status;
  while(1){
    write(1,getenv("PS1"), 2);
    amount_read = read(0,buffer,BUFLEN);
    if(amount_read == 0){
      exit(0);
    }
    commandLine = mytoc(buffer, ' ');
    if(is_builtin(commandLine[0]))
      {
	if(chdir(commandLine[1])!=0)
	  {
	    write(2, "Error while changing directory.",31);
	  }
	continue;
      }
    else
      {
	pid = fork();
	if(pid == 0)
	  {
	    status = execute_command(commandLine, envp);
	    if(status < 0)
	      {
		write(2,"Command finished with error number.\n",36);
		exit(1);
	      }
		else if(status > 0)
	      {
		write(2,"Command not found.\n",19);
		exit(1);
	      }
	    else
	      {
		exit(0);
	      }
	  }
	else if(pid < 0)
	  {
	    write(2,"Fork failed.\n",13);
	  }
	else
	  {
	    wait(NULL);
	  }
      }
  }
}


/*
int main(int argc, char **argv, char **envp)
{
  int index;
  int fullpath = 0;
  int amtRead;
  int pid;
  int status;
  char buf[BUFLEN];
  char s[2];
  char* err;
  char** command;
  char** path;
  char* error;
  char** pathVar;
  char* pathConcat;
  char* commandRead;
  while(1)
    {
      error = "Command not found.\n";
      err = "Program terminated with exit code\n";
      s[0] = '$';
      s[1] = ' ';
      write(1,s,2);
      amtRead = read(0,buf, BUFLEN);
      if(amtRead == 0){
	exit(0);
      }
      buf[amtRead-1] = '\0';
      command =  mytoc(buf,' ');
      if(strEq(command[0],"exit"))  //exit if you read exit
	{
	  break;
	}
      pid = fork();
      if(pid == 0)
	{
	  index = findPathIndex(envp);
	  pathVar = mytoc(envp[index],'=');
	  path = mytoc(pathVar[1],':');
	  commandRead = command[0];
	  if(commandRead[0] != '/'){              //setup the possible paths and the executable directory
	     commandRead = concat("/",commandRead);
	     fullpath = 1;
	  }
	  while((*path) != '\0')                  //try the mashup in every possible path
	    {
	      if(fullpath)
		{
		status = execve(pathConcat,command,envp);
		if(status != -1) break; 
		}
	      else
		{
		pathConcat = concat(*path,commandRead);
		command[0] = pathConcat;
		status = execve(pathConcat,command,envp);
		if(status != -1) exit(0);      
		path++;
		}
	    }
	  if(status < 0)                          //If you reach here command wasn't found
	    {
	      write(1, error, 20);
	    }
	  exit(0);
	}
      else
	{
	  wait(NULL);
	}
    }
}
 */
