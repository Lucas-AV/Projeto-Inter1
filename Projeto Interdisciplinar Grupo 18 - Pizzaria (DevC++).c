// github: LucasV75
/*
Feito:
1. Op��o de troca de acessos (Usu�rio e senha) para funcion�rios e administradores
Pendente:
1. Informa��o de funcion�rio (Geral similar a cliente)
2. Sal�rio do funcion�rio
*/
#include <stdio.h>   // Inputs e outputs em C
#include <stdlib.h>  // Padr�o do C
#include <locale.h>  // Configura o idioma do terminal
#include <ctype.h>   // Serve para verificar os tipos de vari�veis
#include <stdbool.h> // Adiciona o tipo de vari�vel bool ao C
#include <Windows.h> // Inclui a fun��o "sleep" e mais algumas outras
#include <conio.h>   // Respons�vel pelo getch();
#include <time.h>    // Serve para usar fun��es relacionadas a tempo
// Cores
#define GRN "\e[1;32m"
#define RED "\e[1;31m"
#define RST "\e[0m"

// Utilidades!
void strcenter(char *line, char *string, char digit, bool color){
    int i;
	int lenString = strlen(string);
    if(color == true){
        lenString -= 10;
    }
    int Mid = strlen(line)-lenString; // Calcula a diferen�a de tamanho entre as strings fornecidas
    printf("%s\n",line);
    if(strlen(line) % 2 != 0){
        Mid += 1; // Contador
    }
    for(i = 0; i < Mid/2; i++){
        printf("%c",digit); // Printa o digito no lado esquerdo
    }
    if(strlen(line) % 2 != 0){
        Mid -= 1;
    }
    printf("%s",string); // Printa a string principal

    for(i = 0; i < Mid/2; i++){
        printf("%c",digit); // Printa o digito no lado direito
    }
    printf("\n%s\n",line); // Printa a linha final
}

// M�todo de valida��o de informa��o por meio de verifica��o de caracteres
int ValInfo(char Alvo, char *Lista){
    int Count = 0;
    int i;
    for(i = 0; i < strlen(Lista); i++){
        //printf("%i: %c && %c\n",i,Alvo,Lista[i]); // DEBUG
        if(Alvo == Lista[i]){
            Count++;
        }
    }
    // Se Count for igual a 0, o char que est� sendo verificado vai ser considerado inv�lido!
    return Count;
}

// Anima��o de carregamento!
void Animation(){
    int i;
    for (i = 0; i < 16; i++){
        if (i % 5 == 0){
            printf("\b\b\b\b\b");
        } else {
            printf(" ");
        }
        Sleep(100);
    }
}

// Structs!
// Struct dos restaurantes
struct Locais{
    char *Cidades[4], *Enderecos[4];
    int Salas[4], Empregados[4];
    float Gastos[4], Renda[4], Lucros[4];
    int QntLojas;
};

// Struct para salvar informa��es referentes ao usuario
struct User{
    char *Pizzas[100], *Tamanhos[100];  // Informa��os das pizzas pedidas pelo cliente
    char usuario[100], senha[100], nome[100], telefone[100], retirada[100]; // Informa��es do cliente
    char endereco[2][100];  // Endere�o do cliente (Cidade + Endere�o)
    int quantidade[100];   // Quantidade das pizzas do cliente por pedido
    int ID;         // Usado para verificar a exist�ncia da conta
    int Contador;   // Utilizado para interagir com Pizzas,Tamanhos e quantidade;
    bool logado;    // Utilizado para valida��o de login (Atualmente s� funciona com Admin)
    float total;    // Total do pedido
};

// Usei para armazenar informa��es referentes a cada usuario (Um jeito de salvar os pedidos)
struct Login{
    struct User sessoes[100];   // Registro de sess�es de logins feitas
    int numSessoes;             // Contador de sessoes
};

// Struct Pizzas!
struct Pizzas{
    int QntSalgadas, QntDoces, QntGeral; // Contadores de pizzas
    char *salgadas[100][100];
    char *doces[100][100];
    char *geral[100][100];
    char *tamanhos[3];
    float precos[3];
};

// Struct Menus (Struct geral para prints de menus)
struct Menu{
    char *Items[100];
    char title[100];
    int Tamanho;
};

void viewPizzas(struct Pizzas pizzas, char *line, int digit){
    system("cls");
    strcenter(line,"Sabores de pizzas dispon�veis no momento!",digit,false);
    int i;
    int l;
    for(i = 0; i < pizzas.QntSalgadas; i++){
        char format[100];
        sprintf(format,"%c. %s",i+65,pizzas.salgadas[i][0]);
        int lenght = strlen(format);

        printf("%s",format);
        for(l = 0; l <= 34 - lenght; l++){
            printf("%1c",digit);
        }
        if(i < pizzas.QntDoces){
            printf("%c. %s",(i+pizzas.QntSalgadas-1)+66,pizzas.doces[i][0]);
        }
        printf("\n");
    }
    printf("%s\n",line);
}

void viewDescontos(char *decorador, char *Dias[7], char *Promos[7]){
    system("cls");
    strcenter(decorador,"Descontos",32,false);
    int i;
    for(i = 0; i < 7; i++){
        printf("- %s %s\n", Dias[i], Promos[i]);
    };
    printf("%s\n",decorador);
}

void viewContatos(char *decorador){
    system("cls");
    strcenter(decorador,"Contatos",32,false);
    printf("Email:     CodePizza@gmail.com\n");
    printf("Discord:   CodePizza#1140\n");
    printf("Telefone:  61 93879-8634\n");
    printf("Instagram: @CodePizza\n");
    printf("UberEats:  CodePizza\n");
    printf("Ifood:     CodePizza\n");
    printf("%s\n",decorador);
    system("PAUSE");
}

void viewSobre(char *decorador){
    system("cls");
    strcenter(decorador,"Sobre",32,false);
    printf("Mensagem de motiva��o da pizzaria     (EXEMPLO)\n");
    printf("Descri��o do neg�cio da pizzaria      (EXEMPLO)\n");
    printf("%s\n",decorador);
    system("PAUSE");
}

void viewTamanhosPizza(char *decorador, float preco[3], char *nomes[3], char *sabor){
    system("cls");
    strcenter(decorador,sabor,32,false);
    int i;
    for(i = 0; i < 3; i++){
        printf("%i. %s: R$ %.2f\n",i+1,nomes[i],preco[i]);
    }
    printf("%s\n",decorador);
}

void viewLojas(struct Locais Lojas, char *line, int digit){
    system("cls");
    strcenter(line,"Informa��es sobre cada loja!",digit,false);
    int i;
    for(i = 0; i < Lojas.QntLojas; i++){
        printf("%s\n",Lojas.Cidades[i]);
        printf("%s\n",Lojas.Enderecos[i]);
        printf("Receita: R$ %.2f\n",Lojas.Renda[i]);
        printf("Lucro:   R$ %.2f\n",Lojas.Lucros[i]);
        printf("Gasto:   R$ %.2f\n",Lojas.Gastos[i]);
        printf("Empregados: %i\n",Lojas.Empregados[i]);
        if(Lojas.Lucros[i] > Lojas.Gastos[i]){
            printf(GRN"Lucro!"RST" (R$ %.2f)",Lojas.Lucros[i] - Lojas.Gastos[i]);
        }
        else if(Lojas.Lucros[i] == Lojas.Gastos[i]){
            printf("Neutro!");
        }
        else{
           printf(RED"Preju�zo!"RST" (R$ %.2f)",Lojas.Lucros[i] - Lojas.Gastos[i]);    
        }
        printf("\n%s\n",line);
    }
    system("PAUSE");
}

void viewMenu(struct Menu menu, char *line, int digit){
    system("cls");
    strcenter(line,menu.title,digit,false);
    int i;
    for(i = 0; i < menu.Tamanho; i++){
        printf("%i. %s\n",i+1,menu.Items[i]);
    }
    printf("%s\n",line);
    printf("> ");
}

void viewEnderecos(char enderecos[100][2][100], char users[100][4][100], int cUsers,char *line, int digit){
    system("cls");
    strcenter(line,"- Lista de endere�os dos clientes -",digit,false);
    int i;
    if(cUsers > 2){
        for(i = 2; i < cUsers; i++){
            printf("> Cliente:  %s\n",users[i][0]);
            printf("> Cidade:   %s\n",enderecos[i][0]);
            printf("> Endere�o: %s\n",enderecos[i][1]);
            if(i < (cUsers-1)){
                printf("\n");
            }
        }
    } else {
        printf("> Sem clientes cadastrados\n");
        printf("> Sem endere�os cadastrados\n");
    }
    
    printf("%s\n",line);
    system("pause");
}

void viewPedidos(struct Login logins, char *line){
    strcenter(line,"- Pedidos do dia -",32,false);
    int i, C;
    if(logins.numSessoes > 0){
        for(i = 0; i < logins.numSessoes; i++){
            if(logins.sessoes[i].total > 0){
                printf("Cliente: %s\n",logins.sessoes[i].usuario);
                for (C = 0; C < logins.sessoes[i].Contador; C++){
                    printf("> %s (%i %s)\n",logins.sessoes[i].Pizzas[C],logins.sessoes[i].quantidade[C],logins.sessoes[i].Tamanhos[C]);
                }
                if(logins.sessoes[i].endereco[0] > 0 && logins.sessoes[i].endereco[1] > 0 && strcmp(logins.sessoes[i].retirada,"Endere�o do cliente") == 0){
                    printf("Endere�o: %s\n",logins.sessoes[i].endereco[1]);
                    printf("Cidade:   %s\n",logins.sessoes[i].endereco[0]);
                }
                else {
                    printf("Retirada: %s\n",logins.sessoes[i].retirada);
                }
                printf("Total:    R$ %.2f\n",logins.sessoes[i].total);
                printf("%s\n",line);
            }
        }
    } 
    else {
        printf("Nenhum pedido ainda!\n%s\n",line);
    }
    system("PAUSE");
}

int main(){
    // Configura��es!
    // system("chcp 65001");
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Declara��es
    int option = 100;               // Navega��o
    char PassUsers[100][4][100];    // Lista de contas criadas (Nome, Telefone, Usu�rio, Senha);
    char Enderecos[100][2][100];    // Lista de Endere�os criados (Cidade, Endere�o)
    int cPassUsers = 0;             // Contador para contas criadas
    int i;

    // decoradores!
    char *lineM = "===========================================";
    char *line = "===============================================";
    char *line2 = "====================================================================";
    char *nome = "Pizzaria: Code Pizza"; // nome da loja

    // Lista de caracteres dispon�veis
    char nums[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char Alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char AlphaNums[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; // Alfabeto

    // Admin
    char AdmNome[100] = "Admin";
    char AdmUser[100] = "adm@gmail.com";
    char AdmSenha[100] = "adm123";
    // Funcion�rio
    char FuncNome[100] = "Funcion�rio";
    char FuncUser[100] = "func@gmail.com";
    char FuncSenha[100] = "func123";
    float FuncSal = 3000;
    int FuncHoras = 160;

    // Registro (ADM e FUNC)
    strcpy(PassUsers[cPassUsers][0],AdmNome);
    strcpy(PassUsers[cPassUsers][1],AdmUser);
    strcpy(PassUsers[cPassUsers][2],AdmSenha);
    cPassUsers++;
    strcpy(PassUsers[cPassUsers][0],FuncNome);
    strcpy(PassUsers[cPassUsers][1],FuncUser);
    strcpy(PassUsers[cPassUsers][2],FuncSenha);
    cPassUsers++;

    // Lojas
    struct Locais lojas;
    lojas.QntLojas = 4;

    lojas.Lucros[0] = rand() % 5000 + 10000;
    lojas.Gastos[0] = rand() % 5000 + 7500;
    lojas.Renda[0] = lojas.Renda[0] + lojas.Gastos[0];
    lojas.Cidades[0] = "�guas Claras Norte";
    lojas.Enderecos[0] = "Rua 10 Lote 3";
    lojas.Salas[0] = rand() % 3 + 2;
    lojas.Empregados[0] = rand() % 10 + 2;

    lojas.Lucros[1] = rand() % 5000 + 10000;
    lojas.Gastos[1] = rand() % 5000 + 7500;
    lojas.Renda[1] = lojas.Renda[1] + lojas.Gastos[1];
    lojas.Cidades[1] = "Taguatinga Norte";
    lojas.Enderecos[1] = "CND 14 Lote 10";
    lojas.Salas[1] = rand() % 3 + 2;
    lojas.Empregados[1] = rand() % 10 + 2;

    lojas.Lucros[2] = rand() % 5000 + 10000;
    lojas.Gastos[2] = rand() % 5000 + 7500;
    lojas.Renda[2] = lojas.Renda[2] + lojas.Gastos[2];
    lojas.Cidades[2] = "Vicente Pires";
    lojas.Enderecos[2] = "Rua 5 Lote 28";
    lojas.Salas[2] = rand() % 3 + 2;
    lojas.Empregados[2] = rand() % 10 + 2;
    
    lojas.Lucros[3] = 0;
    lojas.Gastos[3] = 0;
    lojas.Renda[3] = 0;
    lojas.Cidades[3] = "CodePizza";
    lojas.Enderecos[3] = "Rede Geral";
    lojas.Salas[3] = 0;
    lojas.Empregados[3] = 0;

    for(i = 0; i < 3; i++){
        lojas.Lucros[3] += lojas.Lucros[i];
        lojas.Gastos[3] += lojas.Gastos[i];
        lojas.Renda[3] += lojas.Renda[i];
        lojas.Salas[3] += lojas.Salas[i];
        lojas.Empregados[3] += lojas.Empregados[i];
    }
    // Pizzas
    struct Pizzas pizzas;
    pizzas.QntSalgadas = 0;
    pizzas.QntDoces = 0;
    pizzas.QntGeral = 0;

    // Salgadas
    pizzas.salgadas[0][0] = "Pizza de Calabresa com bacon";
    pizzas.salgadas[0][1] = "> Calabresa\n> Bacon\n> Mu�arela\n> Or�gano";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[1][0] = "Pizza de Portuguesa especial";
    pizzas.salgadas[1][1] = "> Mu�arela\n> Presunto\n> Palmito\n> Ervilha\n> Lombo canadense\n> Provolone\n> Ovo\n> Bacon";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[2][0] = "Pizza de Frango com catupiry";
    pizzas.salgadas[2][1] = "> Peito de frango\n> Or�gano\n> Queijo catupiry";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[3][0] = "Pizza de Marguerita";
    pizzas.salgadas[3][1] = "> Mu�arela\n> Manjeric�o\n> Or�gano\n> Tomate\n> Azeitona";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[4][0] = "Pizza de 4 Queijos";
    pizzas.salgadas[4][1] = "> Parmes�o ralado\n> Mu�arela ralada\n> Provolone\n> Gorgonzola";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[5][0] = "Pizza de Pepperoni";
    pizzas.salgadas[5][1] = "> Salame italiano\n> Piment�o\n> Mu�arela\n> Pimenta Calabresa\n> Molho especial";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[6][0] = "Pizza de Mussarela";
    pizzas.salgadas[6][1] = "> Mu�arela\n> Or�gano";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    pizzas.salgadas[7][0] = "Pizza Romana";
    pizzas.salgadas[7][1] = "> Mu�arela\n> Azeitona\n> Anchovas\n> Azeite\n> Tomate Seco";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.salgadas[pizzas.QntGeral][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.salgadas[pizzas.QntGeral][1];
    pizzas.QntSalgadas += 1;
    pizzas.QntGeral += 1;

    // Doces
    pizzas.doces[0][0] = "Pizza de Morango com chocolate";
    pizzas.doces[0][1] = "> P�ssego em calda fatiado\n> Abacaxi em calda fatiado\n> Figo em calda fatiado\n> Mu�arela\n> Lombinho";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[1][0] = "Pizza de Banana com chocolate";
    pizzas.doces[1][1] = "> Leite condensado\n> Mu�arela\n> Chocolate\n> Banana";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[2][0] = "Pizza de Banana com canela";
    pizzas.doces[2][1] = "> A�ucar com canela\n> Mu�arela\n> Banana";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[3][0] = "Pizza de Frutas vermelhas";
    pizzas.doces[3][1] = "> Framboesa fatiada\n> Morgango fatiado\n> Cereja fatiada\n> Chocolate";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[4][0] = "Pizza de Romeu e Julieta";
    pizzas.doces[4][1] = "> Mu�arela\n> Goiabada\n> Canela";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[5][0] = "Pizza de California";
    pizzas.doces[5][1] = "> P�ssego em calda fatiado\n> Abacaxi em calda fatiado\n> Figo em calda fatiado\n> Mu�arela\n> Lombinho";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;
    
    pizzas.doces[6][0] = "Pizza de Sorvete";
    pizzas.doces[6][1] = "> Sorvete de creme\n> Cereja em calda\n> Chocolate branco fatiado\n> Granulados";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    pizzas.doces[7][0] = "Pizza de Chocolate";
    pizzas.doces[7][1] = "> Calda de chocolate\n> Castanhas torradas mo�das\n> Cereja em calda\n> Granulado";
    pizzas.geral[pizzas.QntGeral][0] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][0];
    pizzas.geral[pizzas.QntGeral][1] = pizzas.doces[pizzas.QntGeral%pizzas.QntSalgadas][1];
    pizzas.QntDoces += 1;
    pizzas.QntGeral += 1;

    // Pre�os
    pizzas.precos[0] = 10.00;
    pizzas.precos[1] = 15.00;
    pizzas.precos[2] = 25.00;

    // Tamanhos
    pizzas.tamanhos[0] = "Pizza P";
    pizzas.tamanhos[1] = "Pizza M";
    pizzas.tamanhos[2] = "Pizza G";

    // Init struct logins
    struct Login logins;
    logins.numSessoes = 0;

    // Init struct Menus = {MainMenu, AdmMenu, UserMenu, AccMenu}
    struct Menu MainMenu;
    strcpy(MainMenu.title,nome);
    MainMenu.Items[0] = "Cardapio de pizzas";
    MainMenu.Items[1] = "Logar no sistema";
    MainMenu.Items[2] = "Contatos";
    MainMenu.Items[3] = "Sobre";
    MainMenu.Items[4] = "Sair";
    MainMenu.Tamanho = 5;

    struct Menu UserMenu;
    UserMenu.Items[0] = "Fazer um pedido";
    UserMenu.Items[1] = "Ver resumo do pedido";
    UserMenu.Items[2] = "Locais de retirada";
    UserMenu.Items[3] = "Modificar endere�o";
    UserMenu.Items[4] = "Ver sua conta";
    UserMenu.Items[5] = "Sair";
    UserMenu.Tamanho = 6;

    struct Menu AdmMenu;
    strcpy(AdmMenu.title,"Logado como Administrador");
    AdmMenu.Items[0] = "Consultar Lojas";
    AdmMenu.Items[1] = "Receita do m�s";
    AdmMenu.Items[2] = "Pedidos do dia";
    AdmMenu.Items[3] = "Informa��es de acessos";
    AdmMenu.Items[4] = "Sair";
    AdmMenu.Tamanho = 5;

    struct Menu AccMenu;
    strcpy(AccMenu.title,"- MUDAN�A DE INFORMA��ES -");
    AccMenu.Items[0] = "Nome em conta";
    AccMenu.Items[1] = "Telefone";
    AccMenu.Items[2] = "Usu�rio";
    AccMenu.Items[3] = "Senha";
    AccMenu.Items[4] = "Voltar";
    AccMenu.Tamanho = 5;

    struct Menu FuncMenu;
    FuncMenu.Items[0] = "Resumo da rede pizzaria";
    FuncMenu.Items[1] = "Endere�o dos clientes";
    FuncMenu.Items[2] = "Pedidos da pizzaria";
    FuncMenu.Items[3] = "Informa��es";
    FuncMenu.Items[4] = "Sair";
    FuncMenu.Tamanho = 5;
    // Code
    do{
        // Init struct User ("Usuario atual >>> Muda toda vez q o loop recome�a!")
        struct User user_atual;
        user_atual.Contador = 0;    // Contador de pizzas pedidas at� o momento
        user_atual.total = 0;       // Total do pedido
        user_atual.logado = false;  // Bool de controle

        viewMenu(MainMenu,line,32); // Fun��o de menu
        option = getch();           // Um tipo de input especifico sem enter que retorna um valor em n�mero digitado pelo usu�rio!
        Sleep(20);
        if(option >= 48 && option <= 57){ // 0 a 9 s�o respectivamente as teclas de n�mero 48 a 57 do teclado
            option = option%48;
        }

        if (option == 1){ // Comando condicional que se relaciona com o valor option
            // Loop para mostar informa��es das Pizzas
            int CodePizza; // Define o valor de option para 100 por padr�o para evitar bugs relacionados ao scanf
            do{
                viewPizzas(pizzas,line2,32); // Ver Cadapio de Pizzas
                printf("Escolha uma pizza! (Pressione ESC para voltar)");
                printf("\n> ");
                CodePizza = getch();
                Sleep(20);
                // Apenas pra deixar o c�digo mais bonito, essa parte escreve no terminal a letra que foi digitada pelo usu�rio
                if(CodePizza >= 65 && CodePizza <= 90){ // Caixa alta (A ... Z)
                    printf("%c\n",CodePizza);
                    CodePizza %= 65;
                }
                else if(CodePizza >= 97 && CodePizza <= 122){ // Letra min�scula (a ... z)
                    printf("%c\n",toupper(CodePizza));
                    CodePizza %= 97;
                }

                if (CodePizza <= pizzas.QntGeral - 1 && CodePizza >= 0){
                    system("cls");
                    strcenter(line,pizzas.geral[(CodePizza)][0],32,false); // pizzas[(option-1)] = Consulta o valor de index (option-1) na lista pizzas
                    printf("%s\n%s\n",pizzas.geral[(CodePizza)][1],line);
                    system("PAUSE");
                }
            }while(CodePizza != 27);
        }

        else if (option == 2){
            do{
                system("cls");
                strcenter(line,"Login || Registro",32,false);
                printf("> Usu�rio: ");
                gets(user_atual.usuario); // user_atual.usuario = variavel usuario de user_atual
                fflush(stdin);
                int cpmUser = strcmp(user_atual.usuario, AdmUser); // strcmp compara as strings e retorna 0 se forem iguais (-1,1) se forem diferentes
                int cmpQuit = strcmp(user_atual.usuario, "quit");
                if(cmpQuit == 0){
                    break;
                }
                printf("> Senha:   ");
                scanf("%s",&user_atual.senha);
                fflush(stdin);
                int cmpSenha = strcmp(user_atual.senha, AdmSenha);
                Animation();
                bool contaReal = false;     // Serve como verificador de exist�ncia das contas (Por padr�o � false)
                bool senhaErrada = false;   // Serve como verificador de senhas por usu�rio    (Por padr�o � false)
                // Loop de repeti��o em for para checar usu�rio por usu�rio para ver se ele existe ou n�o
                for(i = 0; i < cPassUsers; i++){
                    if(strcmp(user_atual.usuario,PassUsers[i][2]) == 0){
                        contaReal = true;
                        strcpy(user_atual.nome,PassUsers[i][0]);
                        strcpy(user_atual.telefone,PassUsers[i][1]);
                        strcpy(user_atual.endereco[0],Enderecos[i][0]);
                        strcpy(user_atual.endereco[1],Enderecos[i][1]);
                        user_atual.ID = i;
                    }
                    if(strcmp(user_atual.usuario,PassUsers[i][2]) == 0 && strcmp(user_atual.senha,PassUsers[i][3]) != 0){
                        senhaErrada = true;
                    }
                    if(contaReal == true){
                        break;
                    }
                }

                // Verifica��o de exist�ncia de USER
                if(contaReal == false && cpmUser != 0 && cmpSenha != 0 && strcmp(user_atual.usuario,FuncUser) != 0 && strcmp(user_atual.senha,FuncSenha) != 0){
                    strcenter(line,RED"- Essa conta n�o existe! -"RST,32,true);
                    char SN;    // Sim e N�o
                    printf("Deseja criar uma conta?\n> ");
                    SN = getch();
                    Sleep(20);
                    printf("%c\n",SN);
                    if(SN == 'S' || SN == 's'){
                        // Nome do cliente
                        int ValChar;
                        do{
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome: ");
                            gets(PassUsers[cPassUsers][0]);
                            fflush(stdin);
                            ValChar = ValInfo(PassUsers[cPassUsers][0][0],AlphaNums);
                        } while (strlen(PassUsers[cPassUsers][0]) == 0 || ValChar == 0);
                       
                        // N�mero de telefone
                        bool valTelefone = false;
                        do{
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome: %s\n",PassUsers[cPassUsers][0]);
                            printf("> Telefone (com DDD): ");
                            scanf("%s",&PassUsers[cPassUsers][1]);
                            fflush(stdin);
                            int Counts = 0;
                            int j;
                            // Loop para verificar exist�ncia de n�meros (S� acontece se o tamanho for exatamente igual a 11 (DDD + Telefone))
                            if(strlen(PassUsers[cPassUsers][1]) == 11){
                                for(i = 0; i < 11; i++){
                                    for(j = 0; j < 10; j++){
                                        if(PassUsers[cPassUsers][1][i] == nums[j]){
                                            Counts++;
                                        }
                                    }
                                }
                            }

                            if(Counts == 11){
                                valTelefone = true;
                            }
                            else{
                                // Mensagem de erro para n�meros de telefones inv�lidos
                                strcenter(line,RED"- ERROR: Telefone inv�lido -"RST,32,true);
                                Sleep(600);
                            }
                        } while (valTelefone != true);
                        
                        // Usu�rio
                        //int ValChar;
                        bool contaUnica = false; // Serve como verificador de contas repetidas
                        do{
                            int rpConta = 0; // Serve como um contador (Se for maior ou igual a 2, o sistema vai considerar a conta como repetida)
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome:     %s\n",PassUsers[cPassUsers][0]);
                            printf("> Telefone:     %s\n",PassUsers[cPassUsers][1]);
                            printf("> Usu�rio:      ");
                            gets(PassUsers[cPassUsers][2]);
                            fflush(stdin);
                            ValChar = ValInfo(PassUsers[cPassUsers][2][0],AlphaNums);
                            for(i = 0; i < cPassUsers+1; i++){
                                if(strcmp(PassUsers[cPassUsers][2],PassUsers[i][2]) == 0){
                                    rpConta++;
                                }
                            }
                            if(rpConta == 2){
                                contaUnica = false;
                                strcenter(line,RED"- ERROR: USU�RIO INDISPON�VEL! -"RST,32,true);
                                Sleep(800);
                            }
                            else if(strcmp(PassUsers[cPassUsers][2]," ") == 0 || ValChar == 0){
                                contaUnica = false;
                                strcenter(line,RED"- ERROR: USU�RIO INV�LIDO! -"RST,32,true);
                                Sleep(800);
                            }
                            else{
                                contaUnica = true;
                                break;
                            }
                        } while (contaUnica != true);
                        
                        do{
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome:     %s\n",PassUsers[cPassUsers][0]);
                            printf("> Telefone:     %s\n",PassUsers[cPassUsers][1]);
                            printf("> Usu�rio:      %s\n",PassUsers[cPassUsers][2]);
                            printf("> Senha:        ");
                            gets(PassUsers[cPassUsers][3]);
                            fflush(stdin);
                            ValChar = ValInfo(PassUsers[cPassUsers][3][0],AlphaNums);
                        } while (strlen(PassUsers[cPassUsers][3]) == 0 || ValChar == 0);
                        
                        
                        do{
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome:     %s\n",PassUsers[cPassUsers][0]);
                            printf("> Telefone:     %s\n",PassUsers[cPassUsers][1]);
                            printf("> Usu�rio:      %s\n",PassUsers[cPassUsers][2]);
                            printf("> Senha:        %s\n",PassUsers[cPassUsers][3]);
                            printf("> Sua cidade:   ");
                            gets(Enderecos[cPassUsers][0]);
                            fflush(stdin);
                            ValChar = ValInfo(Enderecos[cPassUsers][0][0],AlphaNums);
                        } while (strlen(Enderecos[cPassUsers][0]) == 0 || ValChar == 0);
                        do{
                            system("cls");
                            strcenter(line,"- CRIA��O DE CONTA! -",32,false);
                            printf("> Seu nome:     %s\n",PassUsers[cPassUsers][0]);
                            printf("> Telefone:     %s\n",PassUsers[cPassUsers][1]);
                            printf("> Usu�rio:      %s\n",PassUsers[cPassUsers][2]);
                            printf("> Senha:        %s\n",PassUsers[cPassUsers][3]);
                            printf("> Sua cidade:   %s\n",Enderecos[cPassUsers][0]);
                            printf("> Seu endere�o: ");
                            gets(Enderecos[cPassUsers][1]);
                            fflush(stdin);
                            ValChar = ValInfo(Enderecos[cPassUsers][1][0],AlphaNums);
                        } while (strlen(Enderecos[cPassUsers][1]) == 0 || ValChar == 0);
                        cPassUsers++;
                        strcenter(line,GRN"- CONTA CRIADA COM SUCESSO -"RST,32,true);
                        Sleep(600);
                    }
                }

                // ADM
                if(cpmUser == 0 && cmpSenha == 0){
                    strcenter(line,GRN"Logado com Sucesso!"RST,32,true);
                    Sleep(600);
                    int option = 0;
                    do{
                        viewMenu(AdmMenu,line,32);
                        option = getch();
                        Sleep(20);
                        if(option >= 48 && option <= 57){
                            option = option%48;
                        }
                        system("cls");
                        int NavOpt, ValChar;
                        switch (option) {
                            case 1:
                                strcenter(line,"Informa��o das lojas",32,false);
                                for (i = 0; i < 3; i++){
                                    printf("> %s\n",lojas.Cidades[i]);
                                    printf("Endereco:      %s\n",lojas.Enderecos[i]);
                                    printf("Salas da loja: %i\n",lojas.Salas[i]);
                                    printf("Empregados:    %i\n",lojas.Empregados[i]);
                                    printf("%s\n",line);
                                }
                                system("PAUSE");
                                break;

                            case 2:
                                viewLojas(lojas,line,32);
                                break;

                            case 3:
                                viewPedidos(logins,line);
                                break;

                            case 4:
                                do{
                                    system("cls");
                                    strcenter(line,"- Informa��es de acesso! -",32,false);
                                    printf("1. Acesso de Admin:\n");
                                    printf("> Usu�rio: %s\n",AdmUser);
                                    printf("> Senha:   %s\n\n",AdmSenha);
                                    printf("2. Acesso de funcion�rio:\n");
                                    printf("> Usu�rio: %s\n",FuncUser);
                                    printf("> Senha:   %s\n\n",FuncSenha);
                                    printf("3. Voltar\n");
                                    printf("%s\n> ",line);
                                    NavOpt = getch();
                                    printf("%c",NavOpt);
                                    Sleep(20);
                                    if(NavOpt >= 48 && NavOpt <= 57){ // 0 a 9 s�o respectivamente as teclas de n�mero 48 a 57 do teclado
                                        NavOpt = NavOpt%48;
                                    }

                                    if(NavOpt == 1){
                                        ValChar = 0;
                                        do{
                                            system("cls");
                                            strcenter(line,"- Modifca��o de conta de administrador -",32,false);
                                            printf("> Novo usu�rio: ");
                                            scanf("%s",&AdmUser);
                                            ValChar = ValInfo(AdmUser[0],AlphaNums);
                                            if(ValChar == 0){
                                                strcenter(line,RED"- ERROR: USU�RIO INV�LIDO -"RST,32,true);
                                                Sleep(800);
                                            }
                                        } while (ValChar == 0);
                                        
                                        ValChar = 0;
                                        do{
                                            system("cls");
                                            strcenter(line,"- Modifca��o de conta de administrador -",32,false);
                                            printf("> Novo usu�rio: %s\n",AdmUser);
                                            printf("> Nova senha:   ");
                                            scanf("%s",&AdmSenha);
                                            ValChar = ValInfo(AdmSenha[0],AlphaNums);
                                            if(ValChar == 0){
                                                strcenter(line,RED"- ERROR: SENHA INV�LIDA -"RST,32,true);
                                                Sleep(800);
                                            }
                                        } while (ValChar == 0);
                                        fflush(stdin);
                                    }

                                    else if(NavOpt == 2){
                                        ValChar = 0;
                                        do{
                                            system("cls");
                                            strcenter(line,"- Modifca��o de conta de funcion�rio -",32,false);
                                            printf("> Novo usu�rio: ");
                                            scanf("%s",&FuncUser);
                                            ValChar = ValInfo(FuncUser[0],AlphaNums);
                                            if(ValChar == 0){
                                                strcenter(line,RED"- ERROR: USU�RIO INV�LIDO -"RST,32,true);
                                                Sleep(800);
                                            }
                                        } while (ValChar == 0);
                                        
                                        ValChar = 0;
                                        do{
                                            system("cls");
                                            strcenter(line,"- Modifca��o de conta de funcion�rio -",32,false);
                                            printf("> Novo usu�rio: %s\n",FuncUser);
                                            printf("> Nova senha:   ");
                                            scanf("%s",&FuncSenha);
                                            ValChar = ValInfo(FuncSenha[0],AlphaNums);
                                            if(ValChar == 0){
                                                strcenter(line,RED"- ERROR: SENHA INV�LIDA -"RST,32,true);
                                                Sleep(800);
                                            }
                                        } while (ValChar == 0);
                                        fflush(stdin);
                                    }

                                    else if(NavOpt == 3 || NavOpt == 27){
                                        break;
                                    }
                                    else{
                                        strcenter(line,RED"- ERROR: OP��O INV�LIDA! -"RST,32,true);
                                        Sleep(800);
                                    }
                                } while (NavOpt != 3 && NavOpt != 27);
                                break;
                            
                            case 5:
                                break;   
                            
                            default:
                                break;
                        }
                        system("cls");
                    } while(option != 5);
                    user_atual.logado = true;
                }
                
                // Verifica��o de login para ADM e USER
                else if(cpmUser == 0 && cmpSenha != 0 && contaReal == true || senhaErrada == true){
                    strcenter(line,RED"- Senha Incorreta! -"RST,32,true);
                    Sleep(600);
                }

                // USER
                else if(cpmUser != 0 && contaReal == true && senhaErrada == false){
                    sprintf(UserMenu.title,"- Bem Vindo %s -",user_atual.usuario);
                    strcenter(line,GRN"Logado com Sucesso!"RST,32,true);
                    Sleep(600);
                    do{
                        int option = 0;
                        viewMenu(UserMenu,line,32);
                        option = getch();
                        Sleep(20);
                        if(option >= 48 && option <= 57){
                            option = option%48;
                        }
                        system("cls");
                        if (option != 6 && option != 27){
                            if (option == 1){
                                int CodePizza;
                                do{
                                    viewPizzas(pizzas,line2,32);
                                    printf("Escolha uma pizza! (Pressione ESC para voltar)\n> ");
                                    CodePizza = getch(); // 65 a 90 || 97 a 122 (Alfabeto para getch())
                                    Sleep(20);
                                    if(CodePizza >= 65 && CodePizza <= 90){ // Caixa alta
                                        printf("%c\n",CodePizza);
                                        CodePizza %= 65;
                                    }
                                    else if(CodePizza >= 97 && CodePizza <= 122){ // Letra min�scula
                                        printf("%c\n",toupper(CodePizza));
                                        CodePizza %= 97;
                                    }
                                    else if(CodePizza == 27){ // 27 == Esc
                                        printf("\b\b");
                                        break;
                                    }
                                    else{
                                        CodePizza = 100;
                                    }

                                    system("cls");
                                    if(CodePizza <= pizzas.QntGeral - 1){
                                        char titlePizza[100];
                                        sprintf(titlePizza,"Sabor: %s",pizzas.geral[CodePizza][0]);
                                        strcenter(line2,titlePizza,32,false);
                                        printf("%s\n%s\n",pizzas.geral[CodePizza][1],line2);
                                        system("PAUSE");
                                        system("cls");

                                        int select = 0;
                                        do{
                                            viewTamanhosPizza(line2,pizzas.precos,pizzas.tamanhos,pizzas.geral[(CodePizza)][0]);
                                            printf("> ");
                                            select = getch();
                                            Sleep(20);
                                            if(select >= 48 && select <= 57){
                                                select = select%48;
                                            }
                                            if(select > 3){
                                                system("cls");
                                            }
                                        } while(select > 3 || select == 0);

                                        int quantidade = 0;
                                        do{
                                            viewTamanhosPizza(line2,pizzas.precos,pizzas.tamanhos,pizzas.geral[(CodePizza)][0]);
                                            printf("Quantas pizzas %s (%s) ser�o pedidas?\n> ",pizzas.geral[(CodePizza)][0],pizzas.tamanhos[select-1]);
                                            scanf("%i",&quantidade);
                                            fflush(stdin);
                                            printf("%s\n",line2);
                                            if (quantidade <= 0){
                                                system("cls");
                                            }
                                        } while (quantidade <= 0);

                                        user_atual.total += pizzas.precos[select-1]*quantidade;
                                        user_atual.Pizzas[user_atual.Contador] = pizzas.geral[(CodePizza)][0];
                                        user_atual.Tamanhos[user_atual.Contador] = pizzas.tamanhos[select-1];
                                        user_atual.quantidade[user_atual.Contador] = quantidade;
                                        user_atual.Contador += 1;

                                        system("PAUSE");
                                    }
                                }while(CodePizza != 27);
                            }
                            
                            else if(option == 2){
                                strcenter(line,"Revis�o do pedido",32,false);
                                for(i = 0; i < user_atual.Contador; i++){
                                    printf("> %s (%i %s)\n", user_atual.Pizzas[i],user_atual.quantidade[i],user_atual.Tamanhos[i]);
                                }
                                printf("> Total: R$ %.2f\n%s\n",user_atual.total,line);
                                system("PAUSE");
                            }
                            
                            else if(option == 3){
                                strcenter(line,"- Localiza��o das pizzarias -",32,false);
                                for(i = 0; i < 3; i++){
                                    printf("> %s: %s\n",lojas.Cidades[i],lojas.Enderecos[i]);
                                }
                                printf("%s\n",line);
                                system("PAUSE");
                            }

                            else if(option == 4){
                                int ValChar;
                                strcenter(line,"- Cadastro de endere�o -",32,false);
                                printf("Sua cidade:   %s\n",user_atual.endereco[0]);
                                printf("Seu endere�o: %s\n",user_atual.endereco[1]);
                                printf("%s\n",line);
                                char SN;
                                printf("Deseja mudar seu endere�o?\n> ");
                                SN = getch();
                                Sleep(20);
                                printf("%c\n",SN);
                                if(SN == 'S' || SN == 's'){
                                    do{
                                        system("cls");
                                        strcenter(line,"- Cadastro de endere�o -",32,false);
                                        printf("Digite sua cidade\n> ");
                                        gets(user_atual.endereco[0]);
                                        ValChar = ValInfo(user_atual.endereco[0][0],AlphaNums);
                                    } while (strlen(user_atual.endereco[0]) == 0 || ValChar == 0);
                                    do{
                                        system("cls");
                                        strcenter(line,"- Cadastro de endere�o -",32,false);
                                        printf("Digite seu endere�o\n> ");
                                        gets(user_atual.endereco[1]);
                                        ValChar = ValInfo(user_atual.endereco[1][0],AlphaNums);
                                    } while (strlen(user_atual.endereco[1]) == 0 || ValChar == 0);
                                }
                                printf("%s\n",line);
                                system("PAUSE");
                            }

                            else if(option == 5){
                                int ValChar;
                                strcenter(line,"- Informa��es da sua conta -",32,false);
                                printf("> Seu nome: %s\n",user_atual.nome);
                                printf("> Endere�o: %s (%s)\n",user_atual.endereco[1], user_atual.endereco[0]);
                                printf("> Telefone: %s\n",user_atual.telefone);
                                printf("> Usu�rio:  %s\n",user_atual.usuario);
                                printf("> Senha:    %s\n",user_atual.senha);
                                printf("%s\n",line);
                                char SN;
                                printf("Dseja mudar alguma informa��o?\n> ");
                                SN = getch();
                                Sleep(20);
                                printf("%c\n",SN);
                                if(SN == 'S' || SN == 's'){
                                    char InfoOpt;
                                    do{
                                        viewMenu(AccMenu,line,32);
                                        InfoOpt = getch();
                                        Sleep(20);
                                        printf("%c\n",InfoOpt);
                                        if(InfoOpt == '1'){
                                            ValChar = 0;
                                            char newName[100];
                                            do{
                                                system("cls");
                                                strcenter(line,"- Informa��es da sua conta -",32,false);
                                                printf("> Nome Antigo: %s\n",user_atual.nome);
                                                printf("> Nome novo: ");
                                                gets(newName);
                                                ValChar = ValInfo(newName[0],AlphaNums);
                                                if(strlen(newName) > 0 && ValChar != 0){
                                                    strcpy(user_atual.nome,newName);
                                                    fflush(stdin);
                                                    strcpy(PassUsers[user_atual.ID][0],newName);
                                                    fflush(stdin);
                                                    strcenter(line,GRN"- Nome trocado com sucesso -"RST,32,true);
                                                    Sleep(600);
                                                    break;
                                                }
                                                else if(strcmp(newName,"voltar") == 0){
                                                    strcenter(line,"- Voltando para tela anterior -",32,false);
                                                    Sleep(600);
                                                }
                                                else{
                                                    strcenter(line,RED"- ERROR: NOME INV�LIDO -"RST,32,true);
                                                    Sleep(600);
                                                }
                                            } while (strlen(newName) == 0 || ValChar == 0);
                                        }

                                        else if(InfoOpt == '2'){
                                            ValChar = 0;
                                            bool valTelefone = false;
                                            char newPhone[100];
                                            do{
                                                system("cls");
                                                strcenter(line,"- Informa��es da sua conta -",32,false);
                                                printf("> Telefone antigo: %s",user_atual.telefone);
                                                for(i = 0; i < strlen(user_atual.endereco[0]); i++){
                                                    printf("\b");
                                                }
                                                printf("\n");
                                                printf("> Telefone novo: ");
                                                gets(newPhone);
                                                int Counts = 0;
                                                int j;
                                                // Loop para verificar exist�ncia de n�meros (S� acontece se o tamanho for exatamente igual a 11 (DDD + Telefone))
                                                if(strlen(newPhone) == 11){
                                                    for(i = 0; i < 11; i++){
                                                        for(j = 0; j < 10; j++){
                                                            if(newPhone[i] == nums[j]){
                                                                Counts++;
                                                            }
                                                        }
                                                    }
                                                }
                                                if(Counts == 11){
                                                    valTelefone = true;
                                                    strcpy(user_atual.telefone,newPhone);
                                                    fflush(stdin);
                                                    strcpy(PassUsers[user_atual.ID][1],newPhone);
                                                    fflush(stdin);
                                                }
                                                else{
                                                    // Mensagem de erro para n�meros de telefones inv�lidos
                                                    strcenter(line,RED"- ERROR: Telefone inv�lido -"RST,32,true);
                                                    Sleep(600);
                                                }
                                            } while (valTelefone != true);
                                            system("cls");
                                            strcenter(line,"- Informa��es da sua conta -",32,false);
                                            printf("> Telefone novo: %s\n",user_atual.telefone);
                                            strcenter(line,GRN"- TELEFONE TROCADO COM SUCESSO -"RST,32,true);
                                            Sleep(1000);
                                        }

                                        else if(InfoOpt == '3'){
                                            ValChar = 0;
                                            char newUser[100];
                                            do{
                                                system("cls");
                                                strcenter(line,"- Informa��es da sua conta -",32,false);
                                                printf("> Usu�rio Antigo: %s\n",user_atual.usuario);
                                                printf("> Usu�rio novo:   ");
                                                gets(newUser);
                                                ValChar = ValInfo(newUser[0],AlphaNums);
                                                if(strlen(newUser) > 0 && ValChar != 0){
                                                    strcpy(user_atual.usuario,newUser);
                                                    fflush(stdin);
                                                    strcpy(PassUsers[user_atual.ID][2],newUser);
                                                    fflush(stdin);
                                                    strcenter(line,GRN"- Usu�rio trocado com sucesso -"RST,32,true);
                                                    Sleep(600);
                                                    break;
                                                }
                                                else if(strcmp(newUser,"voltar") == 0){
                                                    strcenter(line,"- Voltando para tela anterior -",32,false);
                                                    Sleep(600);
                                                }
                                                else{
                                                    strcenter(line,RED"- ERROR: Usu�rio INV�LIDO -"RST,32,true);
                                                    Sleep(600);
                                                }
                                            } while (strlen(newUser) == 0 || ValChar == 0);
                                            system("cls");
                                            strcenter(line,"- Informa��es da sua conta -",32,false);
                                            printf("> Usu�rio novo: %s\n",user_atual.usuario);
                                            strcenter(line,GRN"- USU�RIO TROCADO COM SUCESSO -"RST,32,true);
                                            Sleep(1000);
                                        }
                                        
                                        else if(InfoOpt == '4'){
                                            ValChar = 0;
                                            char newPass[100];
                                            do{
                                                system("cls");
                                                strcenter(line,"- Informa��es da sua conta -",32,false);
                                                printf("> Senha Antiga: %s\n",user_atual.senha);
                                                printf("> Senha nova:   ");
                                                gets(newPass);
                                                ValChar = ValInfo(newPass[0],AlphaNums);
                                                if(strlen(newPass) > 0 && ValChar != 0){
                                                    strcpy(user_atual.senha,newPass);
                                                    fflush(stdin);
                                                    strcpy(PassUsers[user_atual.ID][3],newPass);
                                                    fflush(stdin);
                                                    strcenter(line,GRN"- Senha trocado com sucesso -"RST,32,true);
                                                    Sleep(600);
                                                    break;
                                                }
                                                else if(strcmp(newPass,"voltar") == 0){
                                                    strcenter(line,"- Voltando para tela anterior -",32,false);
                                                    Sleep(600);
                                                }
                                                else if(strlen(newPass) == 0 || ValChar == 0){
                                                    strcenter(line,RED"- ERROR: SENHA INV�LIDO -"RST,32,true);
                                                    Sleep(600);
                                                }
                                            } while (strlen(newPass) == 0 || ValChar == 0);
                                            system("cls");
                                            strcenter(line,"- Informa��es da sua conta -",32,false);
                                            printf("> Senha nova: %s\n",user_atual.senha);
                                            strcenter(line,GRN"- SENHA TROCADA COM SUCESSO -"RST,32,true);
                                            Sleep(1000);
                                        }
                                        
                                        else if(InfoOpt == '5'){
                                            break;
                                        }
                                        
                                        else{
                                            strcenter(line,RED"ERROR: OP��O INV�LIDA"RST,32,true);
                                            Sleep(750);
                                        }
                                    } while (InfoOpt != '5');
                                }
                            }
                        }

                        else {
                            if(user_atual.Contador > 0){
                                int selectEntrega;
                                do{
                                    system("cls");
                                    strcenter(line,"CONFIRMA��O DE PEDIDO",32,false);
                                    printf("Resumo do pedido:\n");
                                    for(i = 0; i < user_atual.Contador; i++){
                                        printf("> %s (%i %s)\n", user_atual.Pizzas[i],user_atual.quantidade[i],user_atual.Tamanhos[i]);
                                    }
                                    printf("> Total: R$ %.2f\n",user_atual.total);
                                    printf("%s\n",line);
                                    printf("1. Para retirada\n");
                                    printf("2. Para entrega\n");
                                    printf("Escolha uma op��o\n> ");
                                    selectEntrega = getch();
                                    Sleep(20);
                                    if(selectEntrega >= 48 && selectEntrega <= 57){
                                        selectEntrega = selectEntrega%48;
                                    }
                                } while (selectEntrega < 1 || selectEntrega > 2);
                                
                                if(selectEntrega == 1){
                                    int selectLoja;
                                    do{
                                        system("cls");
                                        strcenter(line,"Lojas dispon�veis para retirada!",32,false);
                                        for(i = 0; i < 3; i++){
                                            printf("%i. Pizzaria de %s\n",i+1,lojas.Cidades[i]);
                                            printf("Endere�o: %s\n\n",lojas.Enderecos[i]);
                                        }
                                        printf("%s\n",line);
                                        printf("Escolha uma das pizzarias\n> ");
                                        selectLoja = getch();
                                        Sleep(20);
                                        if(selectLoja >= 48 && selectLoja <= 57){
                                            selectLoja = selectLoja%48;
                                        }
                                        if(selectLoja >= 1 && selectLoja <= 3){
                                            lojas.Renda[selectLoja-1] += user_atual.total;
                                            lojas.Lucros[selectLoja-1] += user_atual.total;
                                            strcpy(user_atual.retirada,lojas.Cidades[selectLoja - 1]);
                                            break;
                                        }
                                    } while (selectLoja < 1 || selectLoja > 3);
                                }

                                else if(selectEntrega == 2){
                                    printf("\n%s\n",line);
                                    printf("Endere�o de entrega:\n");
                                    printf("> Cidade:   %s\n",user_atual.endereco[0]);
                                    printf("> Endere�o: %s\n",user_atual.endereco[1]);
                                    strcpy(user_atual.retirada,"Endere�o do cliente");
                                    printf("%s\n",line);
                                    system("PAUSE");
                                }
                            }    
                            break;
                        }
                    } while(option != UserMenu.Tamanho && option != 27);
                    user_atual.logado = true;
                    logins.sessoes[logins.numSessoes] = user_atual;
                    logins.numSessoes++;
                }

                // FUNC
                else if(strcmp(user_atual.usuario,FuncUser) == 0 && strcmp(user_atual.senha,FuncSenha) == 0){
                    strcenter(line,GRN"Logado com Sucesso!"RST,32,true);
                    Sleep(600);
                    sprintf(FuncMenu.title,"- Bem vindo %s -",FuncNome);
                    int funcNav;
                    do{
                        viewMenu(FuncMenu,line,32);
                        funcNav = getch();
                        if(funcNav >= 48 && funcNav <= 57){ // 0 a 9 s�o respectivamente as teclas de n�mero 48 a 57 do teclado
                            funcNav = funcNav%48;
                        }
                        printf("%i\n",funcNav);
                        Sleep(20);
                        system("cls");
                        if(funcNav == 1){
                            viewLojas(lojas,line,32);
                        }
                        else if(funcNav == 2){
                            viewEnderecos(Enderecos,PassUsers,cPassUsers,line,32);
                        }
                        else if(funcNav == 3){
                            viewPedidos(logins,line);
                        }
                        else if(funcNav == 4){
                            strcenter(line,"- Informa��es da conta -",32,false);
                            printf("> Nome:  %s\n",FuncNome);
                            printf("Usu�rio: %s\n",FuncUser);
                            printf("Senha:   %s\n",FuncSenha);
                            printf("Sal�rio: R$ %.2f\n",FuncSal);
                            printf("Horas:   %ih\n",FuncHoras);
                            printf("%s\n",line);
                            system("pause");
                        }
                        else if(funcNav == 5){
                            user_atual.logado = true;
                            break;
                        }
                    } while(funcNav != 27 && funcNav != 5);
                }
            } while(user_atual.logado != true);
        }
        
        else if (option == 3){
            viewContatos(line);
        }

        else if (option == 4){
            viewSobre(line);
        }

        else if (option == 5){
            printf("Saindo do sistema...\n%s\n",line);
            break;
        }
    } while(option != 5 && option != 27);
    return 0;
}
