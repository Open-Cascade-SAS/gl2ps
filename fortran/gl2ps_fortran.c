#include "gl2ps.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

/* #define FC_FUNC(name,NAME) name ## _ */

void string_f2c(char *string, long length, char *cstring);
void restore_string_f2c(char *string, long length);

FILE *fp=NULL;

void FC_FUNC(gl2psbeginpage, GL2PSBEGINPAGE)
  (char *title, GLint *format, GLint *sort,
   GLint *buffersize,
   char *filename, int *ierr,
   long n_title, long n_filename)
{
  char *ctitle, *cfilename;
  *ierr=0;

  /* open the file if still/already closed */
  if (fp == NULL) {
    if ((fp = fopen(cfilename, "wb")) == NULL) {
      perror(cfilename);
      *ierr=GL2PS_ERROR;
      return;
    }
  }

  ctitle = (char*)malloc((n_title+1)*sizeof(char));
  cfilename = (char*)malloc((n_filename+1)*sizeof(char));
  string_f2c(title, n_title, ctitle);
  string_f2c(filename, n_filename, cfilename);

  /* call gl2psBeginPage with reasonable values for option, colormode & c. */
  *ierr=gl2psBeginPage(ctitle, "gl2ps_f90", NULL, *format, 
		       *sort == 0 ? GL2PS_SIMPLE_SORT : *sort, 
		       GL2PS_DRAW_BACKGROUND | GL2PS_USE_CURRENT_VIEWPORT,
		       GL_RGBA, 0, NULL, 0, 0, 0, *buffersize, fp, cfilename);
  free(ctitle);
  free(cfilename);
}


void FC_FUNC(gl2psendpage, GL2PSENDPAGE)(int *ierr)
{
  *ierr=gl2psEndPage();
  if (fp != NULL) {
    fclose(fp);
    fp = NULL;
  }
}


/* add a null char terminator to a fortran string in a reasonable place */
void string_f2c(char *string, long length, char *cstring)
{
  char *p;

  strncpy(cstring, string, length);
  cstring[length]='\0';
  for(p=cstring+length-1; (*p == ' ' || *p == '\0') && p > cstring; p--);
  *(p+1)='\0';
}
