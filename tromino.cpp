/*

Alexandre Regali Seleghim	RA: 551473
Gustavo David Leite Bastos  RA: 551597


Problema do preenchimento da matriz (2^N)(2^N) com trominos.
	Resolvido por Divisao e Conquista.

*/

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

using namespace std;

//cor utilizada para pintar com o tromino
int cor = 3;

//coordenadas utilizadas para mover o cursor para o inicio do console
short int a = 0;
short int b = 0;
COORD pos = {a, b};


//funcao que inicializa a matriz vazia (com 0's)
void inicializa_vetor(vector< vector<int> >& tabela, int dimensao){

	dimensao = pow(2.0, (double)dimensao);

	vector<int> aux;

	for(int i = 0; i < dimensao; i++){
		aux.push_back(0);
	}

	for(int i = 0; i < dimensao; i++){
		tabela.push_back(aux);
	}

	return;
}


//funcao que desenha a matriz na tela

//	[celula] = 0	->	vazia
//	[celula] = 1	->	preenchida
void desenha_vetor(vector< vector<int> > tabela){

	int dimensao = tabela.size();

	//usado para limpar a tela E imprimir usando cores diferentes
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	//volta o cursor pro inicio do console (para eliminar o "flickering" causado pela funcao "system("CLS")"
	SetConsoleCursorPosition(hConsole, pos);
	//system("CLS");

	for(int i = 0; i < dimensao; i++){
		for(int j = 0; j < dimensao; j++){

            //se [celula] = 0	->	vazia
			if(tabela[i][j] == 0){

				SetConsoleTextAttribute(hConsole, 15);
				cout << (char)254 << " ";
			}

            //se [celula] = 1	->	preenchida
			if(tabela[i][j] == 1){

				SetConsoleTextAttribute(hConsole, cor);
				cout << (char)254 << " ";
			}
		}
		cout << "\n";
	}

    //restaura cor original do console
    SetConsoleTextAttribute(hConsole, 15);
    //pede um enter
	getchar();

	return;
}


//funcao recursiva que resolve o problema
//void tromino(&matriz, inicio_x, inicio_y, dimensao)
void tromino(vector< vector<int> >& tabela, int inicio_x, int inicio_y, int dimensao){ //METODO DE P.D.

	//caso base
	if(dimensao == 0){
		//desenha_vetor(tabela);
		return;
	}


	//descobrindo qual o tipo de Q (Q1, Q2, Q3, Q4)
	int Q = 0;

	//comparacao Q1
	if(tabela[inicio_x][inicio_y] == 0){
		if(tabela[inicio_x + pow(2.0, (double)dimensao) - 1][inicio_y] == 0){
			if(tabela[inicio_x][inicio_y + pow(2.0, (double)dimensao) - 1] == 0){
				if(tabela[inicio_x + pow(2.0, (double)dimensao) - 1][inicio_y + pow(2.0, (double)dimensao) - 1] == 0){
					Q = 1;
				}
			}
		}
	}

	//comparacao Q2
	if(tabela[inicio_x][inicio_y + pow(2.0, (double)dimensao) - 1] == 1){
		Q = 2;
	}

	//comparacao Q3
	if(tabela[inicio_x + pow(2.0, (double)dimensao) - 1][inicio_y] == 1){
		Q = 3;
	}

	//comparacao Q4
	if(tabela[inicio_x][inicio_y] == 1){
		Q = 4;
	}

	//comparacao Q5
	if(tabela[inicio_x + pow(2.0, (double)dimensao) - 1][inicio_y + pow(2.0, (double)dimensao) - 1] == 1){
		Q = 5;
	}

	//preenchendo os centros

	int c1 = inicio_x + pow(2.0, (double)dimensao - 1);
	int c2 = inicio_y + pow(2.0, (double)dimensao -1);

	//centro base
	tabela[c1][c2] = 1;

	//centros Q1
	if(Q == 1){
		tabela[c1][c2 - 1] = 1;
		tabela[c1 - 1][c2] = 1;
	}

	//centros Q2
	if(Q == 2){
		tabela[c1][c2 - 1] = 1;
		tabela[c1 - 1][c2 - 1] = 1;
	}

	//centros Q3
	if(Q == 3){
		tabela[c1 - 1][c2] = 1;
		tabela[c1 - 1][c2 - 1] = 1;
	}

	//centros Q4
	if(Q == 4){
		tabela[c1][c2 - 1] = 1;
		tabela[c1 - 1][c2] = 1;
	}

	//centros Q5
	if(Q == 5){
		tabela[c1][c2 - 1] = 1;
		tabela[c1 - 1][c2] = 1;
		tabela[c1 - 1][c2 - 1] = 1;
	}

	desenha_vetor(tabela);


	//chamadas recursivas

	//chamando Q1
	tromino(tabela, inicio_x, inicio_y, dimensao - 1);

	//chamando Q2
	tromino(tabela, inicio_x, inicio_y + pow(2.0, (double)dimensao - 1), dimensao - 1);

	//chamando Q3
	tromino(tabela, inicio_x + pow(2.0, (double)dimensao - 1), inicio_y, dimensao - 1);

	//chamando Q4
	tromino(tabela, inicio_x + pow(2.0, (double)dimensao - 1), inicio_y + pow(2.0, (double)dimensao - 1), dimensao - 1);



	return;
}

void tromino_dec(vector< vector<int> >& tabela, int dimensao) //METODO DE DECREMENTO E CONQUISTA
{
    int i,j,tamanho;
    bool pronto=false;
    desenha_vetor(tabela);
    tamanho=pow(2.0,(double)dimensao);
    //caso base
	if(tamanho==0)
    {
		//desenha_vetor(tabela);
		return;
	}
	else
    {
        if (tamanho>4)
        {
            i=tamanho-1;
            while(i>0)
            {
                j=tamanho-1;
                while (j>3)
                {
                    tabela[i][j]=1;
                    tabela[i][j-1]=1;
                    tabela[i-1][j]=1;
                    desenha_vetor(tabela);
                    j-=2;
                    tabela[i][j]=1;
                    tabela[i-1][j+1]=1;
                    tabela[i-1][j]=1;
                    desenha_vetor(tabela);
                    j-=1;
                }
                i-=2;
            }
            switch((dimensao%2))
            {
                case 1:
                    i=tamanho-1;
                    while (i>1)
                    {
                        tabela[i][0]=1;
                        tabela[i][1]=1;
                        tabela[i-1][1]=1;
                        desenha_vetor(tabela);
                        i--;
                        tabela[i][0]=1;
                        tabela[i-1][0]=1;
                        tabela[i-1][1]=1;
                        desenha_vetor(tabela);
                        i-=2;
                    }
                    tabela[i][0]=1;
                    tabela[i][1]=1;
                    tabela[i-1][1]=1;
                    desenha_vetor(tabela);
                    pronto=true;
                    break;
                case 0:
                    i=tamanho-1;
                    while(i>4)
                    {
                        tabela[i][0]=1;
                        tabela[i][1]=1;
                        tabela[i-1][0]=1;
                        desenha_vetor(tabela);
                        tabela[i][2]=1;
                        tabela[i][3]=1;
                        tabela[i-1][3]=1;
                        desenha_vetor(tabela);
                        i--;
                        tabela[i][1]=1;
                        tabela[i-1][1]=1;
                        tabela[i-1][0]=1;
                        desenha_vetor(tabela);
                        tabela[i][2]=1;
                        tabela[i-1][2]=1;
                        tabela[i-1][3]=1;
                        desenha_vetor(tabela);
                        i-=2;
                    }
                    break;
            }

        }
        if(!pronto&&tamanho>2)
        {
            tabela[0][1]=1;
            tabela[1][0]=1;
            tabela[1][1]=1;
            desenha_vetor(tabela);
            tabela[1][2]=1;
            tabela[2][2]=1;
            tabela[2][1]=1;
            desenha_vetor(tabela);
            tabela[2][3]=1;
            tabela[3][3]=1;
            tabela[3][2]=1;
            desenha_vetor(tabela);
            tabela[0][2]=1;
            tabela[0][3]=1;
            tabela[1][3]=1;
            desenha_vetor(tabela);
            tabela[2][0]=1;
            tabela[3][0]=1;
            tabela[3][1]=1;
            desenha_vetor(tabela);
            pronto=true;
        }
        else if (!pronto&&tamanho==2)
        {
            tabela[0][1]=1;
            tabela[1][0]=1;
            tabela[1][1]=1;
            desenha_vetor(tabela);
        }
    }
}



int main() {

    //METODOS Força Bruta (1) e Programação Dinâmica (2)
    int metodo;

    //TAMANHO DO TABULEIRO
    int tamanho;

	//coordenadas iniciais da nossa matriz
	int inicio_x = 0;
	int inicio_y = 0;

	//mensagem de instrucao
	cout << "(Utilize o botao [ENTER] para seguir passo a passo o algoritmo)\n\n";

	//pegando do usuario a dimensao da matriz
	string entrada;
	cout << "Entre com o tamanho de N para selecionar a dimensao da matriz (2 ^ N): ";
	cin >> entrada;

	int dimensao = atoi(entrada.c_str());
	//int dimensao = stoi(entrada);
    //int dimensao = 3;

	//criando e inicializando a matriz
	vector< vector<int> > tabela;
	inicializa_vetor(tabela, dimensao);

	//limpando a tela
	getchar();
	system("CLS");
    //desenhando a matriz inicial
	desenha_vetor(tabela);

    //ESCOLHENDO O METODO DE RESOLUÇÃO
    entrada="";
	cout << "Escolha o modo (1 - Decremento e Conquista ou 2 - Divisao e Conquista): ";
	cin >> entrada;
    getchar();
    system("CLS");

	metodo = atoi(entrada.c_str());
    switch(metodo)
    {
        case 1: //DECREMENTO E CONQUISTA
            tromino_dec(tabela, dimensao);
            break;
        case 2: //PROGRAMAÇÃO DINAMICA
            //primeira chamada da funcao recursiva que resolve o problema
            tromino(tabela, inicio_x, inicio_y, dimensao);
            break;
    }



	//imprimindo a mensagem final
	dimensao = pow(2.0, (double)dimensao);
	cout << "Matrix " << dimensao << "x" << dimensao << " preenchida com sucesso!" << endl;
	getchar();


	return 0;
}
