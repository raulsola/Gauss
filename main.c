/* 
 * File:   main.c
 * Author: Rayssa & Raúl
 * Project: Metodo de eliminaçao de Gauss 2.0
 * Created on 15 de outubro de 2012, 19:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int gauss(int grau)
{   
    int tamLinha = grau, tamColuna = (grau+1);
    int i, j, y, l, c, x=0;
    double multiplicador[tamLinha-1], vetorTroca[tamColuna], matriz[tamLinha][tamColuna], matrizEsc[tamLinha][tamColuna], solucao[tamLinha]; 
    FILE *fp;
    
    
    fp = fopen("matriz.txt","r");
    
    for(i=0;i<tamLinha;i++)
    {
        for(j=0;j<tamColuna;j++)
        {
            fscanf(fp, "%lf", &matriz[i][j]);
        }
    }
    
    fclose(fp);
 
    //TROCA DE LINHAS    
    //Confere os elementos da primeira coluna, e ordena as linhas da matriz na ordem decrescente, segundo os elementos da primeira coluna. 
    //Se for 0, a linha é movida para a parte inferior da matriz.    
    for(i=tamLinha-1; i>0; i--)
    {
        if (((matriz[i-1][0]==0) && (matriz[i][0]!=0)) || ((matriz[i][0]>0) && (matriz[i-1][0]<matriz[i][0])))
        {           
            for(j=0; j<tamColuna;j++)
            {
                vetorTroca[j]= matriz[i][j];
                matriz[i][j]= matriz[i-1][j];
                matriz[i-1][j]= vetorTroca[j];
            }
            i=(tamLinha);
        }
    }    

    //Mostrar a matriz aumentada
    printf ("\nMatriz Aumentada: \n \n");
    for(i = 0; i < tamLinha; i++)
    {
        for(j = 0; j < tamColuna; j++)
        {
            if (j != (tamColuna - 1))
            {
                printf("| %lf ", matriz[i][j]);
            }
            else
            {
                printf(": %lf |", matriz[i][j]);
            }
        }        
        printf("\n");
    }

    //Copiar matriz a matrizEsc
    for(i=0; i<tamLinha; i++)
    {
        for(j=0; j<tamColuna; j++)
        {
            matrizEsc[i][j]=matriz[i][j];
        }
    }
    
    //Contruçao da soluçao do sistema triangular superior
    for(j=0; j<tamColuna; j++)
    {
        for(i=0; i<tamLinha; i++)
        {
            if((i>j) && (matriz[i][j] != 0))
            {                
                // calculando o  multiplicador
                multiplicador[x] = (matriz[i][j] / matriz[j][j]);
                //aplicando o multiplicador              
                for(y=j;y<tamColuna;y++)
                {
                    matrizEsc[i][y]= (matriz[i][y] - (multiplicador[x]*matriz[j][y]));
                }
                x++;
            }
        }        
        //Copiar matrizEsc a matriz
        for(l=0; l<tamLinha; l++)
        {
            for(c=0; c<tamColuna; c++)
            {
                matriz[l][c]=matrizEsc[l][c];
            }
        }        
        //Troca de linhas se o pivo for 0
        for(l=j+1; l<tamLinha; l++)
        {
            if((matriz[j+1][j+1]==0) && (matriz[l+1][j+1]!=0))
            {
                for(c=0; c<tamColuna; c++)
                {
                    vetorTroca[c]= matriz[j+1][c];
                    matriz[j+1][c]= matriz[l+1][c];
                    matriz[l+1][c]= vetorTroca[c];
                    l=(tamLinha);
                }
            }
        }
        x=0;
    }
    
    //Mostrar a matriz triangular
    printf ("\nMatriz Triangular Inferior: \n \n");
    for(i = 0; i < tamLinha; i++)
    {
        for(j = 0; j < tamColuna; j++)
        {
            if (j != (tamColuna - 1))
            {
                printf("| %lf ", matriz[i][j]);
            }
            else
            {
                printf(": %lf |", matriz[i][j]);
            }
        }        
        printf("\n");
    }
    
    //Resolver a equaçao    
    for(i=tamLinha-1;i>=0;i--)
    {
        for(j=tamColuna-1;j>=0;j--)
        {                 
            if(j==tamColuna-1)
                solucao[i]= matriz[i][j];

            if(i<j && j!=tamColuna-1)
                solucao[i]= (solucao[i] - (matriz[i][j] * solucao[j]));
            
            if(i==j)
                solucao[i]= (solucao[i] / matriz[i][j]);
        }
    }
    
    //Mostrar a Soluçao
    printf("\nSolução:");
    for(i=0;i<tamLinha;i++)
    {
        printf("\nx%d= %lf",i+1,solucao[i]);
    }       
}

int main() 
{
    setlocale(LC_ALL, "");
    
    int i, j, tam=0;
    char linea[999999];
    FILE *fp;
    
    printf("Resolução de Sistemas de Equações Lineares - Método de Eliminação de Gauss: \n");

    fp = fopen("matriz.txt","r");
    
    if(fp==NULL)
    {
        printf("O arquivo matriz.txt não pode ser lido!");
        exit(0);
    }
        
   
    fgets(linea, sizeof(linea), fp);

    for (i=0;i<(strlen(linea))-2;i++)
    {
        if (linea[i] == ' ' && i!=(strlen(linea))-3)
            tam++;
    }
    
    fclose(fp);
    
    gauss(tam);  
    
    getchar();
    getchar();
}

