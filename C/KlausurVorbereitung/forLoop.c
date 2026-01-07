#include <stdio.h>

#define NUM_ALUNOS 3
#define NUM_DISCIPLINAS 4

typedef struct 
{
    char nome[50];
    int notas[NUM_DISCIPLINAS];
} Student;

int main(void){

    Student alunos[NUM_ALUNOS] = {
        {"Ana", {85, 90, 78, 92}},
        {"Carlos", {70, 65, 80, 75}},
        {"Beatriz", {88, 92, 94, 89}}
    };

    for(int i = 0; i < NUM_ALUNOS; ++i){
        
        int soma = 0;

        for(int j = 0; j < NUM_DISCIPLINAS; ++j){
            
            soma += alunos[i].notas[j];
        }

        printf("%s = %d\n", alunos[i].nome, soma);
    }
}
