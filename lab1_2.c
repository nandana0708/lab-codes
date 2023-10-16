//count no. of lines and chars in a file

#include<stdio.h>
#include<stdlib.h>
int main(){
 FILE *fp;
 char filename[100];
 char c;
 int lines=0, chars=0;
 
 printf("file name: ");
 scanf("%s", filename);
 fp = fopen(filename,"r");
 if (fp == NULL){
  printf("file not found");
  exit(0);
 }
 c = fgetc(fp);
 while(c!=EOF){
  chars++;
  if(c == '\n'){
   lines++;
  }
  c = fgetc(fp);
 }
 printf("no. of chars: %d\n", chars);
 printf("no. of lines: %d\n", lines);
 fclose(fp);
 return 0;
}

//always remember to use fgetc not fgets.
