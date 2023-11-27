#include<string.h>
#include<stdio.h>
#include<stdlib.h>

char afn[50][50], s[20], es[10][20], efech[20], entrada[20];
int z,e,topo=0,topod=0,n=0,ne,nos,en;

int check(char a){
    int i = 0;
    while (i < en) {
    if (entrada[i] == a)
        return i;
    i++;
    }
    return -1;
}

void adiciona(char a){
    s[topo] = a;
    topo++;
}

char remove(){
    topo--;
    return s[topo];
}

void adicionad(char *a){
    strcpy(es[topod],a);
    topod++;
}

char *removed(){
    topod--;
    return es[topod];
}

int ctoi(char a){
    int i = a-48;
    return i;
}

char itoc(int a){
    char i = a + 48;
    return i;
}

char *efechamento(char *a){//A função eclosure recebe como parâmetro um conjunto de estados a e retorna o fecho transitivo desse conjunto considerando transições vazias ('e') em um afn
    int i, j;
    char c;
    for(i = 0; i < strlen(a); i++)//Adiciona cada estado do conjunto a à pilha s.
        adiciona(a[i]);
    e = strlen(a); //Inicializa a variável e com o comprimento do conjunto a.
    strcpy(efech, a); //Copia o conjunto a para a variável eclos, que será usada para armazenar o fecho transitivo.
        while(topo != 0){
            c = remove(); //Remove um estado do topo da pilha s e armazena em c.
            for(j = 0;j < ne;j++){
                if(afn[ctoi(c)][j] == 'e'){ // Verifica se há uma transição vazia de c para o estado j.
                    if(check(itoc(j) == -1)){//Verifica se o estado j ainda não foi adicionado ao fecho transitivo.
                        efech[e] = itoc (j);
                        adiciona(efech[e]);
                        e++;
                    }
                }
            }
        }
    efech[e] = '\0';
    return efech;
}

int main(){
    int i, j, k, count;
    char ef[50], a[20], b[20], c[20], destados[10][10];

    printf("Numero de estados:\n");
    scanf("%i", &ne);

    for(i = 0; i < ne; i++){// gerar uma matriz[ne][ne]
        for(j = 0;j < ne; j++){
            printf("Do estado q[%i] para o estado q[%i]", i, j);
            scanf("%s%*[^\n]", &afn[i][j]);
            
            if(afn[i][j] != '-' && afn [i][j] != 'e'){//se for diferente de vazio e de eplison 
                if((check(afn[i][j])) == -1)// verifica se é um valor valido
                    entrada[en++] = afn [i][j]; //valida o character // os valores validos estaram dentro do vetor entrada// Verifica se o símbolo da transição não está na 
                    //lista de símbolos de entrada. Se não estiver, adiciona à lista.
            }
        }
    }

    topod = 0;
    nos = 0;
    c[0]=itoc(0);
    c[1] = '\0';
    adicionad(efechamento(c));
    strcpy(destados[nos],efechamento(c)); // Copia o fecho transitivo do estado inicial para a matriz destados.
    for(z = 0; z < en; z++){
        printf("\t%c\t", entrada[z]);// exibir os símbolos de entrada.
    }
    printf("\n");
    while(topod>0){
        strcpy(a, removed());//  Início de um loop que continua até a pilha st estar vazia.
        printf("%s\t", a);
        for(i = 0; i < en; i++){
            int len = 0;
            for(j = 0; j<strlen(a); j++){
                int z=ctoi(a[j]);
                for(k = 0;k < ne; k++){
                    if(afn[z][k] == entrada[i])
                        ef[len++] = itoc(k);
                }
            }
            ef[len]='\0';
            strcpy(b,efechamento(c));
            count=0;
            for(j = 0;j <= nos; j++){
                if(strcmp(destados[j],b)==0)
                    count++;
            }
            if(count == 0){
                if(b[0] != '\0'){
                    nos++;
                    adicionad(b);
                    strcpy(destados[nos],b);
                }
            }
            printf("%s\t", b);
        }
        printf("\n");
    }
    return 0;
}