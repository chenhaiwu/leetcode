#define Push(x, s)  (s[++top] = x)
#define Pop(s)      (s[top--])
#define IsStackEmpty (top == -1)
#define StackTop(s)     (s[top])

#define IsOption(ch) (ch == '&' || ch == '|' || ch == '!')
bool CalcBoolRes(char ch, char op, int cur)
{
    bool bFlag;
    if (ch == 't'){
        bFlag = true;
    } else {
        bFlag = false;
    }
    if (op == '!'){
        return !bFlag;
    } else if (cur == -1){
        return bFlag;
    }
    if (op == '&'){
        return cur & bFlag;
    } else if (op == '|'){
        return cur | bFlag;
    }
    return false;
}
//|(&(t,f,t), |(t,f,t), !(t), !(f))"
//ŸÏ¦Z¥ý«e‰]²z¡A¸I¨ì`ºâ²Å?©l?¥X?Õu¡A?ºâ§¹?ªG¦A??¡C
bool parseBoolExpr(char * expression){
    int expLen = (int)strlen(expression);
    char stack[expLen];
    int top = -1;
    for (int i = expLen - 1; i >= 0; i--) {
        char ch = expression[i];
        if (IsOption(ch)) {
            int cur = -1;
            char sCh;
            while (!IsStackEmpty && (sCh = Pop(stack)) != ')') {
                if (sCh == 't' || sCh == 'f'){
                    cur = CalcBoolRes(sCh, ch, cur);
                }
            }
            //printf("%d\n", cur);
            if (cur == true){
                Push('t', stack);
            } else {
                Push('f', stack);
            }
        } else {
            Push(ch, stack);
        }
    }
    return StackTop(stack) == 't';
}