#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTLEN 100

typedef struct data_base
{
    char comes[12];
    char sender[50];
    char name[50];
    long int weight;
    long int count;
    char images[50]; 
    char worker[50];
    struct data_base *next;
} data_base;

data_base head;
data_base *tail = &head;
FILE *input, *output;
char condition[INPUTLEN];
char fields[][7] = {"comes", "sender", "name", "weight", "count", "images", "worker"};
int N=0;

typedef struct
{
    char *name;
    void (*func)();
} Command;

void insert()
{
    data_base *unit = malloc(sizeof(data_base));
    char bit_mask_for_checking_free_space = 0;
    char field[12], value[50];
    char *condition_temp = condition;
    int i;
    
    while((*(condition_temp++)!=' '||*condition_temp==' ')&&*condition_temp);//рассматриваем только параметры команды
    
    while (*(condition_temp-1)==','||*(condition_temp-1)==' ')
    {
        i = 0;
        while (i < 11 && *condition_temp && *condition_temp != '=')
            field[i++] = *condition_temp++;
        field[i] = '\0';
        
        condition_temp += (*condition_temp == '=');// чтобы просто было
        
        i = 0;
        while (i < 49 && *condition_temp && *condition_temp != ',' && *condition_temp != '\n')
            value[i++] = *condition_temp++;
        value[i] = '\0';
        
        condition_temp += (*condition_temp == ',');// вроде бы обойдемся и без этого но пусть будет
        
        for (i = 0; i < 7 && strcmp(fields[i], field) != 0; i++);
        if (i == 7 || (1 << i & bit_mask_for_checking_free_space)) {bit_mask_for_checking_free_space&=1 << i;break;}

        bit_mask_for_checking_free_space|=1 << i;

        switch (i)
        {
            case 0: strncpy(unit->comes, value, sizeof(unit->comes) - 1); break;
            case 1: strncpy(unit->sender, value, sizeof(unit->sender) - 1); break;
            case 2: strncpy(unit->name, value, sizeof(unit->name) - 1); break;
            case 3: unit->weight = atol(value); break;
            case 4: unit->count = atol(value); break;
            case 5: strncpy(unit->images, value, sizeof(unit->images) - 1); break;
            case 6: strncpy(unit->worker, value, sizeof(unit->worker) - 1); break;
        }
    }

    if(bit_mask_for_checking_free_space!=127)
        free(unit);
    else{
        tail->next=unit;
        tail=unit;
        unit->next=NULL;
        N+=1;
        //printf("N=%d",n);
    }
    fprintf(output,"select: %d\n",N);
}
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
        for (int j = 0; j < 5; j++)
            if (strcmp(command, commands[j].name) == 0)
                commands[j].func();
    }
}

int main()
{
    head.next = NULL;
    printf("Добро пожаловать! Работать с командами из:\n1)Консоль(тут)\n2)input.txt/output.txt\nВведите 1 или 2:");
    if (!(getchar() - '1')){
        input = stdin;
        output=stdout;
    }
    else{
        input = fopen("input.txt", "r");
        output = fopen("output.txt", "w");
    }
    getchar();
    read_the_commands();

    fclose(input);
    fclose(output);

    return 0;
}