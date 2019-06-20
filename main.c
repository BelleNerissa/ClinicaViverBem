#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

struct Tpaciente
{
    int cod;
    char nome [50];
    char endereco [50];
    char celular [9];
    char data_nascimento [10];

};
typedef struct Tpaciente paciente;

void cadastropaciente(FILE *fl)
{
    paciente pac;
    int posicao, codigo;
    printf("Digite o codigo: ");
    fflush(stdin);
    scanf("%d",&pac.cod);
    posicao=localizacodigo(fl,pac.cod);
    if(posicao==-1){
        printf("Digite o seu nome completo: ");
        fflush(stdin);
        gets(pac.nome);

        printf("Digite o seu endereço: ");
        fflush(stdin);
        gets(pac.endereco);

        printf("Digite o seu celular: ");
        fflush(stdin);
        gets(pac.celular);

        printf("Digite a data do seu nascimento: ");
        fflush(stdin);
        gets(pac.data_nascimento);


        fseek(fl,0,SEEK_SET);
        fwrite(&pac, sizeof(pac),1,fl);
        fclose(fl);
    }
    else {
        printf("Paciente já está cadastrado no sistema. Por isso não foi incluido.\n");
    }
}

  int localizacodigo(FILE *fl, int cod) {
    int posicao=-1,achou=0;
    paciente pac;
    fseek(fl,0,SEEK_SET);
    fread(&pac, sizeof(pac),1, fl);
    while (!feof(fl) && !achou)
    {
        posicao++;
        if (pac.cod == cod)
        {
            achou=1;
        }
        fread(&pac, sizeof(pac), 1, fl);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void main() {
    setlocale(LC_ALL, "portuguese");

    cadastropaciente(fopen("db.bin", "ab+"));
}
