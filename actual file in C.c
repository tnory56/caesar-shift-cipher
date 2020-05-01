/* Project #4

 Project Description:

 In this project, you will implement three basic cryptography procedures for shift cipher.
 Cryptography refers to the use of encryption (or encoder) to convert plain text information into
 unintelligible gibberish (cipher text) for security purposes. A corresponding decryption
 algorithm (or decoder) will convert the cipher text back to the plain text with the correct
 decryption key. A code breaker tries to decode the cipher text without the key.
 Shift cipher is one of the simplest cryptography systems. It encrypts the plain text message by
 shifting each character for fixed number of characters down the relevant alphabet. This fixed
 number is called the encryption key. For example, consider the English alphabet, when the
 encryption key is 2, a, b, c, …, x, y, z will be shifted to c, d, e, …, z, a, b, respectively. A shift
 cipher with encryption key 2 will convert the plain text “project” into cipher text “rtqlgev”. The
 decoder in this case will be shifting each letter 2 position to the left, that is, replacing a, b, c, …,
 x,y,z in the cipher text by y, z, a, …, v, w, x, respectively. It suffices for a code breaker in this
 case to guess the value of the encryption/decryption key.
 You need to write a single program to perform these three basic cryptography procedures at the
 user’s choice. Assuming that a.out is the executable of your program:
 a.out 1 input output key encodes input file with key and write cipher text to output
 a.out 2 input output key decodes input file with key and write plain text to output
 a.out 3 input output breaks the cipher text input and write plain text to output
 The code breaker procedure tries all the possible key values and matches the words in the
 corresponding plain text with the words in a dictionary “mydictional.txt”. The key that produces
 the maximal number of matches will be considered as the key and will be used to generate the
 plain text file output.

 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define my_letters 72

int main (int argc, char *argv[])
{

    /*-------------------Declaration of the variables------------------------------------------*/

    FILE *input, *output, *dictionary;
    int i=FALSE, j=FALSE, k=FALSE, l=FALSE, v=FALSE;
    char ch, dict;
    char my_letter_array[my_letters];
    char *ptr, *library;
    int key, correct_key=FALSE, number_matched=0;
    int user_input;
    int counter=FALSE, matches=FALSE;
    int compare=FALSE, cnt=FALSE;

    if(argv[4] != NULL)
    {
        key = atoi(argv[4]);
    }
    if(argv[1] != NULL)
    {
        user_input = atoi(argv[1]);
    }

    /*-------------------Command Line Arguments------------------------------------------------*/

    if(argc < 4 || argc > 5)                                                                 // Checks to see if the usage is correct.
    {
        printf("\nUsage: (exectuable) (user_choice) (input_file) (output_file) (key_code)\n");
        printf("\n*****(key_code **only** if user_input is 1 or 2)*****\n");                // Prints this is the information if not inputed corectly.
        return(FALSE);
    }
    input = fopen(argv[2],"r");                                                              // Open the input file.
    if ((user_input < TRUE) || (user_input > 3))
    {
        printf("\nThat is not a valid encryption/decryption setting! (Must be between 1-3)\n");
        return(FALSE);
    }
    if(argv[4] == NULL && user_input != 3)                                                   //Makes sure that a key is entered if user_input is 1 or 2.
    {
        printf("\nA key value is needed in order to proceed (key = (0-72))\n");
        return(FALSE);
    }
    if ((key < FALSE || key > 72) && user_input != 3)                                        //Makes sure that the key is not a neg or greater than 72.
    {
        printf("\nA key value is needed in order to proceed (key = (0-72))\n");
        return(FALSE);
    }
    input = fopen(argv[2],"r");                                                              // Open the input file.
    if( input == NULL)                                                                      // Checks whether there is an input file.
    {
        printf("\nFile %s cannot open!\n", argv[2]);                                        // Prints this if not.
        return(FALSE);
    }
    output = fopen(argv[3], "w");                                                            // Opens the output file.
    if( output == NULL)                                                                     // Checks whether there is and output file.
    {
        printf("\nFile %s cannot open!\n", argv[3]);                                        // Prints this if not.
        return(FALSE);
    }
    dictionary = fopen("mydictional.txt", "r");                                              // Opens the dictionary file to check the words.
    if( dictionary == NULL)                                                                 // Checks whether there is a dictionary file.
    {
        printf("\nFile dictionary.txt cannot open!\n");                                     // Prints this if not.
    }

    /*------------------Make the 72-letter alphabet--------------------------------------------*/

    for(i=97; i<123; i++)
    {
        my_letter_array[counter++] = i;
    }
    for(i=65; i<91; i++)
    {
        my_letter_array[counter++] = i;
    }
    for(i=48; i<58; i++)
    {
        my_letter_array[counter++] = i;
    }
    my_letter_array[counter++] = ';';
    my_letter_array[counter++] = ':';
    my_letter_array[counter++] = ',';
    my_letter_array[counter++] = '.';
    my_letter_array[counter++] = '\'';
    my_letter_array[counter++] = '"';
    my_letter_array[counter++] = '(';
    my_letter_array[counter++] = ')';
    my_letter_array[counter++] = '\n';
    my_letter_array[counter++] = ' ';

    /*------------------Memory allocation of the pointers--------------------------------------------*/

    if (( ptr = (char *) malloc(sizeof(char))) == NULL)
    {
        printf("no memory ...\n");
        return(FALSE);
    }

    if (( library = (char *) malloc(sizeof(char))) == NULL)
    {
        printf("no memory ...\n");
        return(FALSE);
    }
    /*------------------Scan and print to output file for option 1-----------------------------------*/

    if(user_input == TRUE)
    {
        while ((fscanf(input, "%c", &ch) == TRUE) && (!feof(input)))
        {
            ptr[i++] = ch;
            for (k=FALSE; k<my_letters; k++)
            {
                if (ch == my_letter_array[k])
                {
                    if (k+key>(my_letters-1))                             //Encrypts the char by the key.
                    {
                        ch = my_letter_array[(k+key)%my_letters];        //If the key put the char past my_letter_array it will return to the start.
                        break;
                    }
                    else
                    {
                        ch = my_letter_array[k+key];                     //Else just increase the ch by the array.
                        break;
                    }
                }
            }
            fprintf(output, "%c", ch);                               //print each ch to the output.
            ptr = (char *) realloc(ptr, (i+1)*sizeof(char));
        }
        printf("\n\n******This is what is in the input_file:******\n\n");
        for (j=FALSE; j<i; j++)
        {
            printf("%c", ptr[j]);                                     //This is just to show what was scanned in to the ptr pointer.
        }
        printf("\n");
        free(ptr);
        printf("\n\n******The encryption has taken place******\n\n");
    }

    /*------------------Scan and print to output file for option 2-----------------------------------*/

    if(user_input == 2)
    {
        while ((fscanf(input, "%c", &ch) == 1) && (!feof(input)))
        {
            ptr[i++] = ch;
            for (k=FALSE; k<my_letters; k++)
            {
                if (ch == my_letter_array[k])
                {
                    if (k-key<FALSE)                                   //Decrypts the char by the key.
                    {
                        ch = my_letter_array[my_letters-abs(k-key)];    //If the key subtracts past the first array it will start from the end.
                        break;
                    }
                    else
                    {
                        ch = my_letter_array[k-key];                    //Else just decrease the ch by the array.
                        break;
                    }
                }
            }
            fprintf(output, "%c", ch);
            ptr = (char *) realloc(ptr, (i+1)*sizeof(char));
        }
        printf("\n\n******This is what is in the input_file:******\n\n");
        for (j=FALSE; j<i; j++)
        {
            printf("%c", ptr[j]);                                    //This was just to show what was scanned in to the ptr pointer.
        }
        printf("\n");
        free(ptr);
        printf("\n\n******The decryption has taken place******\n\n");
    }

    /*------------------Scan and print and determine the key that is needed to decifer the code----------*/

    i=FALSE, k=FALSE, j=FALSE;
    if(user_input == 3)
    {
        printf("%s%11s\n", "Key", "Matches");
        for(key=1; key<my_letters; key++)                                         //This changes the key from 1 to 71.
        {
            input = fopen(argv[2], "r");                                        //Opens the input file to read again.
            while ((fscanf(input, "%c", &ch) == TRUE) && (!feof(input)))      //Scans the input file until the end of file.
            {
                for (k=FALSE; k<my_letters; k++)                       //Same algorithm as the user_input 2 for shifting the ch.
                {
                    if (ch == my_letter_array[k])
                    {
                        if (k-key<FALSE)
                        {
                            ch = my_letter_array[my_letters-abs(k-key)];
                            break;
                        }
                        else
                        {
                            ch = my_letter_array[(k-key)];
                            break;
                        }
                    }
                }
                switch(ch)                                            //If any ch is equal to the below statements make it a string.
                {
                    case ';': case ':': case ',': case '.': case '\'': case '"': case '(': case ')': case '\n': case ' ':
                    {
                        ptr[j] = '\0';
                        dictionary = fopen("mydictional.txt", "r");      //Keep opening the dictionary.
                        while ((fscanf(dictionary, "%c", &dict) == TRUE) && (!feof(dictionary))) //until the end of file.
                        {
                            if(dict == '\n')                           //if the ch is \n line make the library string.
                            {
                                library[i++] = '\0';
                                compare = strcmp(ptr, library);         //Compare the library string and the ptr string.
                                if (compare == FALSE)                  //This checks if they are the same and increments the amount of mathces.
                                {
                                    matches++;
                                    break;                              //If it matches break out of the loop.
                                }
                                i=FALSE;                              //Reset i to 0 so that it will overwrite the data.
                            }
                            else
                            {
                                library[i++] = dict;                    //If the dict is not a newline char make the library string.
                            }
                            library = (char *) realloc(library, (strlen(library)+1));  //Reallocate the memory to library.
                        }
                        j=-1;                                             //Reset i to -1 so that it will overwrite the data.
                        fclose(dictionary);                               //Close the dictionary so no seg faults.
                    }
                    default:
                    {
                        ptr[j] = ch;                                    //If the ch is not a punctuation make the ptr string.
                        j++;
                        ptr = (char *) realloc(ptr, (strlen(ptr)+1));   //Reallocate the memory to ptr.
                    }
                }
            }
            printf("%-2d     %-2d\n", key, matches);                        //Show what the matches are from the key.
            if (matches > number_matched)                                   //If the matches is greater than the number_matched.
            {
                number_matched = matches;                                    //Finds the largest number of matches.
                correct_key = key;                                           //And then tells what the correct_key is.
            }
            matches=FALSE;                                                  //Set matches to 0.
            fclose(input);                                                  //Close the input file.
        }
        printf("\nCorrect Key is %d\n", correct_key);                                 //Tell the user the correct key.
    }

    //free(ptr);
    free(library);
    fclose(input);
    fclose(output);
    fclose(dictionary);

    return FALSE;
}

