/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAX_N 1000

int check(char *src)
{
    int len = strlen(src);
    if (len == 0 || len > 3) {
        return 1;
    }

    switch (len) {
        case 1:
            break;
        case 2:
            if (src[0] == '0') {
                return 1;
            }
            break;
        case 3:
            if (src[0] <= '0' || src[0] > '2') {
                return 1;
            }

            if (src[0] == '2' && src[1] > '5') {
                return 1;
            }

            if (src[0] == '2' && src[1] == '5' && src[2] > '5') {
                return 1;
            }
        }
    return 0;
}


char ** restoreIpAddresses(char * s, int* returnSize)
{
    int len = strlen(s);
    int cnt = 0;
    char **ret = (char **)malloc(sizeof(char *) * MAX_N);
    memset(ret, 0x0, sizeof(char *) * MAX_N);
    char ip1[4] = {0};
    char ip2[4] = {0};
    char ip3[4] = {0};
    char ip4[4] = {0};

    for (int i = 1; i <= 3; i++) {
        memset(ip1, 0x0, 4);
        strncpy(ip1, &s[0], i);
        if (check(ip1) != 0) continue;
        for (int j = i + 1; j < len && j <= i + 3; j++) {
            memset(ip2, 0x0, 4);
            strncpy(ip2, &s[i], j - i);
            if (check(ip2) != 0) continue;
            for (int k = j + 1; k < len && k <= j + 3; k++) {
                memset(ip3, 0x0, 4);
                strncpy(ip3, &s[j], k - j);
                if (check(ip3) != 0) continue;
                memset(ip4, 0x0, 4);
                if (len - k > 3) continue;
                strncpy(ip4, &s[k], len - k);
                if (check(ip4) != 0) continue;
                ret[cnt] = (char *)malloc(20);
                memset(ret[cnt], 0, 20);
                sprintf(ret[cnt], "%s.%s.%s.%s", ip1, ip2, ip3, ip4);
                cnt++;
            }
        }
    }

    *returnSize = cnt;
    return ret;
}

#define LEN 100
bool is_valid_ip(char *s, int len)
{
    int num = 0;
    //len > 1 "0000"
    if (s[0] == '0' && len > 1) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        num = num * 10 + (s[i] - '0');
    }
    if (num > 255) {
        return false;
    }
    return true;
}

/*
* path: 记录中间结果
* depth: 总共有四层
*/
void dfs(char *s, int begin, int depth, char *path, char **ans, int *returnSize)
{
    if (depth > 4) {
        return;
    }
    if (depth > 0 && depth < 4) {
        path[begin++] = '.';
    }
    //这里的条件判断去除最后的数字大于4个
    if (s[0] == '\0' && depth == 4) {
        ans[*returnSize] =(char *)calloc(strlen(path) + 1, sizeof(char));
        strcpy(ans[*returnSize], path);
        (*returnSize)++;
        return;
    }

    for (int len = 1; len <= 3 && len <= strlen(s); len++) {
        if (is_valid_ip(s, len)) {
            // 这里相当于试探结果
            for (int i = 0; i < len; i++) {
                path[begin + i] = s[i];
            }
            dfs(s + len, begin + len, depth + 1, path, ans, returnSize);
            //这里相当于回溯
        }
    }
}
char ** restoreIpAddresses(char * s, int* returnSize){
    char **ans = (char **)calloc(LEN, sizeof(char *));
    char *path = (char *)calloc(strlen(s) + 4, sizeof(char *));
    int res_size = 0;
    dfs(s, 0, 0, path, ans, &res_size);
    *returnSize = res_size;
    return ans;
}