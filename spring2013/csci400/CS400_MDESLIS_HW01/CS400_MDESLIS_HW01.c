/*********************
* AUTHOR: MARIA DESLIS
* CSCI400 BAHN SPRING 2013
* HWO1
**********************/

#include <stdio.h>
#include <stdlib.h>

void fileStats(FILE *file) {
  int countChar = 0;
  int countLine = 1;
  int countSpace = 0;
  int countNum = 0;
  int countElse = 0;
  int countLetter = 0;
  int countUpper = 0;
  int countLower = 0;

  int ch; //one-character buffer (is in to hold status value)

  while ( (ch = fgetc(file)) != EOF ) 
  {
       // COUNTING INPUT FILE
       // ASCII LETTERS
       if ((ch >= 'a') && (ch <= 'z')) 
       {
         countLetter++;
         countLower++;
      }
      
       if ((ch >= 'A') && (ch <= 'Z')) 
       {
         countLetter++;
         countUpper++;
       }
      
       // ASCII NUMBERS
       if ((ch >= '0') && (ch <= '9')) 
       {
         countNum++;
       }
      
       // ASCII SYMBOLS
       if ((ch >= '{') && (ch <= '~')) 
       {
         countElse++;
       }
      
       if ((ch >= '[') && (ch <= '_')) 
       {
         countElse++;
       }
      
       // ASCII PUNCTUATIONS
       if ((ch >= '!') && (ch <= '/')) 
       {
         countElse++;
       }
    
       if ((ch >= ':') && (ch <= '?')) 
       {
         countElse++;
       }
      
       // ASCII SPACE
       if (ch == ' ') 
       {
         countSpace++;
       }
     
       // ASCII LINE 
       if (ch == '\n') 
       {
         countLine++;
       }
     countChar++;
  }

  printf("# CHARACTERS: %d\n", countChar);
  printf("# LINES: %d\n", countLine);
  printf("# ELSE: %d\n", countElse);
  printf("# SPACES: %d\n", countSpace);
  printf("# UPPER CASE: %d\n", countUpper);
  printf("# LOWER CASE: %d\n", countLower);
  printf("# LETTERS: %d\n\n", countLetter);
}

char *LoadKey(char *cipher) {
  char *user; // cipher that the user gives us. pointer to the buffer
  int length; // length of string, not counting NULL
  int buffsize; // length of buffer
  int ch; //one-character buffer (is in to hold status value)


  char *mines; // default user for when the user does not input anything
  mines = (char *)"Colorado School of Mines";
  int i;
  i = 0;

  // Allocate initial buffer to just hold the NULL terminator
  user = NULL;
  length = 0;
  buffsize = 1;
  user = (char *) realloc(user, buffsize*sizeof(char));

  // Allocation failed
  if (!user) 
  {
    return NULL;
  }

  // Will exit via RETURN
  while (1) { 
    ch = cipher[i]; // Going through each position in the string

    if ( ch == '\0' ) { // \0 tells us we have reached the end of the array of our string of characters
       return user; // Read operation complete. Do not store EOL/EOF
    }

    // If it's not a letter, skip over it
    while ( !((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) ) {
      i++;
      ch = cipher[i];

      if ( ch == '\0') {
        return user;
      }
    }

    // If it's a lower case letter, make it uppercase
    if ( (ch >= 'a') && (ch <= 'z')) {
      ch = ch - 32;
    }


    if ( !((length+1) < (buffsize-1)) ) // Grow buffer if needed
    {
       buffsize <<= 1; // Double the buffer size
       user = (char *) realloc(user, buffsize*sizeof(char));
       if (!user)
          return NULL; // Allocation failed, data may be lost
    }
    
    user[length++] = ch; // Add the new character to the string
    user[length] = 0;   // Regenerate the NUL terminator
    i++;
  }
  
  free(mines); // Freeing the prompt string

  return NULL;  // THIS IS BAD
}


int main(int argc, char * argv[]) {
  //ECHO COMMAND LINE + ARGUMENTS TO SCREEN
  printf("COMMAND LINE: ");

  // DECLARING VARS FOR ECHOING TO COMMAND LINE
  int i;

  for (i = 0; i < argc; i++) {
      printf(" %s", argv[i]);
  }

  printf("\n\n");
  
  
  // ERROR Checking Arguments
  if (argc < 2) {
    printf("ABORT:\n");
    printf(" MINIMUM OF ONE COMMAND ARG REQUIRED:  input file\n");
    printf(" MAXIMUM OF FOUR COMMAND ARG:input file, output file, cipher key, mode\n");
    exit(EXIT_FAILURE);
  } 


  // DECLARE INPUT AND OUTPUT FILES
  FILE *f_in, *f_out;

  // INPUT FILE ARGUMENT 1
  // ERROR CHECK to see if there is an argument for the input file in the command line
  if (argc < 2)  {
    printf("ABORT - Input file must be specified first.\n");
    exit(EXIT_FAILURE);
  }

  // OPEN INPUT FILE
  f_in = fopen(argv[1], "rt");

 // ERROR CHECK if input file failed to open
 if (!f_in) {
    printf("ABORT - Failed to open input file <%s> \n", argv[1] );
    exit(EXIT_FAILURE);
  } 

  // CALLING STATS FUNCTION FOR INPUT FILE
  printf("STATS FOR INPUT FILE:\n");
  fileStats(f_in);

  // OUTPUT FILE ARGUMENT 2
  // ERROR CHECK if there is no argument for the output file, print to screen
  if (argc < 3) {
    f_out = stdout;
  } else {
    // OPEN OUTPUT FILE
    f_out = fopen(argv[2], "wt");
      
    // ERROR CHECK if output file failed to  open
    if (!f_out) {
      printf("WARNING - Failed to open output file <%s>.\n", argv[2]);
      printf("        USING stdout INSTEAD.\n");
      exit(EXIT_FAILURE);
    }
  }

  // CALLING STATS FUNCTION FOR OUTPUT FILE
  printf("STATS FOR OUTPUT FILE:\n");
  fileStats(f_out);

  // CIPHER KEY ARGUMENT 3

  // DECLARING VARS FOR CIPHER KEY
  char *p;
  char *key;

  // ERROR CHECK if there is no cipher key give it Colorado School of Mines
  if (argc < 4) {
    p = LoadKey(key);
  } else {
    free (p);
    key = argv[3];
    p = LoadKey(key);
  }

  // ERROR CHECK if there is no pointer to buffer the cipher, fail to allocate cipher key
  if (!p) {
    printf("ABORT - Failed to create and allocate cipher key<%s>.\n", argv[3]);
    exit(EXIT_FAILURE);
  }


/*
  // MODE (ENCRYPTION OR DECRYPTION) ARGUMENT 4

  // DECLARING VARS FOR MODE
  // SO CONFUSED!
*/


  //PARAMETERS USED
  printf("PARAMETERS THAT WILL BE USED:\n");
  printf("Input File: %s\n", argv[1]);
  printf("Output File: %s\n", argv[2]);
  printf("Cipher: ");
  puts(p);

  //FREE THE CIPHER
  free(p);

  //CLOSE INPUT + OUTPUT FILE
  fclose(f_in);
  fclose(f_out);

  // CLOSING THE PROGRAM
  printf("\n")  ;
  printf("ENTER/RETURN to EXIT");
  getc(stdin);
  return 0;
}
