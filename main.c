#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//Dados Abstratos
struct Telefone
{
    int ddd;
    int numero;
};
typedef struct Telefone telefoneEntity;

struct Endereco
{
    int numero;
    char rua[20],complemento[15],bairro[20],cidade[20],uf[3],cep[10];
};
typedef struct Endereco enderecoEntity;

struct Data
{
    int dia,mes,ano,horas;
};
typedef struct Data dataEntity;

//Entidades
struct Paciente
{
    int codigo;
    char nome[30];
    telefoneEntity telefone;
    enderecoEntity endereco;
    dataEntity dataNascimento;    
};
typedef struct Paciente pacienteEntity;

struct Medico
{
    int codigo;
    char nome[30];
    telefoneEntity telefone;
    char especialidade[30];
    char turno[30];  
};
typedef struct Paciente pacienteEntity;

struct Consulta
{
    int codigo;
    int codigoMedico;
    int codigoPAciente;
    telefoneEntity telefone;
    dataEntity data;
};
typedef struct Paciente pacienteEntity;


FILE *arquivoPacientes;
FILE *arquivoMedicos;
FILE *arquivoConsultas;
int main() {

    setlocale(LC_ALL,"portuguese");

    inicializaArquivos(arquivoPacientes, arquivoMedicos, arquivoConsultas);


    int menu;
    do {
        printf("\n\n============================\n");
        printf("Selecione uma opção:\n");
        printf("1 - Cadastrar um Paciente\n");
        printf("2 - Cadastrar um Médico\n");
        printf("3 - Cadastrar Locação\n");
        printf("4 - Baixa em locação\n");
        printf("5 - Localizar dados\n");
        printf("6 - Locação por cliente\n");
        printf("7 - Pontuação do cliente\n");
        printf("8 - Clientes que recebem kit\n");
        printf("9 - Exibe locações atrasadas\n");
        printf("0 - Sair do programa\n");
        printf("Opcao: ");
        scanf("%d",&menu);
        printf("============================");
        switch(menu)
        {
            case 0:
                printf("Saindo... \n");
                break;
            case 1:
                cadastraPaciente(arquivoPacientes);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                printf("Opção inválida.\n\n");
                break;
        }
    }while(menu != 0);

}
//Inicializa Arquivos
void inicializaArquivos(){
    if ((arquivoPacientes=fopen("./data/pacientes.txt","r+b"))==NULL)
    {
        printf("Criando arquivo de clientes...\n");
        if ((arquivoPacientes=fopen("./data/pacientes.txt","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo de clientes!!\n");
            exit(1);
        }
    }

    if ((arquivoMedicos=fopen("./data/medicos.txt","r+b"))==NULL)
    {
        printf("Criando arquivo de veiculos...\n");
        if ((arquivoMedicos=fopen("./data/medicos.txt","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo de veículos!!\n");
            exit(1);
        }
    }

    if ((arquivoConsultas=fopen("./data/consultas.txt","r+b"))==NULL)
    {
        printf("Criando arquivo de veiculos...\n");
        if ((arquivoConsultas=fopen("./data/consultas.txt","w+b"))==NULL)
        {
            printf("Erro na criação do arquivo de veículos!!\n");
            exit(1);
        }
    }

    return;
}

//Manipula Pacientes
void cadastraPaciente(FILE *arquivoPacientes)
{
    printf("\n====Cadastra Paciente====\n");
    pacienteEntity p;
    int posicao,codigo;
    printf("\nCódigo:             ");
    scanf("%d",&codigo);
    posicao=encontraCliente(arquivoPacientes,codigo,"---");
    if (posicao==-1)
    {
        p.codigo=codigo;
        printf("Nome:               ");
        fflush(stdin);
        gets(p.nome);

        cadastraTelefone(&p.telefone);

        cadastraEndereco(&p.endereco);

        fseek(arquivoPacientes,0,SEEK_END);
        fwrite(&p, sizeof(p),1,arquivoPacientes);
        fflush(arquivoPacientes);

        printf("\Pacientes cadastrado com sucesso!");
    }
    else
    {
        printf("Já existe um Pacientes com esse código. Inclusão não realizada!\n");
    }
}

int encontraCliente(FILE *arquivoPacientes,int codigo, char nome[30])
{
    int posicao=-1,achou=0;
    pacienteEntity p;
    fseek(arquivoPacientes,0,SEEK_SET);
    fread(&p, sizeof(p),1, arquivoPacientes);
    while (!feof(arquivoPacientes) && !achou)
    {
        posicao++;
        if (p.codigo==codigo || strcmpi(p.nome,nome)==0)
        {
            achou=1;
        }
        fread(&p, sizeof(p),1, arquivoPacientes);
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

//Manipula Médicos