/*
* Author: BOGDAN MACOVEI
* File: secondProblem of 3rd Project
* Date: 07th of January (2017)
* Status: 100% completed
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/// I define the general string length at LEN = 501
///     and the type boolean := unsigned short int

#define LEN 501
#define boolean unsigned short int

/// To complete the boolean type,
///     I define an enumeration with
///     false := 0 and true := 1

enum
{
    false, true
};

/// This is an aux-function that returns
///     the first appearance of t-string in s-string
///     (like char *p = strstr(s, t))

int findStringPosition(char *s, char *t)
{
    int n = strlen(s);
    int i, j;

    for(i = 0; i < n; ++i)
        if(s[i] == t[0])
        {
            int m = strlen(t), nr = 0;

            for(j = 0; j < m; ++j)
                if(s[i+j] == t[j])
                    nr++;

            if(nr==m)
                return i;
        }

    return -1;
}

/// 1. This is the first operation on binary file "file.txt"
///     that swap two strings with the same length
///     this function retains a line from the text-file, but not the entire string.

/// This function return true(1) if the operation was made, and false(0) otherwise

boolean swapString(char *strFirst, char *strSecond)
{
    FILE *in = fopen("file.txt", "r+b");

    // I use two boolean variables to know if is the end of file
    //      and if the operation was made

    boolean isEof = false;
    boolean globalFind = false;

    while(!feof(in))
    {
        // I retain just a lineText

        char lineText[LEN];

        fgets(lineText, LEN, in);

        if(feof(in))
            isEof = true;

        // I put the file pointer at the beginning of the current line

        fseek(in, ftell(in) - strlen(lineText), SEEK_SET);

        if(isEof)
            break;

        // I re-read the lineText with fread function from binary files

        fread(lineText, strlen(lineText) * sizeof(char), 1, in);

        // If I found the str( First or Second) in lineText
        //      I make globalFind = true to return a true value
        //      I retain the current position (ftell(in)),
        //          because I change this value in this if-statement
        //      using findStringPosition-aux-function, I retain in pos_str
        //          the position of the first appearance of str in lineText
        //      I put the pointer before this word, to rewrite the other word

        if(strstr(lineText, strFirst))
        {
            globalFind = true;

            int current_position = ftell(in);
            int pos_str = findStringPosition(lineText, strFirst);

            fseek(in, ftell(in) - strlen(lineText) + pos_str, SEEK_SET);
            fputs(strSecond, in);
            fseek(in, current_position, SEEK_SET);
        }

        // and here is the same explication

        if(strstr(lineText, strSecond))
        {
            globalFind = true;

            int current_position = ftell(in);
            int pos_str = findStringPosition(lineText, strSecond);

            fseek(in, ftell(in) - strlen(lineText) + pos_str, SEEK_SET);
            fputs(strFirst, in);
            fseek(in, current_position, SEEK_SET);
        }
    }

    free(in);

    return globalFind;
}

/// 2. This is the second operation on this binary file
///     that find a specified word in file and replace this with another string

/// This operation is similar with swap-operation

void findAndReplaceWords(char *strFind, char *strReplaceWith)
{
    FILE *in = fopen("file.txt", "r+b");

    boolean isEof = false;

    while(!feof(in))
    {
        char lineText[LEN];

        fgets(lineText, LEN, in);

        if(feof(in))
            isEof = true;

        fseek(in, ftell(in) - strlen(lineText), SEEK_SET);

        if(isEof)
            break;

        fread(lineText, strlen(lineText) * sizeof(char), 1, in);

        if(strstr(lineText, strFind))
        {
            int current_position = ftell(in);
            int pos_str = findStringPosition(lineText, strFind);

            fseek(in, ftell(in) - strlen(lineText) + pos_str, SEEK_SET);
            fputs(strReplaceWith, in);
            fseek(in, current_position, SEEK_SET);
        }
    }

    free(in);
}

void doublingWords(char *str)
{
    FILE *in = fopen("file.txt", "r+b");

    boolean isEof = false;

    int pos = 0;
    int text_pos = 0;

    while(!feof(in))
    {
        char lineText[LEN];

        fgets(lineText, LEN, in);

        if(feof(in))
            isEof = true;

        fseek(in, ftell(in) - strlen(lineText), SEEK_SET);

        if(isEof)
            break;

        fread(lineText, strlen(lineText) * sizeof(char), 1, in);

        char copyLineText[LEN];
        strcpy(copyLineText, lineText);

        char *word = strtok(lineText, " .,!=-?{}()`'\n");

        int globalCurrentPos = ftell(in);

        while(word)
        {
            if(!strcmp(word, str))
            {
                // I'll double the word str in this line

                int current_pos = ftell(in);
                int pos_str = findStringPosition(copyLineText, str);

                pos_str = ftell(in) - strlen(copyLineText) + pos_str;

                fseek(in, pos_str + strlen(word) + 1, SEEK_SET);

                fputs(copyLineText + (current_pos - strlen(copyLineText) + pos_str), in);
                fputc(0, in);
            }
            word = strtok(NULL, " .,!=-?{}()`'\n");
        }

        /*
        while(word)
        {
            pos += 1;
            text_pos += 1;

            fseek(in, pos + strlen(word), SEEK_SET);
            fputs(copyLineText + text_pos - 1, in);

            pos += 2 * strlen(word) + 1;
            text_pos += strlen(word);

            word = strtok(NULL, " ");
        }*/
    }

    fclose(in);
}

/// 4. This is the 4th operation on this binary-file
///     that encode the file using the next two rules:
///         a) if the current char is a vowel,
///             then the current char will be next consonant and
///         b) if the current char is a consonant,
///             then the current char will be previous character

void file_encoding()
{
    FILE *in = fopen("file.txt", "r+b");

    while(!feof(in))
    {
        char str[21];
        int i;

        fscanf(in, "%s", str);

        if(feof(in))
            break;

        for(i = 0; i < strlen(str); ++i)
            if(strchr("aAeEiIoOuU", str[i]))                        // if it is vowel
            {
                int current_poz = ftell(in);
                fseek(in, ftell(in) - strlen(str) + i, SEEK_SET);
                fputc(str[i] + 1, in);
                fseek(in, current_poz, SEEK_SET);
            }
            else                                                    // if it is consonant
            {
                int current_poz = ftell(in);
                fseek(in, ftell(in) - strlen(str) + i, SEEK_SET);
                fputc(str[i] - 1, in);
                fseek(in, current_poz, SEEK_SET);
            }
    }

    fclose(in);
}
