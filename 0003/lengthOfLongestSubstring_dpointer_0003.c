#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)

int BitSet(int mask, int bit)
{
    return mask | (1 << bit);
}

int BitClr(int mask, int bit)
{
    return mask & (~(1 << bit));
}

bool BitTest(int mask, int bit)
{
    if ((mask & (1 << bit)) >> bit == 1) {
        return true;
    } else {
        return false;
    }
}

/* 双指针的解法，只适合只有26个字母的做法，但是这题有可能不是字母，导致执行出错 */
int lengthOfLongestSubstring1(char * s)
{
    int ans = 1;
    int len = strlen(s);
    if (len <= 1) {
        return len;
    }
    int left = 0;
    int right = 1;
    int v = s[0] - 'a';
    v = BitSet(0, v);
    while (right < len) {
        int rightid = s[right] - 'a';
        if (BitTest(v, rightid)) {
            while (left < right && BitTest(v, rightid)) {
                v = BitClr(v, s[left] - 'a');
                left++;
            }
        } else {
            ans = MAX(ans, right - left + 1);
        }
        v = BitSet(v, rightid);
        right++;
    }
    return ans;
}

int lengthOfLongestSubstring(char * s){
    int maxLen = 0;
    int curLen = 0;
    int position[256];
    int preIndex;
    for (int i = 0; i < 256; i++)
        position[i] = -1;
    int strLen = strlen(s);
    for (int i = 0; i < strLen; i++){
        preIndex = position[s[i]];
        if (preIndex == -1 || i - preIndex > curLen) {
            curLen++;
            maxLen = MAX(maxLen, curLen);
        } else {
            curLen = i - preIndex;
            maxLen = MAX(maxLen, curLen);
        }
        position[s[i]] = i;
    }
    printf("%d", maxLen);
    return maxLen;
}

void main()
{
    int ans;
    ans = lengthOfLongestSubstring("abcabcbb");
    printf("ans=%d\n", ans);
    ans = lengthOfLongestSubstring("bbbb");
    printf("ans=%d\n", ans);
    ans = lengthOfLongestSubstring("pwwkew");
    printf("ans=%d\n", ans);
}