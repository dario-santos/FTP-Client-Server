#include "msg.h"
#include <stdio.h>
#include <string.h>

int teste_msg_make_node(void);
int teste_msg_insert_node (void);
int teste_msg_find_node(void);
int teste_msg_max_id(void);
int teste_msg_remove_node(void);
int teste_msg_free (void);

int main()
{
	if(teste_msg_make_node() == 1){	
	printf("test_msg_make_node() - OK\n");
	}	
	
	else{
	printf("test_msg_make_node() - NOT OK\n");
	}
	
	if(teste_msg_insert_node() == 1){
	printf("test_msg_insert_node() - OK\n");
	}
	else{
	printf("test_msg_insert_node() - NOT OK\n");
	}

	if (teste_msg_find_node()==1){
	printf("test_msg_find_node() - OK\n");
	}
	else{
	printf("test_msg_find_node() - NOT OK\n");
	}

	if (teste_msg_max_id()==1){
	printf("teste_msg_max_id() - OK\n");
	}
	else{
	printf("test_msg_max_id() - NOT OK\n");
	}

	
	if(teste_msg_remove_node() == 1){	
	printf("test_msg_remove_node() - OK\n");
	}	
	
	else{
	printf("test_msg_remove_node() - NOT OK\n");
	}

	
	if(teste_msg_free()==1){
	printf("test_msg_free() - OK\n");
	}
	else{
	printf("test_msg_free() - NOT OK\n");
	}
	
}


int teste_msg_make_node(void)
{
	
	Msg *mensagem = msg_make_node(2, "ola");
	
	if(mensagem->id != 2)
	return 0;

	if(strcmp("ola", mensagem->content) != 0)
	return 0;

	return 1;
}




int teste_msg_insert_node(void)
{
	Msg *insert = msg_insert_node(NULL, msg_make_node(3,"ola"));
	Msg *aux = insert;
	int cnt = 0;

	while (aux != NULL)
	{
		if(3 == aux->id);
		break;	
		aux = aux->p_seg;
	}	
	
	if (aux == NULL){
		return 0;
	}
	
	if(aux->id != 3){
	return 0;
	}

	if (strcmp("ola", aux->content) != 0){
	return 0;
	}

	insert = msg_insert_node(insert, NULL);
	aux=insert;

	while (aux!=NULL){
		cnt++;
		aux= aux->p_seg;
	}
	
	if (cnt == 0){
		return 0;
	}

	return 1;
}
		
	
int teste_msg_free (void) 
{
	Msg *insert = msg_insert_node(NULL, msg_make_node(3,"ola"));
	insert = msg_free(insert);


	if (insert!=NULL){
	return 0;
	}	
	else {
	return 1;
	}
}

int teste_msg_find_node(void){
	Msg *insert = msg_insert_node(NULL, msg_make_node(3,"AAA"));
	insert = msg_insert_node(insert, msg_make_node(5,"BBB"));
	insert = msg_insert_node(insert, msg_make_node(4,"CCC"));


	Msg *aux = msg_find_node(insert, 5);

	if (strcmp("BBB", aux->content) != 0){
		return 0;
	}
	return 1;
}

int teste_msg_remove_node(void){
	Msg *mensagem = msg_insert_node(NULL, msg_make_node(3,"AAA"));
	mensagem = msg_remove_node (mensagem, mensagem);

	if (mensagem != NULL)
		return 0;

	return 1;
}

int teste_msg_max_id(void){
	Msg *insert = msg_insert_node(NULL, msg_make_node(3,"AAA"));
	insert = msg_insert_node(insert, msg_make_node(5,"BBB"));
	insert = msg_insert_node(insert, msg_make_node(4,"CCC"));


	int id = msg_max_id(insert);

	if ( id != 5){
		return 0;
	}
		
	return 1;

}


