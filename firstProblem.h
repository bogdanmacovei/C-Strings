/*
* Author: BOGDAN MACOVEI
* File: firstProblem of 3rd Project
* Date: 28th of December (2016)
* Status: 100% completed
*/

#include <stdio.h>
#include <stdlib.h>

/// This is a general function to print a file
///     this function print each line on console
///     with a tab ('\t')

void showAFile(FILE *file)
{
    char ch;

    printf("\t");

    while(!feof(file))
    {
        if(ch=='\n')
            printf("\t");

        fscanf(file, "%c", &ch);

        if(ch == 0)
            break;

        printf("%c", ch);
    }

    fclose(file);
}

/// This is an aux-function, all of the characters in range ['A', 'Z']
///     are replaced with an character from ['a', 'z'], using
///     f(X) = X + 32

void lower_string(char *str)
{
    int n = strlen(str), i;

    for(i = 0; i < n; ++i)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

/// This is also an aux-function, all of the characters that are not in range ['a', 'z']
///     are deleted

void deleteNotAlpha(char *str)
{
    int n = strlen(str), i;

    char str_aux[n];

    for(i = 0; i < n; ++i)
    {
        if(str[i] < 'a' || str[i] > 'z')
        {
            strcpy(str_aux, str + i + 1);
            strcpy(str + i, str_aux);
            n--;
            i--;
        }
    }
}

/// A valid string (in this problem) is a string that contains just characters
///     in range ['a', 'z']

short int isValidString(char *str)
{
    int n = strlen(str), i;

    if(n == 0)
        return 0;

    for(i = 0; i < n; ++i)
    {
        if(str[i] < 'a' || str[i] >= 'z')
            return 0;
    }

    return 1;
}

/// 1. This is the first function for this problem
///     that makes all of the file strings
///         a) to contains just characters in range ['a', 'z'],
///         b) that are separated by spaces.

/// To solve this problem, I used those two aux-functions
///     (lowerString and deleteNotAlpha)

void lowerTextFromFile()
{
    FILE *in = fopen("date.in", "r");
    FILE *out = fopen("date.out", "w");

    while(!feof(in))
    {
        char str[101], ch;

        fscanf(in, "%s", str);

        lower_string(str);
        deleteNotAlpha(str);

        if(isValidString(str))
            fprintf(out, "%s ", str);

        if(feof(in))
            break;
    }

    fclose(in);
    fclose(out);
}

/// 2. Find and replace function:
///     find firstStr in text, and replace firstStr with replaceStr
/// This function is not case sensitive.

void findAndReplace(char *firstStr, char *replaceStr)
{
    FILE *in = fopen("date.in", "r");
    FILE *out = fopen("date.out", "w");

    while(!feof(in))
    {
        char str[21], ch;

        fscanf(in, "%s", str);
        fscanf(in, "%c", &ch);

        if(feof(in))
            break;

        char aux_str[21], aux_firstStr[21];

        // I make a copy for each string

        strcpy(aux_str, str);
        strcpy(aux_firstStr, firstStr);

        // For each copy I'll use the lower_string - aux-function

        lower_string(aux_str);
        lower_string(aux_firstStr);

        // I verify if aux_firstStr is in aux_str

        if(strstr(aux_str, aux_firstStr))
        {
            int i, j;

            // and, if it is,
            // I will keep in top the index appearance,
            // and in last := the length of this string

            for(i = 0; i < strlen(aux_str); ++i)
            {
                if(aux_str[i] == aux_firstStr[0])
                {
                    short int ok = 1;

                    for(j = 0; j < strlen(aux_firstStr); ++j)
                        if(aux_str[i+j] != aux_firstStr[j])
                            ok = 0;

                    if(ok)
                    {
                        int top = i, last = strlen(aux_firstStr);

                        // Now, I know that the replaceStr is between top and last

                        for(j = 0; j < top; ++j)
                            fprintf(out, "%c", str[j]);

                        fprintf(out, "%s", replaceStr);

                        for(j = last; j < strlen(str); ++j)
                            fprintf(out, "%c", str[j]);

                        fprintf(out, "%c", ch);
                    }
                }
            }
        }

        else
        {
            fprintf(out, "%s", str);
            fprintf(out, "%c", ch);
        }
    }

    fclose(in);
    fclose(out);

}
