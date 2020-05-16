/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
 * Description: ¦Ò¥Í‰b?¥N?
 * Note: ¯Ê¬Ù¥N??¨Ñ‰ë¦Ò¡A¥i¦Û¦æú¨©w¨Ï¥Î¡B­×§ï©Î ç°£
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
// #include "securec.h"

char *gBitStr[] = {"", "Thousand ", "Million ", "Billion "};
char *gNumStr[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven","Eight", "Nine"};
char *gOneStr[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
char *gTwoStr[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

char *AddOne(int num)
{
    switch (num)
    {
        case 1: return "One";
        case 2: return "Two";
        case 3: return "Three";
        case 4: return "Four";
        case 5: return "Five";
        case 6: return "Six";
        case 7: return "Seven";
        case 8: return "Eight";
        case 9: return "Nine";
    default:
        return "";
    }
}

char *Addless20(int num)
{
    switch (num)
    {
        case 10: return "Ten";
        case 11: return "Eleven";
        case 12: return "Twelve";
        case 13: return "Thirteen";
        case 14: return "Fourteen";
        case 15: return "Fifteen";
        case 16: return "Sixteen";
        case 17: return "Seventeen";
        case 18: return "Eighteen";
        case 19: return "Nineteen";
    default:
        return "";
    }
}

char *AddTen(int num)
{
    switch (num)
    {
        case 2: return "Twenty";
        case 3: return "Thirty";
        case 4: return "Forty";
        case 5: return "Fifty";
        case 6: return "Sixty";
        case 7: return "Seventy";
        case 8: return "Eighty";
        case 9: return "Ninety";
    default:
        return "";
    }
}

char *g_ten[30];
char *AddTwo(int num)
{
    if (num == 0) {
        return "";
    } else if (num < 10) {
        return AddOne(num);
    } else if (num < 20) {
        return Addless20(num);
    } else {
        int ten = num / 10;
        int ge = num % 10;
        if (ge == 0) {
            return AddTen(ten);
        } else {
            memset(g_ten, 0x0, sizeof(g_ten));
            char *s = AddTen(ten);
            strcat(g_ten, s);
            strcat(g_ten, " ");
            s = AddOne(ge);
            strcat(g_ten, s);
        }
    }
    return g_ten;
}

char *AddThree(int num)
{
    char * str1;
    char *ret = (char *)malloc(50);
    memset(ret, 0x0, 50);
    int hundred = num / 100;
    int left = num - hundred * 100;
    if (hundred > 0 && left > 0) {
        str1 = AddOne(hundred);
        strcat(ret, str1);
        strcat(ret, " Hundred ");
        str1 = AddTwo(left);
        strcat(ret, str1);
    } else if (hundred == 0 && left != 0) {
        str1 = AddTwo(left);
        strcat(ret, str1);
    } else if (hundred != 0 && left == 0) {
        str1 = AddOne(hundred);
        strcat(ret, str1);
        strcat(ret, " Hundred");
    }
    return ret;
}

char * numberToWords(int num)
{
    char *ret = (char *)malloc(200);
    memset(ret, 0x0, 100);
    if (num == 0) {
        strcat(ret, "Zero");
        return ret;
    }
    int bil = num / 1000000000;
    int mil = (num - bil * 1000000000) / 1000000;
    int thro = (num - bil * 1000000000 - mil * 1000000) / 1000;
    int ge = (num - bil * 1000000000 - mil * 1000000 - thro * 1000);
    if (bil > 0) {
        char *str3 = AddThree(bil);
        strcat(ret, str3);
        strcat(ret, " Billion");
        free(str3);
    }
    if (mil > 0) {
        char *str3 = AddThree(mil);
        if (strlen(ret) > 0) {
            strcat(ret, " ");
        }
        strcat(ret, str3);
        strcat(ret, " Million");
        free(str3);
    }
    if (thro > 0) {
        char *str3 = AddThree(thro);
        if (strlen(ret) > 0) {
            strcat(ret, " ");
        }
        strcat(ret, str3);
        strcat(ret, " Thousand");
        free(str3);
    }
    if (ge > 0) {
        char *str3 = AddThree(ge);
        if (strlen(ret) > 0) {
            strcat(ret, " ");
        }
        strcat(ret, str3);
        free(str3);
    }
    return ret;
}


// int main()
// {
//     char *str;
//     str = numberToWords(1123123);
//     printf("%s\n", str);
//     free(str);
//     str = numberToWords(1251123123);
//     printf("%s\n", str);
//     free(str);
//     str = numberToWords(0);
//     printf("%s\n", str);
//     free(str);
//     return 0;
// }