 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>  
 #include <ctype.h>

char* strchrt(char* str,char ch){ 
  if(*str == ch)
    return str;

  return *str ? strchrt(++str,ch) : NULL;
}

int main(int argc, char *argv[]) 
{
 putc(*strchrt("America",'c'),stdout);
  
} 