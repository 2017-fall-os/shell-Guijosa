#include <stdlib.h>

/* Function that copies a string to a certain adress sepcified by the destination pointer*/
void strCopy(char* from, char* destination, char delim)
{
  char* fromPointer, *toPointer;
  fromPointer = from;
  toPointer = destination;
  while((*fromPointer != delim) && (*fromPointer != '\0') && (*fromPointer != '\n')) //while there is a current token
    {
      *toPointer = *fromPointer; //copy that token
      toPointer++;
      fromPointer++;
    }
  *toPointer = '\0'; //set the copy's last element to o terminator
  return;
}

/* Function that counts the lenght of a token, given a delimiter*/
int tokenlen(char* tokenBegin, char delim)
{
  char* strPointer;
  int counter;
  for(strPointer = tokenBegin; (*strPointer != delim) && (*strPointer != '\0'); strPointer++);
  counter = strPointer - tokenBegin + 1;
  return counter;
}

/*Funtion to count thenumber of tokens on a string in accordance to the given delimiter*/
int tokenCount(char* str, char delim)
{
  int counter = 0;
  int tokenBool = 0;
  char* strPointer;
  for(strPointer = str; *strPointer != '\0'; strPointer++) //go through the string
    {
      if(*strPointer == delim) //if you find a delimiter
	{
	  if(tokenBool)  // if you are on a token
	    {
	      tokenBool = 0; //mark that you are not on one now
	    }
	}
      else //if you find a char
	{
	  if(!tokenBool) //if you are not on a token
	    {
	      tokenBool = 1; //mark you are now on one
	      counter++; //count one more token
	    }
	}
    }
  return counter;
}

/*Function to tokenize a given string, in accordance to a given delimiter*/
char** mytoc(char* str, char delim)
{
  char* strPointer, *currentTokenBegin;
  int numTokens = tokenCount(str,delim);  //count tokens
  numTokens++;
  int tokenBool = 0, currentTokenLen = 0, currTok  = 0;
  char** tokenVec = calloc(numTokens,sizeof(char*)); // allocate mem for the vector
  tokenVec[numTokens-1] = (char *)0; //set las place of vetor to 0 terminator
  for(strPointer = str; *strPointer != '\0'; strPointer++) // go through string
    {
      if(*strPointer == delim) //if you find a delim
	{
	  if(tokenBool) //if on a token 
	    {
	      tokenBool = 0; //mark you are in none now
	    }
	}
      else // if thou find a character
	{
	  if(!tokenBool)//if you are not on a token
	    {
	      tokenBool = 1;// mark you are now on a token
	      currentTokenBegin = strPointer; //point to the beggining of said token
	      currentTokenLen = tokenlen(currentTokenBegin,delim); //get length of said token
	      tokenVec[currTok] = (char*)malloc(currentTokenLen*sizeof(char)); // allocate mem for said token
	      strCopy(currentTokenBegin,tokenVec[currTok],delim); //copy token
	      currTok++; //point to a next place in token vector.
	    }
	}
    }
  return tokenVec;
}
