
/*
 * context maintain here, 我选择简单点的ARM 32bit thumb上下文
 */
    .globl save_context
    .type save_context, %function
save_context:
    /*  r0 parameter: arm_context_t * pctx */
    stmia   r0, {r0-r12}        /* save r0 - r12, actully we no need save so many, 
                                  only respect AAPCS r0-r4, r12 is ok */
    str     sp, {r0, #52}        /* 4 * 13, (r0-r12) save sp to pctx->sp */
    str     r14, {r0, #56}
    str     pc,  {r0, #60}
.size save_context, .-save_context


    .globl restore_context
    .type restore_context, %function
restore_context:
    /*  r0 parameter: arm_context_t * pctx */
    ldr   r0, {r0, #0}              /* save r0 - r3, r12, actully we no need save so many, 
                                        only respect AAPCS r0-r4, r12 is ok */
    ldr   r1, {r0, #4}              /* 调用者保存r0-r3, r12 */
    ldr   r2, {r0, #8}
    ldr   r3, {r0, #12}
    ldr   r4, {r0, #16}
    ldr   r5, {r0, #48}
    ldr   sp, {r0, #52}             /* 4 * 13, (r0-r12) save sp to pctx->sp */
    ldr   lr, {r0, #56}             /* 4 * 13, (r0-r12) save sp to pctx->sp */
    ldr   pc, {r0, #60}             /* 注意pc 从协程的handlefun恢复，还有栈侦sp */
.size restore_context, .-restore_context