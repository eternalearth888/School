#include <stdio.h>
#include <stdlib.h>

/* This function reads a single line from a stream (file or keyboard)
 * storing it in a dynamically allocated string. 
 * 
 * RETURN: A pointer to the dynamically allocated string containing the line
 *         NULL under several conditions, including reaching end of file.
 */

char *fgetline(FILE *fp)
{
     char *p;     // pointer to buffer
     int length;  // length of string, not counting NUL
     int bufsize; // length of buffer
     int c;       // one-character buffer (is int to hold status values)
     
     // Do not attempt to read from either standard output device   
     if ( (stdout==fp) || (stderr==fp) )
        return NULL;
     
     // Check if end of file has already been reached.
     if (fp) // fp is assumed to be a file.
        if (feof(fp))
           return NULL;
           
     // Read from stdin (keyboard) if fp is NULL  
     if (!fp) 
        fp = stdin;

     // Allocate initial buffer to just hold the NUL terminator
     p = NULL;
     bufsize = 1;
     length = 0;
     p = (char *) realloc(p, bufsize*sizeof(char));
     if (!p)
        return NULL; // Allocation failed
     
     while (1) // Will exit via RETURN
     {
        c = getc(fp);
        if ((EOF==c)||('\n'==c))
           return p; // Read operation complete. Do not store EOL/EOF
        
        if ( !((length+1)<(bufsize-1)) ) // Grow buffer if needed
        {
           bufsize <<= 1; // Double the buffer size
           p = (char *) realloc(p, bufsize*sizeof(char));
           if (!p)
              return NULL; // Allocation failed, data may be lost
        }
        
        p[length++] = c; // Add the new character to the string
        p[length] = 0;   // Regenerate the NUL terminator
     }
           
     return NULL; // Should never get here
}

/* The first command line argumant is the file to read from while
 * the second is the file to write to. If the second file is omitted
 * the output goes to the console. The first argument is required.
 *
 * The program prompts the user for a string to prepend to each line.
 * It then outputs the line preceded by a line number and the string.
 */
 
int main(int argc, char *argv[])
{
  FILE *fp_i, *fp_o;  
  int lines;
  char *p, *s;
  int i;
  
  // Echo command line to screen
  printf("COMMAND LINE:");
  for (i = 0; i < argc; i++)
      printf(" %s", argv[i]);
  printf("\n");
  
  // Open input file
  if (argc < 2) // No command line arguments provided.
  {
     printf("ABORT - Input file must be specified.\n");
     exit(EXIT_FAILURE);
  }
  fp_i = fopen(argv[1], "rt");
  if (!fp_i) // Input file failed to open.
  {
     printf("ABORT - Failed to open input file <%s>.\n", argv[1]);
     exit(EXIT_FAILURE);
  }

  // Open output file
  if (argc < 3) // No output file specified on command line.
  {
     fp_o = stdout;
  }
  else
  {
     fp_o = fopen(argv[2], "wt");
     if (!fp_o) // Output file failed to open, use stdout.
     {
        printf("WARNING - Failed to open output file <%s>.\n", argv[2]);
        printf("          USING stdout INSTEAD.\n");
        exit(EXIT_FAILURE);
     }
  }
  
  // Prompt user for string prefix.
  printf("\n");
  printf("String to prefix lines with: ");
  s = fgetline(stdin);
  printf("\n");
  if (!s)
  {
     printf("ABORT - Failed to allocate prompt string.\n");
     exit(EXIT_FAILURE);
  }

  // Process input one line at a time  
  for (lines = 0; p = fgetline(fp_i); lines++)
  {
      fprintf(fp_o, "%5i: %s%s\n", lines, s, p);
      free(p);
  }

  free(s); // Free the prompt string.
  fclose(fp_i);
  fclose(fp_o);
  
  printf("\n");
  printf("Hit RETURN to exit:");
  getc(stdin); 

  return 0;
}
