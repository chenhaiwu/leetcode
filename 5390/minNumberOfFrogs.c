/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int g_hash[5];

bool CheckValid()
{
    if (g_hash[0] >= g_hash[1] &&
    g_hash[1] >= g_hash[2] &&
    g_hash[2] >= g_hash[3] &&
    g_hash[3] >= g_hash[4]
    ) {
        return true;
    }
    return false;
}

bool CheckValid2zero()
{
    if (g_hash[0] ==0  && 0 == g_hash[1] &&
    0 == g_hash[2] &&
    0 == g_hash[3] &&
    0 == g_hash[4]
    ) {
        return true;
    }
    return false;
}

int minNumberOfFrogs(char * s)
{
    int ans = -1;
    memset(g_hash, 0x0, sizeof(g_hash));
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'c') {
            g_hash[0]++;
            if (g_hash[0] > ans) {
                ans = g_hash[0];
            }
        } else if (s[i] == 'r') {
            g_hash[1]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'o') {
            g_hash[2]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'a') {
            g_hash[3]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'k') {
            g_hash[4]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
            g_hash[0]--;
            g_hash[1]--;
            g_hash[2]--;
            g_hash[3]--;
            g_hash[4]--;
        } else {
            ans = -1;
            break;
        }
    }
    if (CheckValid2zero()) return ans;
    else return -1;
}


int main()
{
    int ret;
    ret = minNumberOfFrogs("croakcroak");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("crcoakroak");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("croakcrook");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("croakcroa");
    printf("%d\n", ret);
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: chenhaiwu
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// #include "securec.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int g_hash[5];

bool CheckValid()
{
    if (g_hash[0] >= g_hash[1] &&
    g_hash[1] >= g_hash[2] &&
    g_hash[2] >= g_hash[3] &&
    g_hash[3] >= g_hash[4]
    ) {
        return true;
    }
    return false;
}

bool CheckValid2zero()
{
    if (g_hash[0] ==0  && 0 == g_hash[1] &&
    0 == g_hash[2] &&
    0 == g_hash[3] &&
    0 == g_hash[4]
    ) {
        return true;
    }
    return false;
}

int minNumberOfFrogs(char * s)
{
    int ans = -1;
    memset(g_hash, 0x0, sizeof(g_hash));
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'c') {
            g_hash[0]++;
            if (g_hash[0] > ans) {
                ans = g_hash[0];
            }
        } else if (s[i] == 'r') {
            g_hash[1]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'o') {
            g_hash[2]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'a') {
            g_hash[3]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
        } else if (s[i] == 'k') {
            g_hash[4]++;
            if (!CheckValid()) {
                ans = -1;
                break;
            }
            g_hash[0]--;
            g_hash[1]--;
            g_hash[2]--;
            g_hash[3]--;
            g_hash[4]--;
        } else {
            ans = -1;
            break;
        }
    }
    if (CheckValid2zero()) return ans;
    else return -1;
}


int main()
{
    int ret;
    ret = minNumberOfFrogs("croakcroak");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("crcoakroak");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("croakcrook");
    printf("%d\n", ret);
    ret = minNumberOfFrogs("croakcroa");
    printf("%d\n", ret);
    return 0;
}    return 0;
}