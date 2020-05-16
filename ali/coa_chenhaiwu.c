/*
 * chenhaiwu, 2020/3/11
*/

#include <stdio.h>
#include <stdlib.h>

#define DATAREGS_NUM 13
#define STACK_SIZE (8 * 1024)

typedef struct arm_context {
    int dataReg[DATAREGS_NUM];          /* r0-r12 实际上不需要保存这么多，follow ARM AAPCS 规范即可 */
    int sp;
    int lr;
    int pc;
} arm_context_t;

typedef int (*func_t) (void *arg);

typedef struct co {
    int coid;
    arm_context_t ctx;                  /* where cur co context to save */
    func_t HandlerFunc;
    void *stack;                        /* top of stack */
    void *bosAddr;                      /* bottom of stack */
    int stack_size;
} co_t;

co_t *g_co_a;
co_t *g_co_b;

co_t * co_create(func_t func, void *arg)
{
    co_t *pCo = (co_t *)calloc(1, sizeof(co_t));
    memset(pCo, 0x0, sizeof(co_t));
    pCo->coid = *(int *)arg;
    pCo->HandlerFunc = func;
    pCo->stack_size = STACK_SIZE;
    pCo->stack = calloc(1, pCo->stack_size);
    memset(pCo->stack, 0x0, STACK_SIZE);
    pCo->bosAddr = pCo->stack + STACK_SIZE;

    /* set sp & pc */
    pCo->ctx.sp = pCo->stack;
    pCo->ctx.pc = pCo->HandlerFunc;
}

/* 由于要算下stack sp的偏移，会影响代码可修改，直接嵌入式assemble*/
inline void init_context(co_t *to)
{
    /* 设置好栈的基址sp及lr */
    __asm__ volatile("ldr r14, %0": "=m"(to->ctx.lr) : : "memory");
    __asm__ volatile("ldr sp, %0": "=m"(to->ctx.sp) : : "memory");

    /* 设置当前pc为协程的HandlerFunc，r0为参数 */
    __asm__ volatile("mov r0, %0": "=m"(to->coid) : : "memory");
    __asm__ volatile("ldr pc, %0": "=m"(to->ctx.pc) : : "memory");
}

static int g_first_b = 1;
void do_switch(co_t *from, co_t *to)
{
    /* 注意保存from的上下文，包括SP及pc */
    save_context(from);

    if (g_first_b == 1) {
    /* 第一次切换到co_b，那么只要做init即可，初始栈底为sp，一次性，否则进下面分支*/
        init_context(to);
        g_first_b = 0;
    } else {
    /* from to的上下文中，恢复pc + sp，注意栈同样是要的，此时sp就不一定是栈底，是原来压栈的sp位置 */
        restore_context(to);
    }
}

void co_run(co_t *a)
{
    /* 初始化上下文，主要完成栈sp的栈底位置，当前协程的栈侦SP, PC = func 的设置 */
    init_context(a);

     /* Never come here */
    for (;;) {}
    return;
}

void co_yield(void *arg)
{
    int a = *(int *)arg;
    if (a == 1) {
        do_switch(g_co_a, g_co_b);
    } else if (a == 2) {
        do_switch(g_co_b, g_co_a);
    }
}

int co_func(void *arg)
{
	int id = (int)arg;
	
	while (1) {
		printf("co id: %d\n", id);
		co_yield(arg);
	}
	
	return 0;
}

int main(void)
{
	co_t *a = co_create(co_func, (void *)1);
	co_t *b = co_create(co_func, (void *)2);
	g_co_a = a;
    g_co_a = b;

	co_run(a);
	
	return 0;
}
