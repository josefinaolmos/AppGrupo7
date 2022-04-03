#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>



int search_book(char *filename, char *book_name)
{
    // declaramos las variables
    FILE *file = fopen(filename, "rb");
    char *buffer;
    long length;
    int found = 0;
    int iterator = 0;
    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    char *token;
    char *last_element;

    if (file == NULL)
    {
        printf("Error opening file\nThe file should be located in the folder above the folder where the program is located\n");
        return 0;
    }
    printf("Searching for book: %s\n", book_name);

    // leemos el archivo linea por linea
    while ((read = getline(&line, &len, file)) != -1)
    {
        // actualizamos el iterador
        iterator++;
        // conseguimos el primer elmento de cada linea
        token = strtok(line, ",");
        while (token != NULL) {
            if  (strcmp(token, book_name) == 0) {
                found = 1;
                printf("\nBook found on line ");
                // printeamos la linea con el libro encontrado
                printf("%d\n\n", iterator);
                printf("Book name: %s\n", token);
                // imprimimeros el resto de los atributos del libro
                token = strtok(NULL, ",");
                printf("Author: %s\n", token);
                token = strtok(NULL, ",");
                printf("Year: %s\n", token);
                token = strtok(NULL, ",");
                printf("Estante number: %s\n", token);
                token = strtok(NULL, ",");
                printf("Estante section: %s\n", token);
                token = strtok(NULL, ",");
                printf("Piso: %s\n", token);
                token = strtok(NULL, ",");
                printf("Edificio: %s\n", token);
                token = strtok(NULL, ",");
                printf("Sede: %s\n", token);

                // cerramos el archivo
                fclose(file);

                Sleep(2000);

                // retornamos el valor encontrado
                return iterator;
            } else {
                // condicional en caso de que el libro no se encuentre
                found = 0;
                // actualizamos el token
                token = strtok(NULL, ",");
            }
        }
    }

}


#define MAX 256

int edit_line(char *filename, char *book_name) {

    FILE *fptr1, *fptr2;
    int lno, linectr = 0;
    char str[MAX], fname[MAX];
    char newln[MAX], temp[] = "temp.txt";
    char author[MAX], anio[MAX], estante_numero[MAX], estante_seccion[MAX], piso[MAX], edificio[MAX], sede[MAX];

    filename[strlen(filename)] = '\0';
    fptr1 = fopen(filename, "rb");
    if (!fptr1)
    {
        printf("Unable to open the input file!!\n");
        return 0;
    }
    fptr2 = fopen(temp, "wb");
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return 0;
    }

    lno = search_book(filename, book_name);

    printf("Please enter the author: ");
    scanf("%[^\n]s", author);
    getchar();

    printf("Please enter the year: ");
    scanf("%[^\n]s", anio);
    getchar();

    printf("Please enter the estante number: ");
    scanf("%[^\n]s", estante_numero);
    getchar();

    printf("Please enter the estante section: ");
    scanf("%[^\n]s", estante_seccion);
    getchar();

    printf("Please enter the piso: ");
    scanf("%[^\n]s", piso);
    getchar();

    printf("Please enter the edificio: ");
    scanf("%[^\n]s", edificio);
    getchar();

    printf("Please enter the sede: ");
    scanf("%[^\n]s", sede);
    getchar();
    printf("\nThe new line is: %s\n", newln);

    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                // add all the new valeus to the line
                fprintf(fptr2, "%s", book_name);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", author);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", anio);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", estante_numero);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", estante_seccion);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", piso);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", edificio);
                fprintf(fptr2, "%s", ",");
                fprintf(fptr2, "%s", sede);
                fprintf(fptr2, "%s", "\n");

            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(filename);
    rename(temp, filename);
    printf("Replacement did successfully..!! \n");
    return 0;
}