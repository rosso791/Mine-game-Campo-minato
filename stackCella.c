#include<stdio.h>
#include<stdlib.h>
#include"stackCella.h"

int push(stackcella *pstack, Info i) {
  stackcella pc = (stackcella)malloc(sizeof(struct infoCelle));
  if (pc) {
    pc->next = *pstack;
    pc->info = i;
    *pstack = pc;
    return 1;
  }
  else 
    return 0;
}


int pop(stackcella *pstack, Info* i) {
  stackcella pc;
  if (*pstack) {
    pc = *pstack;
    *pstack = (*pstack)->next;
    *i = pc->info;
    free(pc);
    return 1;
  }
  else
    return 0;
}


int is_empty(stackcella stack) {
  return (stack == NULL);
}


stackcella empty_stack() {
  return NULL;
}

void svuotastack (stackcella stack){
	stackcella app = stack;
	while (app){
		stack = app->next;
		free(app);
		app = stack;	
	}
}


void print_stack2(stackcella l) {
  /*printf("Stack \n");*/
  while (l) {
      printf("stack %d      %d      %d\n", l->info.riga, l->info.colonna,l->info.ricorsione);
    l = l->next;
  }
}

void print_stack(stackcella *l) {
  /*printf("Stack \n");*/
  while (*l) {
      printf("stack %d      %d      %d\n", (*l)->info.riga, (*l)->info.colonna,(*l)->info.ricorsione);
    (*l) = (*l)->next;
  }
}

/* Main prova stack
int main(){
	Info a,l;
	stackcella c = empty_stack_exp();
	a.riga = 5;
	a.colonna = 6;
	push_exp(&c,a);
	print_stack_exp(c);
	pop_exp(&c,&l);
	print_stack_exp(c);
	printf("%d \n", l.riga);
    printf("%d \n", l.colonna);
	return 0;	
}*/


