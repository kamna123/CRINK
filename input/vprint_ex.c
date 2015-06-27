#include <stdio.h>
#include <stdarg.h>

char buffer[80];
void vspfunc(int i, char *format, ...)
{
   va_list args;
   if(i>4){
   va_start(args, format);
   vprintf(format, args);
   va_end(args);
   }
   //return(ret);
}

int main()
{
   int i = 5;
   char str[50] = "tutoriaspoint.com";
   char q[6]="v5";
   i=atoi(q+1);
   vspfunc(i,"%s %d %s\n","hi", i, str);
   //printf("%s\n", buffer);
   vspfunc(i,"%s %d %s\n","bye", i, str);
   //printf("%s\n", buffer);
    printf("%s\n", "hello");   
   return(0);
}
