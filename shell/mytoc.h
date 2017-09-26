#ifndef  mytoc_Included

#define  mytoc_Included

int tokenlen(char* str, char delim);

int tokenCopy(char* from, char* to, char delim);

int tokenCount(char* str, char delim);

char** mytoc(char* str, char delim);

#endif
