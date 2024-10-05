/*AGLP - Ativ05 - Projeto hotel

13/06/2024

Alexandre Maciano de Oliveira
Gabriel Mechi Lima
Luiz Fernando de Marchi Andrade
Priscilla Yewon Lee 

O programa irá apresentar ao usuário o status do hotel junto de um menu onde o mesmo poderá realizar a reserva de quartos,
o check-in e check-out. Também será possivel realizar o cancelamento de reservas e verificar a taxa de ocupação do hotel.
Ao fazer uma reserva ou um check-in sem reserva, o usuário irá inserir seus dados pessoais (CPF, nome, idade, enderco, telefone
e email), onde os mesmo poderam ser conferidos com o uso da opção 6 do menu "Verificar o status do apartamento".

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct apartamento //Também contém os dados do hospede 
{
    char situacao; //'O' para Ocupado, 'R' para Reservado, '.' para Livre
    char cpf[15]; 
    char nome[50];
    int idade;
    char endereco[100];
    char telefone[15];
    char email[50];

} tipoApto;

// Para criar a matriz de estrutura do Hotel
tipoApto Hotel[20][14];

void menu();
void func_apresentarAp(tipoApto Hotel[20][14]);  // Apresenta a matriz
void func_Reserva(tipoApto Hotel[20][14]);   // Realiza a reserva 
void func_Checkin(tipoApto Hotel[20][14]);  // Realiza o check in
void func_CheckinS(tipoApto Hotel[20][14]);   // Realiza o check in sem reserva 
void func_Checkout(tipoApto Hotel[20][14]);  // Realiza o check ou
void func_Cancela(tipoApto Hotel[20][14]);    // Realiza a cancela da reserva 
void func_Status(tipoApto Hotel[20][14]); // Checa status do apartamento
void func_Taxa(tipoApto Hotel[20][14]);   // Apresenta e faz o calcula da taxa de ocupação do hotel
void fclear();  // Função para limpar o buffer de entrada

int main() 
{
    int opcao;

    // Inicializa todos os apartamentos como disponíveis 
    for(int j = 0; j < 14; j++)
        for(int i = 0; i < 20; i++)
            Hotel[i][j].situacao = '.';

  	func_apresentarAp(Hotel);
    
    while (1) 
    {
         // Mostra o mapa de ocupação do hotel
        menu();
        scanf("%d", &opcao);
        fclear();

        switch(opcao) {
            case 1: // Check-in
                func_Checkin(Hotel);  
                break;
            case 2: //Check-in sem reserva
                func_CheckinS(Hotel);
                break;
            case 3: // Check-out
                func_Checkout(Hotel);
                break;
            case 4: // Realizar reserva
                func_Reserva(Hotel);
                break;
            case 5: // Cancelar a reserva
                func_Cancela(Hotel);
                break;
            case 6: // Status do apartamento
                func_Status(Hotel);
                break;
            case 7: //Apresentar a matriz
            	func_apresentarAp(Hotel);
			    break;
			case 8: // Sair do programa
                exit(0);
                break;
            default:
                printf("Opcao invalida! Tente novamente\n");
                break;
        }
      
	}
}

void menu() 
{ 
    printf("\n=================================================== \n");
    printf("\n           Bem vindo ao hotel PHC         \n");
    printf("\n      Selecione o numero da opcao desejada \n\n");
    printf("  1 -> Realizar um Check-in (com reserva)\n");
    printf("  2 -> Realizar um Check-in (sem reserva)\n");
    printf("  3 -> Realizar um Check-out \n"); 
    printf("  4 -> Realizar uma reserva \n");  
    printf("  5 -> Cancelar uma reserva \n");
    printf("  6 -> Verificar status do apartamento\n");
    printf("  7 -> Verificar o mapa do hotel\n");
	printf("  8 -> Sair do programa \n");
    printf("\n=================================================== \n");
}

void func_apresentarAp(tipoApto Hotel[20][14])
{
    int i, j;

    // Exibir números das colunas (apartamentos)
    printf("         ");
    for (j = 0; j < 14; j++) 	
        printf("%2d ", j + 1);
    
    printf("\n");

    // Exibir números das linhas (andares)
    for (i = 0; i < 20; i++)
    {
        printf("andar %2d ", 20 - i);
        for (j = 0; j < 14; j++) 
            printf(" %c ", Hotel[i][j].situacao);
        
        printf("\n");
    }
    
    func_Taxa(Hotel); // Calcula e exibe a taxa de ocupação e reserva
}

void func_Taxa(tipoApto Hotel[20][14])
{
    int ocupados = 0, reservados = 0, total = 280; // 20 andares * 14 apartamentos
    for (int i = 0; i < 20; i++)
	{
        for (int j = 0; j < 14; j++)
		    {
            if (Hotel[i][j].situacao == 'O') 
                ocupados++;
             else if (Hotel[i][j].situacao == 'R') 
                reservados++;
            }
    }
    
    double taxaOcupacao = (100.0 * ocupados) / total;  // Formula de porcentagem
    double taxaReserva = (100.0 * reservados) / total;
    printf("\nTaxa de Ocupacao: %.2lf%%\n", taxaOcupacao);
    printf("Taxa de Reserva: %.2lf%%\n", taxaReserva);
}

void func_Reserva(tipoApto Hotel[20][14])
{
	func_apresentarAp(Hotel);

    int andar, ap;
    printf("\nDigite o andar que deseja reservar: ");
    scanf("%d", &andar);
    printf("\nQual apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar; // Converte o número do andar para um válido na matriz
    int j = ap - 1;

    if (i < 0 || i >= 20 || j < 0 || j >= 14) // Verifica se o ap existe
	{
        printf("\nO apartamento nao existe, tente outro!\n");
		return;
    }

    if (Hotel[i][j].situacao == 'R' || Hotel[i][j].situacao == 'O') 
	{
        printf("\nO apartamento nao esta disponivel!\n");
		return;
    }  
    
    if (Hotel[i][j].situacao == '.')
    {
        Hotel[i][j].situacao = 'R';
            printf("\nSua reserva no andar %d e apartamento %d foi realizada sucesso!\n", andar, ap);	
    }
}

void func_Checkin(tipoApto Hotel[20][14])
{ 
    func_apresentarAp(Hotel);

    int andar, ap; 
    printf("\nDigite o andar no fazer check-in: ");
    scanf("%d", &andar);
    printf("\nQual o numero do apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar;
    int j = ap - 1;

    if (i < 0 || i >= 20 || j < 0 || j >= 14) 
	{
        printf("\nO apartamento nao existe, tente outro!\n");
	    return;
    }

    if (Hotel[i][j].situacao == 'R')
    {
        do  // Permite que o hospede insira seus dados pessoais 
		 {
            printf("\nEscreva seu nome: ");
            scanf("%s", Hotel[i][j].nome);
            fclear();  // Limpa o buffer de entrada

            printf("\nEscreva sua idade: ");
            scanf("%d", &Hotel[i][j].idade);
            fclear();

            printf("\nEscreva seu CPF: ");
            scanf("%s", Hotel[i][j].cpf);
            fclear();

            printf("\nEscreva seu endereco: ");
            scanf("%s", Hotel[i][j].endereco);
            fclear();

            printf("\nEscreva seu telefone: ");
            scanf("%s", Hotel[i][j].telefone);
            fclear();

            printf("\nEscreva seu email: ");
            scanf("%s", Hotel[i][j].email);
            fclear();

            Hotel[i][j].situacao = 'O';
            printf("\nCheck-in Realizado com sucesso!\n");

        } while(Hotel[i][j].situacao != 'O');
    } 
	
	else if (Hotel[i][j].situacao == 'O') 
	    printf("\nO apartamento ja esta ocupado!\n");
    
	else
        printf("\nO apartamento nao esta reservado!\n");
    
    
}

void func_CheckinS(tipoApto Hotel[20][14])
{ 
    func_apresentarAp(Hotel);

    int andar, ap; 
    printf("\nDigite o andar aonde vai fazer seu check-in: ");
    scanf("%d", &andar);
    printf("\nQual o numero do apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar;
    int j = ap - 1;

    if ( i < 0 || i >= 20 || j < 0 || j>= 14)
	{
        printf("\nO apartamento nao existe, tente outro\n");
	    return;
    }
    
    if (Hotel[i][j].situacao == 'R')
	{
        printf("\nApartamento ja reservado! Escolha outro\n");
	    return;
    }
    
    if (Hotel[i][j].situacao == 'O')
	{
        printf("\nApartamento ja ocupado! Escolha outro\n");
	    return;
    }
    
    else
	{
         do  // Permite que o hospede insira seus dados pessoais 
		 {
            printf("\nEscreva seu nome: ");
            scanf("%s", Hotel[i][j].nome);
            fclear();  // Limpa o buffer de entrada

            printf("\nEscreva sua idade: ");
            scanf("%d", &Hotel[i][j].idade);
            fclear();

            printf("\nEscreva seu CPF: ");
            scanf("%s", Hotel[i][j].cpf);
            fclear();

            printf("\nEscreva seu endereco: ");
            scanf("%s", Hotel[i][j].endereco);
            fclear();

            printf("\nEscreva seu telefone: ");
            scanf("%s", Hotel[i][j].telefone);
            fclear();

            printf("\nEscreva seu email: ");
            scanf("%s", Hotel[i][j].email);
            fclear();

            Hotel[i][j].situacao = 'O';
            printf("\nCheck-in Realizado com sucesso!\n");

        } while(Hotel[i][j].situacao != 'O');
    }
}

void func_Checkout(tipoApto Hotel[20][14])
{
	func_apresentarAp(Hotel);

    int andar, ap; 
    printf("\nDigite o andar no fazer check-out: ");
    scanf("%d", &andar);
    printf("\nQual o numero do apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar;
    int j = ap - 1;

    if (i < 0 || i >= 20 || j < 0 || j >= 14) 
	{
        printf("\nO apartamento nao existe, tente outro!\n");
		return;
    }

    if (Hotel[i][j].situacao == 'O') 
	{
        Hotel[i][j].situacao = '.';
        printf("\nCheck-out realizado com sucesso!\n");        
    } 
	
	else  
	    printf("\nO apartamento ja esta vazio, tente outro!\n");
    
}

void func_Cancela(tipoApto Hotel[20][14])
{
	func_apresentarAp(Hotel);
	
    int andar, ap;
    printf("\nDigite o andar no qual deseja cancelar a reserva: ");
    scanf("%d", &andar);
    printf("\nQual o numero do apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar;
    int j = ap - 1;

    if (i < 0 || i >= 20 || j < 0 || j >= 14) 
	{
        printf("\nO apartamento nao existe, tente outro!\n");
		return;
    }

    if (Hotel[i][j].situacao == 'R')
	{
        Hotel[i][j].situacao = '.';
        printf("\nReserva cancelada com sucesso!\n");
    } 
	
	else if (Hotel[i][j].situacao == 'O') 
        printf("\nO apartamento ja esta ocupado!\n");
    
	else 
        printf("\nO apartamento nao esta reservado!\n");
}

void func_Status(tipoApto Hotel[20][14])
{
	func_apresentarAp(Hotel);

    int andar, ap;

    printf("\nDigite o andar que deseja verificar o status: ");
    scanf("%d", &andar);
    printf("\nQual apartamento?: ");
    scanf("%d", &ap);
    fclear();

    int i = 20 - andar; // Converte o número do andar para um válido na matriz
    int j = ap - 1;

    if (i < 0 || i >= 20 || j < 0 || j >= 14) 
	{
        printf("\nO apartamento nao existe, tente outro!\n");
	    return;
    }

    if (Hotel[i][j].situacao == '.') 
         printf("\nO apartamento esta livre!\n");
      
	if (Hotel[i][j].situacao == 'R')
		 printf("\nO apartamento esta reservado!\n");
	           
    // Apresenta os dados que foram inseridos pelo hospede
    if (Hotel[i][j].situacao == 'O') 
	{
      printf("\nO apartamento esta ocupado!\n");
      printf("\nNome: %s\n", Hotel[i][j].nome);
      printf("Idade: %d\n", Hotel[i][j].idade);
	  printf("CPF: %s\n", Hotel[i][j].cpf);
      printf("Endereco: %s\n", Hotel[i][j].endereco);
      printf("Telefone: %s\n", Hotel[i][j].telefone);
      printf("Email: %s\n\n", Hotel[i][j].email);
    }
}

void fclear() 
{
    char carac;
    while ((carac = fgetc(stdin)) != EOF && carac != '\n') {}
}
