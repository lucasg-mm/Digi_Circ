#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VAZIO 2

typedef struct porta{
	struct porta* esquerda;  //Aponta para o filho da esquerda.
	struct porta* direita;  //Aponta para o filho da direita.
	struct porta* anterior;  //Aponta para a porta anterior (no sentido da raiz).
	char valor_1;
	char valor_2;
	char tipo[10];  //Indica de que tipo é essa porta (AND, OR, ENTRADA, etc...). Também indica o índice da porta.
}PORTA;

PORTA** cria_ArvBin(){
	PORTA** raiz;
	
	raiz = (PORTA**)malloc(sizeof(PORTA*));  //Alocando espaço para a raiz.
	
	if(raiz == NULL){  //Erro de alocação.
		exit(1);  
	}
	
	else{  //raiz != NULL --> Alocação bem-sucedida.
		*raiz = NULL;  //Pois num primeiro momento a árvore se encontra vazia.
			
	    return raiz;
	}
}

PORTA** busca(PORTA** ponteiro, char* tipo_comparar){  //Busca em uma árvore não ordenada.
	PORTA** atual;
	
	if(strcmp((*ponteiro)->tipo, tipo_comparar) == 0){
		return ponteiro;
	}
	else{
		atual = NULL;
		if((*ponteiro)->esquerda != NULL){
			atual = busca(&((*ponteiro)->esquerda), tipo_comparar);
		}
		
		if(atual == NULL){  //Nada encontrado na sub-árvore esquerda.
			if((*ponteiro)->direita != NULL){
				atual = busca(&((*ponteiro)->direita), tipo_comparar);
			}
		}
		return atual;
	}	
}

void insere_zero(PORTA** raiz, char* descricao, int flag){  //Função de inserção na árvore correspondente ao modo 0.
	int i;
	
	if(flag == 0){  //Se for a primeira vez a entrar na função.
		PORTA* novo;  
		PORTA* filho1;
		PORTA* filho2;
		int valor_aux;
		
		//------------------------------------------------------------------------------------------------------
		
		novo = (PORTA*)malloc(sizeof(PORTA));  //Cria a raiz (1ª parte da entrada).
		
		if(novo == NULL){
			exit(0);  //Erro de alocação.
		}
		
		novo->esquerda = NULL;
		novo->direita = NULL;
		novo->anterior = NULL;
		novo->valor_1 = VAZIO;
		novo->valor_2 = VAZIO;
		for(i = 0; i < 3; i++){
			novo->tipo[i] = descricao[i]; //Preenche a descrição do primeiro nó.
		}
		
		*raiz = novo;  //PRIMEIRO NÓ DA ÁRVORE CRIADO! (faltam os dois filhos da entrada).
		
		//---------------------------------------------------------------------------------------------------------
		
		filho1 = (PORTA*)malloc(sizeof(PORTA));  //Cria o filho1.
		
		if(filho1 == NULL){
			exit(0);  //Erro de alocação.		
		}
		
		filho1->esquerda = NULL;
		filho1->direita = NULL;
		filho1->valor_1 = VAZIO;
		filho1->valor_2 = VAZIO;
		filho1->anterior = *raiz;
		for(i = 4; i < 7; i++){
			filho1->tipo[i-4] = descricao[i];
		}
		
		(*raiz)->esquerda = filho1;  //Conecta o filho1 ao restante da árvore.
		
		//---------------------------------------------------------------------------------------------------------
		
		filho2 = (PORTA*)malloc(sizeof(PORTA));  //Cria o filho2.
		
		if(filho2 == NULL){
			exit(0);  //Erro de alocação.
		}
		
		filho2->esquerda = NULL;
		filho2->direita = NULL;
		filho2->valor_1 = VAZIO;
		filho2->valor_2 = VAZIO;
		filho2->anterior = *raiz;
		for(i = 8; i < 11; i++){
			filho2->tipo[i-8] = descricao[i];
		}
		
		(*raiz)->direita = filho2;  //Conecta o filho2  ao restante da árvore.
		
		//----------------------------------------------------------------------------------------------------------
		
		//PRIMEIRA LINHA DE COMANDO IMPLEMENTADA NA ÁRVORE!
	}
	else{ //flag != 1 --> Se não for a primeira vez a entrar na função.
		PORTA** atual;
		PORTA* filho_esq;
		PORTA* filho_dir;  //Esses dois ponteiros cumprem a mesma função que "filho1" e "filho2" (do if acima). 
		char tipo_comp[10];
		
		tipo_comp[0] = descricao[0];
		tipo_comp[1] = descricao[1];
		tipo_comp[2] = descricao[2];
		
		//----------------------------------------------------------------------------------------------------------
		
		atual = busca(raiz, tipo_comp);  //Consulta a árvore binária e retorna o nó com o campo "tipo" correspondente. É diferente do kit de rotinas, pois é uma árvore não ordenada. 
		
		//----------------------------------------------------------------------------------------------------------
		
		filho_esq = (PORTA*)malloc(sizeof(PORTA));  //Cria o "filho_esq".
		
		if(filho_esq == NULL){
			exit(0);  //Erro de alocação.
		}
		
		filho_esq->esquerda = NULL;
		filho_esq->direita = NULL;
		filho_esq->anterior = *atual;
		filho_esq->valor_1 = VAZIO;
		filho_esq->valor_2 = VAZIO;
		for(i = 4; i < 7; i++){
			filho_esq->tipo[i-4] = descricao[i];
		}
		
		(*atual)->esquerda = filho_esq;
		
		//-----------------------------------------------------------------------------------------------------------
		
		if(descricao[8] == '\0'){  //Não existe o "filho_dir" (porta not). 
			return;
		}
		else{  //Existe o "filho_dir", então ele é criado.
			filho_dir = (PORTA*)malloc(sizeof(PORTA));
			
			if(filho_dir == NULL){
				exit(0);
			}
			
			filho_dir->esquerda = NULL;
			filho_dir->direita = NULL;
			filho_dir->anterior = *atual;
			filho_dir->valor_1 = VAZIO;
			filho_dir->valor_2 = VAZIO;
			for(i = 8; i < 11; i++){
				filho_dir->tipo[i-8] = descricao[i];
			}
			
			(*atual)->direita = filho_dir;
		}
	}	
	return;
}

void insere_um(PORTA** raiz, PORTA* atual, char* descricao, int flag){  //Essa flag informa quantas vezes o programa entrou recursivamente na função (mais ou menos como o "i" de um for).
	int foi_esq = 0;
	int erro = 0;
	
	if(flag == 0){  //Se for a primeira vez a entrar na função.
		PORTA* novo_r;
		
		novo_r = (PORTA*)malloc(sizeof(PORTA));  //Cria a raiz.
		
		if(novo_r == NULL){  //Erro de alocação.
			exit(0);  
		}
		
		novo_r->esquerda = NULL;
		novo_r->direita = NULL;
		novo_r->valor_1 = VAZIO;
		novo_r->valor_2 = VAZIO;
		novo_r->anterior=NULL;  //Pois trata-se da raiz.
		novo_r->tipo[0] = descricao[0];
		novo_r->tipo[1] = descricao[1];
		novo_r->tipo[2] = descricao[2];
		
		*raiz = novo_r;  //Atualiza a raiz.
		
		flag++;  //Para sinalizar que entrou uma vez na função.
		atual = *raiz; //Atualiza o nó da árvore selecionado.
		insere_um(raiz, atual, descricao, flag);  //Chama recursivamente a função outra vez.		
	}
	else{  //Se não for a primeira vez a entrar na função.
		PORTA* novo_esq;
		PORTA* novo_dir; 
		
		if((atual)->esquerda == NULL){  //Se o cursor não tiver um filho à esquerda.
			
			//-------------------------------------------------------------------------------------------------------
			
			novo_esq = (PORTA*)malloc(sizeof(PORTA));  //Cria filho à esquerda.
			
			if(novo_esq == NULL){  //Erro de alocação.
				exit(0); 
			}
			
			novo_esq->esquerda = NULL;
			novo_esq->direita = NULL;
			novo_esq->anterior = atual;
			novo_esq->valor_1 = VAZIO;
			novo_esq->valor_2 = VAZIO;
			novo_esq->tipo[0] = descricao[3*flag + 1*flag + 0];
			novo_esq->tipo[1] = descricao[3*flag + 1*flag + 1];
			novo_esq->tipo[2] = descricao[3*flag + 1*flag + 2];
			
			//-------------------------------------------------------------------------------------------------------
			
			(atual)->esquerda = novo_esq;  //Conecta à lista.
			foi_esq = 1;  //Sinaliza que entrou aqui.
			
			//-------------------------------------------------------------------------------------------------------
		}
		else{  //Se o cursor tiver um filho à esquerda.
			novo_dir = (PORTA*)malloc(sizeof(PORTA));  //Cria porta à direita.
			
			if(novo_dir == NULL){  //Erro de alocação
				exit(0);
			}
			
			novo_dir->esquerda = NULL;
			novo_dir->direita = NULL;
			novo_dir->valor_1 = VAZIO;
			novo_dir->valor_2 = VAZIO;
			novo_dir->anterior = atual;
			novo_dir->tipo[0] = descricao[3*flag + 1*flag + 0];
			novo_dir->tipo[1] = descricao[3*flag + 1*flag + 1];
			novo_dir->tipo[2] = descricao[3*flag + 1*flag + 2];
			
			//------------------------------------------------------------------------------------------------------
			
			(atual)->direita = novo_dir;  //Conecta à lista.
			
			//------------------------------------------------------------------------------------------------------
		}
		
		if(descricao[3*flag + 1*flag + 0] == 'E'){  //Se inseriu uma entrada.
			while((atual != NULL) && ((atual->direita != NULL) || (atual->tipo[0] == 'N'))){  //Atualiza "atual", que passa a ser a um nó que tem o campo "direita" nulo.
				atual = atual->anterior;
			}
			if(atual == NULL){
				erro = 1;  //A última entrada foi colocada.
			}						
		}
		else{  //Se não inseriu uma entrada.
			if(foi_esq == 1){  //Atualiza "atual", que passa a ser o próprio inserido.
				atual = atual->esquerda;
			}
			else{  
				atual = atual->direita;
			}
		}
		
		if(erro == 1){
			return;
		}
		else{
			flag++;
			insere_um(raiz, atual, descricao, flag);
		}
	}
}

int tabela_verdade(int entrada_1, int entrada_2, char porta){  //Aplica a tabela verdade em uma determinada porta.
	
	if(porta == 'N'){  //PORTA NOT.
		if(entrada_1 == 1){
			return 0;
		}
		if(entrada_1 == 0){
			return 1;
		}
	}
	
	if(porta == 'A'){  //PORTA AND.
		if((entrada_1 == 0) && (entrada_2 == 0)){
			return 0;
		}
		if((entrada_1 == 1) && (entrada_2 == 1)){
			return 1;
		}
		if((entrada_1 == 1) && (entrada_2 == 0)){
			return 0;
		}
		if((entrada_1 == 0) && (entrada_2 ==1)){
			return 0; 
		}
	}
	
	if(porta == 'O'){  //PORTA OR.
		if((entrada_1 == 0) && (entrada_2 == 0)){
			return 0;
		}
		if((entrada_1 == 1) && (entrada_2 == 1)){
			return 1;
		}
		if((entrada_1 == 1) && (entrada_2 == 0)){
			return 1;
		}
		if((entrada_1 == 0) && (entrada_2 ==1)){
			return 1; 
		}
	}
	
	if(porta == 'D'){  //PORTA NAND.
		if((entrada_1 == 0) && (entrada_2 == 0)){
			return 1;
		}
		if((entrada_1 == 1) && (entrada_2 == 1)){
			return 0;
		}
		if((entrada_1 == 1) && (entrada_2 == 0)){
			return 1;
		}
		if((entrada_1 == 0) && (entrada_2 == 1)){
			return 1; 
		}		
	}
	
	if(porta == 'R'){  //PORTA NOR.
		if((entrada_1 == 0) && (entrada_2 == 0)){
			return 1;
		}
		if((entrada_1 == 1) && (entrada_2 == 1)){
			return 0;
		}
		if((entrada_1 == 1) && (entrada_2 == 0)){
			return 0;
		}
		if((entrada_1 == 0) && (entrada_2 ==1)){
			return 0; 
		}		
	}
	
	if(porta == 'X'){  //PORTA XOR.
		if((entrada_1 == 0) && (entrada_2 == 0)){
			return 0;
		}
		if((entrada_1 == 1) && (entrada_2 == 1)){
			return 1;
		}
		if((entrada_1 == 1) && (entrada_2 == 0)){
			return 1;
		}
		if((entrada_1 == 0) && (entrada_2 ==1)){
			return 0; 
		}		
	}
}

int propaga_entradas(PORTA** raiz, char* entrada, int* indicador){  //Propaga os valores das entradas pelo circuito (indicador indica a qual elemento do vetor entrada o programa está se referindo). (em pós-ordem).
	int resultado;
	
	if(*raiz == NULL){
		return resultado;
	}
	
	//Para a sub-árvore esquerda.
	propaga_entradas(&(*raiz)->esquerda, entrada, indicador);
	
	//Para a sub-árvore direita.
	propaga_entradas(&(*raiz)->direita, entrada, indicador);
	
	//Preenchemos as entradas com seus valores:
	
	if((*raiz)->tipo[0] == 'E'){
		(*raiz)->valor_1 = entrada[*indicador];
		*indicador = *indicador + 2;
	}
	
	//Faz as operações
	
	if((((*raiz)->valor_1 != VAZIO) && ((*raiz)->valor_2 != VAZIO)) || ((*raiz)->tipo[0] == 'N')){  
		resultado = tabela_verdade(((*raiz)->valor_1 - '0'), ((*raiz)->valor_2 - '0'), (*raiz)->tipo[0]);
		
		(*raiz)->valor_1 = ('0' + resultado);
		(*raiz)->valor_2 = VAZIO;
	}
	
	if((*raiz)->anterior == NULL){
		return resultado;
	}
	
	//Recua os valores para os pais (se for not)
	
	if((*raiz)->anterior->tipo[0] == 'N'){  
		(*raiz)->anterior->valor_1 = (*raiz)->valor_1;
	}
	else{  //Se não for uma porta not.
		if((*raiz)->anterior->valor_1 == VAZIO){
		    (*raiz)->anterior->valor_1 = (*raiz)->valor_1;
		}
		else{
		   (*raiz)->anterior->valor_2 = (*raiz)->valor_1;
		}
	}
}

void limpa_circuito(PORTA** raiz){  //APAGA OS VALORES NO CIRCUITO APÓS O USO.
	if(*raiz == NULL){
		return;
	}
	
	//Para a sub-árvore esquerda.
	limpa_circuito(&(*raiz)->esquerda);
	
	//Para a sub-árvore direita.
	limpa_circuito(&(*raiz)->direita);
	
	//Agora, limpa-se os valores:
	
	(*raiz)->valor_1 = VAZIO;
	(*raiz)->valor_2= VAZIO;
}

int main(){
	//Declarações iniciais:
	int modo;  //Guarda o modo em que o programa rodará.
	char descricao[100];  //Essa string descreve como o circuito será montado. (Funciona mais ou menos como uma transição, pois os elementos desse vetor serão transferidos para a matriz 'nomes' de forma mais organizada)
	int linhas;  //Guarda o número de linhas que serão necessárias para montar o circuito (exclusivo para o modo 3-a).
	int i;  //Para uso em fors.
	int j;
	int flag;
	int testes;  //Guarda a quantidade de testes que o usuário deseja realizar.
	char entrada[100];  //Guarda uma entrada
	int resultado[50];  //Guarda os resultados depois de passar as entradas para a função.
	PORTA** raiz;  //Raiz da árvore binária.
	int valor;
	
	//Atribuições iniciais:
	
	testes = 0;
	j = 0;
	flag = 0;
	
	for(i = 0; i < 100; i++){
		entrada[i] = '\0';
	}
		
	//Funções iniciais:
	
	raiz = cria_ArvBin();  //Cria a árvore binária.
	
	//Principal interação do usuário:
	scanf("%d", &modo);  //O programa requisita ao usuário o modo em que o programa será rodado (3-a ou 3-b).
	
	if(modo == 0){  //Modo 3-a.
		scanf("%d", &linhas);  //O programa requisita o número de linhas necessárias para montar o circuito.
		setbuf(stdin, NULL);
		
		while(linhas != 0){
			for(i = 0; i < 100; i++){  //Limpa a string decisão.
				descricao[i] = '\0';
			}
			
			//Requisita os comandos:
			fgets(descricao, 100, stdin);
			insere_zero(raiz, descricao, flag); //Essa flag diz se está entrando na função pela primeira vez (igual a zero, se se sim)
			flag = 1;
			
			linhas--;  //Garante a saída do laço.			
		}
		
		scanf("%d", &testes);  //Requisita a quantidade de testes que o usuário deseja realizar. (O programa deve retornar a mesma quantidade de saídas).
		
		setbuf(stdin, NULL);
		
		while(testes != 0){
			for(i = 0; i < 100; i++){
				entrada[i] = '\0';
			}
			
			valor = 0;
			
			fgets(entrada, 100, stdin);  //Requisita as entradas do usuário (em binário).
			
			resultado[j] = propaga_entradas(raiz, entrada, &valor);  //Chama a função de propagação. (Retorna em entrada [0])
			
			limpa_circuito(raiz);			
			
			testes--;
			j++;
		}
		
		//Realiza a propagação dos resultados e exibe os resultados.
		
	}
	else{  //Se modo == 1 --> Modo 3-b.  (OBS*: necessita de um algoritmo recursivo).
		setbuf(stdin, NULL);
		
		fgets(descricao, 100, stdin);  //Requisita a descrição do circuito para o usuário, assim como o modo anterior.
		
	    insere_um(raiz, NULL, descricao, flag);  //Como aqui o algoritmo recursivo age, não é preciso montar a árvore por partes.
		
		scanf("%d", &testes);
		
		setbuf(stdin, NULL);
		
		while(testes != 0){  //Acumula as entradas e coloca numa função.
			for(i = 0; i < 100; i++){
				entrada[i] = '\0';
			}
			
			valor = 0;
			
			fgets(entrada, 100, stdin);  //Requisita as entradas do usuário (em binário).
			
			resultado[j] = propaga_entradas(raiz, entrada, &valor);  //Chama a função de propagação. (Retorna em entrada [0])
			
			limpa_circuito(raiz);
			
			testes--;
			j++;
		}
	}
	
	for(i = 0; i < j; i++){  //Exibe os resultados (imprime o vetor "resultado").
		printf("%d\n", resultado[i]);
	}	
	
	return 0;
}