#include <stdio.h>
#include <string.h>

#define INPUTLEN 100

typedef enum
{
    FRAGILE = 1 << 0,
    TOXIC = 1 << 1,
    PERISHABLE = 1 << 2,
    ACRID = 1 << 3,
    INFLAMMABLE = 1 << 4,
    FROZEN = 1 << 5
} images;

typedef struct data_base
{
    long int comes;
    char *sender;
    char *name;
    long int weight;
    long int count;
    char images; // храним только коды значков, а не сами значки
    char *worker;
    struct data_base *next;
} data_base;

data_base head;
FILE *input, *output;
char condition[INPUTLEN];

typedef struct
{
    char *name;
    void (*func)();
} Command;

void insert() { printf("1"); }
void select() { printf("2"); }
void delete() { printf("3"); }
void uniq() { printf("4"); }
void update() { printf("5"); }

Command commands[] = {
    {"insert", insert},
    {"select", select},
    {"delete", delete},
    {"update", update},
    {"uniq", uniq},
};

void read_the_commands()
{
    char command[10];

    while (fgets(condition, INPUTLEN, input) != NULL)
    {
        sscanf(condition, "%s", command);
        printf("%s\n", condition);
        for (int j = 0; j < 5; j++)
            if (strcmp(command, commands[j].name) == 0)
                commands[j].func();
    }
}

int main()
{
    head.next = NULL;
    printf("Добро пожаловать! Считывать команды из:\n1)Консоль(тут)\n2)input.txt\nВведите 1 или 2:");
    output = fopen("output.txt", "w");
    if (!(getchar() - '1'))
        input = stdin;
    else
        input = fopen("input.txt", "r");
        
    read_the_commands();

    fclose(input);
    fclose(output);

    return 0;
}