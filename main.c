#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "menus.h"
#include "firstProblem.h"
#include "secondProblem.h"

#include <stdio.h>

void refresh()
{
    system("cls");
}

int main()
{
    initialSet();

    int option;
    int contorPosition = 0;
    char optionChar;

    do
    {
        hello();

        char chPosition = getche();

        if(chPosition == 80)
            contorPosition++;
        else
            if(chPosition == 72)
                contorPosition--;

        if(contorPosition < 0)
            contorPosition = 1;

        if(contorPosition >= 7)
            contorPosition = 7;

        while(contorPosition == 1)
        {
            system("cls");
            Menu_option1();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 11;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 2)
        {
            system("cls");
            Menu_option2();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 12;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 3)
        {
            system("cls");
            Menu_option3();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 21;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 4)
        {
            system("cls");
            Menu_option4();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 22;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 5)
        {
            system("cls");
            Menu_option5();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 23;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 6)
        {
            system("cls");
            Menu_option6();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 24;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        while(contorPosition == 7)
        {
            system("cls");
            Menu_option7();

            optionChar = getche();

            if(optionChar == 13)
            {
                option = 3;
                goto option;
            }
            else
            {
                option = 15;
                break;
            }
        }

        //printf("\n\n\n Your option: ");
        //scanf("%d", &option);

        option:
        switch(option)
        {
            case 11:
                refresh();
                printf("\n\n\t Your option: Lowercase words separated by spaces from a file");
                printf("\n\n\n The file input is: \n\n\n");

                FILE *in = fopen("date.in", "r");
                showAFile(in);
                fclose(in);

                printf("\n\n\n The result is: \n\n\n");
                lowerTextFromFile();

                FILE *in2 = fopen("date.out", "r");
                showAFile(in2);
                fclose(in2);

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            case 12:
                refresh();

                printf("\n\n\t Your option: Find and replace");
                printf("\n\n\n The file input is: \n\n\n");

                char firstString[21], replaceString[21];

                FILE *in3 = fopen("date.in", "r");
                showAFile(in3);
                fclose(in3);

                printf(" Find: ");
                scanf("%s", firstString);

                printf(" Replace with: ");
                scanf("%s", replaceString);

                findAndReplace(firstString, replaceString);

                printf("\n\n The result is: \n\n");

                FILE *in4 = fopen("date.out", "r");
                showAFile(in4);
                fclose(in4);

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            case 3:
                refresh();
                printf("\n\n\tThe program was closed\n\n");
                break;

            case 21:
                refresh();

                printf("\n\n\t Your option: Swap words with the same length");
                printf("\n\n\n The file input is: \n\n\n");


                FILE *file1 = fopen("file.txt", "r");
                showAFile(file1);
                fclose(file1);

                char firstStr[21], secondStr[21];

                int numb_error = 0;

                do
                {
                    if(numb_error)
                        printf("\n Please reenter two string with the same length!\n\n");

                    printf(" First string: ");
                    scanf("%s", firstStr);

                    printf(" Second string: ");
                    scanf("%s", secondStr);

                    numb_error++;
                }
                while(strlen(firstStr) != strlen(secondStr));

                short int isFind = swapString(firstStr, secondStr);

                if(!isFind)
                    printf("\n\n The result is: \n\n These words were not find in this file");

                else
                {
                    printf("\n\n The result is: \n\n");

                    FILE *file2 = fopen("file.txt", "r");
                    showAFile(file2);
                    fclose(file2);
                }

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            case 22:
                refresh();

                printf("\n\n\t Your option: Find and replace and change the file");
                printf("\n\n\n The file input is: \n\n\n");


                FILE *file3 = fopen("file.txt", "r");
                showAFile(file3);
                fclose(file3);

                char findStr[21], replaceWithStr[21];

                numb_error = 0;

                do
                {
                    if(numb_error)
                        printf("\n Please reenter two string with the same length!\n\n");

                    printf(" Find string: ");
                    scanf("%s", findStr);

                    printf(" Replace with string: ");
                    scanf("%s", replaceWithStr);

                    numb_error++;
                }
                while(strlen(findStr) != strlen(replaceWithStr));

                findAndReplaceWords(findStr, replaceWithStr);

                printf("\n\n The result is: \n\n");

                FILE *file4 = fopen("file.txt", "r");
                showAFile(file4);
                fclose(file4);

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            case 23:
                refresh();

                printf("\n\n\t Your option: Doubling word");
                printf("\n\n\n The file input is: \n\n\n");


                FILE *file5 = fopen("file.txt", "r");
                showAFile(file5);
                fclose(file5);

                char double_str[21];

                printf("\n\n Input string: ");
                scanf("%s", double_str);

                doublingWords(double_str);

                printf("\n\n The result is: \n\n");

                FILE *file6 = fopen("file.txt", "r");
                showAFile(file6);
                fclose(file6);

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            case 24:
                refresh();

                printf("\n\n\t Your option: File encoding");
                printf("\n\n\n The file input is: \n\n\n");


                FILE *file7 = fopen("file.txt", "r");
                showAFile(file7);
                fclose(file7);

                file_encoding();

                printf("\n\n The result is: \n\n");

                FILE *file8 = fopen("file.txt", "r");
                showAFile(file8);
                fclose(file8);

                printf("\n\n\n");

                system("pause");
                refresh();
                break;

            default:
                refresh();
                //printf("\n\n\tPlease reenter a valid option\n\n");
                break;
        }
    }
    while(option != 3);
    return 0;
}
