#ifndef STACKCELLA
#define STACKCELLA

typedef struct s_info{
	int riga;
	int colonna;
	int ricorsione;
  
} Info;

struct infoCelle{
  Info info;
  struct infoCelle *next;
};

typedef struct infoCelle* stackcella;


int push(stackcella *pstack, Info i);
int pop(stackcella *pstack, Info* i);
int is_empty(stackcella stack);
stackcella empty_stack();
void svuotastack (stackcella stack);
void print_stack2(stackcella l);
void print_stack(stackcella *l);
#endif

