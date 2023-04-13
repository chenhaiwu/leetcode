/*
塚??惠璶ㄏノ???衡??狦?ńиㄏノ熌???dp[n+1][n+1]

?塚????惠璶フdp[i][j]┮钡?и??秆?dp[i][j]:
dp[i][j]琌?ㄌΩ熛ij??だ澄橋(瞦?)ゲ﹚?村?┮ノ?程
?怇??瞶秆

(1)秆?dp[1][1]:
dp[1][1]琌Τ熌?1и?1?だ澄橋(瞦?)?眔村?┮ノ?程碞笵dp[1][1]=0?и?瞦1氮琌1ぃノ?

(2)秆?dp[1][2]:
dp[1][2]琌Τ壩熌?12
и?1?だ澄橋(瞦?):

瞦1    
氮琌1?0じ
氮琌2?1じ
ゲ﹚?眔村?程?1じ
и?2?だ澄橋(瞦?):

瞦2
氮琌1?2じ
氮琌2?2じ
ゲ﹚?眔村?程?2じ
?璶?[1,2]?熌?歏и?材Ω瞦1璶?1じゲ﹚?眔村?安ぃ来Ω??珇
┮dp[1][2]=1(璶1じゲ﹚?眔村??材Ω瞦1?)

(3)秆?dp[2][3]:
dp[2][3]琌Τ壩熌?23

Τ熌???ぐぃ琌熛1?﹍㎡(フぃノ)
ゑn=3и?材Ω瞦1琌氮琌2┪幫3はタぃ琌1и?琌ぃ琌璶[2,3]?歏??т氮―
dp[2][3]

и?2?だ澄橋(瞦?):

瞦2    
氮琌2?0じ
氮琌3?2じ
ゲ﹚?眔村?程?2じ
и?3?だ澄橋(瞦?):

瞦3
氮琌2?3じ
氮琌3?0じ
ゲ﹚?眔村?程?3じ
?璶?[2,3]?熌?歏и?材Ω瞦2璶?2じゲ﹚?眔村?
┮dp[2][3]=2(璶2じゲ﹚?眔村??材Ω瞦2?)

(4)秆?dp[1][3]:
dp[1][3]琌Τ熌?123
и?1?だ澄橋(瞦?):

瞦1
氮琌1?0じ
氮琌2┪幫3?熌?塏?熌?歏[2,3]?1+dp[2][3]じ
ゲ﹚?眔村?程?max(0,1+dp[2][3])じ
и?2?だ澄橋(瞦?):

瞦2
氮琌1?2+dp[1][1]=2+0=2じ
氮琌2?0じ
氮琌3?2+dp[3][3]=2+0=2じ
ゲ﹚?眔村?程?max(0,2+dp[1][1],2+dp[3][3])じ
и?程3?だ澄橋(瞦?):

瞦3
氮琌1┪幫2,?3+dp[1][2]じ
氮琌3?0じ
ゲ﹚?眔村?程?max(0,3+dp[1][2])じ
?璶?[1][3]?熌?歏и?璶?min( max(0,1+dp[2][3]) , max(0,2+dp[1][1],2+dp[3][3]) , max(0,3+dp[1][2]) )じゲ﹚?村?
τdp[1][3]碞单ê熌min

塝?璶тdp[1][n]
(安ぃフdp[i][j]?甧ㄒフ┕??)

3.???簿よ祘
???簿よ祘?㎡
材4熌ㄒdp[1][3]и?碞塝?
?–熌だ澄橋и?ウオ壩潱?歏程だ澄橋セō?だ澄橋dp[i][j]
?–熌?歏и?┮Τだ澄橋dp[i][j]程?dp[i][j]痷タ
疭??i?だ澄橋dp[i][j]i潱?歏?j?だ澄橋dp[i][j]jオ潱?歏

?熌и?眔来dp[1][3]ぃ?瞶秆璶琌瞶秆ぃ?и?秆?(フぃノ)

i i+1 i+2 ... ... j-2 j-1 j
i+1?だ澄橋??dp1=max(dp[i][i],dp[i+2][j])+i+1
j-1?だ澄橋??: dp2=max(dp[i][j-2],dp[j][j])+j-1
疭?,i?だ澄橋dp0=i+dp[i+1][j];j?だ澄橋: dp3=j+dp[i][j-1]
dp[i][j]=min(dp0,dp1,dp2,dp3)
4.??恶
?熌dp????ノ?恶ウ¨\〃ボタ朴?

(1)﹍て         (2)dp[i][i]=0   
| \ \ \ \ |         | 0 \ \ \ |
| \ \ \ \ |         | \ 0 \ \ |
| \ \ \ \ |         | \ \ 0 \ |
| \ \ \ \ |         | \ \ \ 0 |
钡?璶σ?恶痻?眔dp[1][n]:
甧и?塝?ノ熌竚オ潱㎝潱?誹??衡ウセō?恶

(3)恶1
| 0 1 \ \ |  dp[1][2]?衡˙?
| \ 0 \ \ |
| \ \ 0 \ |
| \ \ \ 0 |
(4)恶1
| 0 1 x \ |  dp[1][3]?衡˙?
| \ 0 2 \ |  dp[2][3]?衡˙?(恶)
| \ \ 0 \ |
| \ \ \ 0 |
(5)恶程:
| 0 1 x x |  dp[1][4]?衡˙?
| \ 0 2 x |  dp[2][4]?衡˙?(礛恶)
| \ \ 0 x |  dp[3][4]?衡˙?(恶)
| \ \ \ 0 |
x恗琌?и?眔衡... ... 敖熌?Τ塕届衡
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)
#define MIN(a, b) (a) < (b) ? (a) : (b)
int getMoneyAmount_dp(int n)
{
    if(n==1)
        return 0;
    //﹚痻?
    int dp[n+1][n+1];
    //﹍て¨\〃
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=INT_MAX;
        }
    }
    //﹚膀?dp[i][i]
    for(int i=0;i<=n;i++){
        dp[i][i]=0;
    }

    //?熛材2?﹍
    for(int j=2;j<=n;j++){
        //︽?熛┕
        for(int i=j-1;i>=1;i--){
            //衡埃壩狠–熌だ澄橋
            for(int k=i+1;k<=j-1;k++){
                dp[i][j]=MIN(k+MAX(dp[i][k-1],dp[k+1][j]),dp[i][j]);
            }
            //衡壩狠
            dp[i][j]=MIN(dp[i][j],i+dp[i+1][j]);
            dp[i][j]=MIN(dp[i][j],j+dp[i][j-1]);
        }
    }
    return dp[1][n];
}

// 漼?衡猭
#define MAXN 1000
int g_memo[MAXN][MAXN];

int Steps(int start, int end)
{
    if (g_memo[start][end] != 0) {
        return g_memo[start][end];
    }
    if (end == 1 || end == 0) {
        return 0;
    }
    if (end - start == 1) {
        return start;
    }
    if (start >= end) {
        return 0;
    }
    int ans = INT_MAX;
    for (int i = start; i < end; i++) {
        int t1 = Steps(start, i - 1);
        int t2 = Steps(i + 1, end);
        int t = MAX(t1, t2) + i;
        ans = MIN(ans, t);
    }
    g_memo[start][end] = ans;
    return ans;
}

int getMoneyAmount(int n)
{
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            g_memo[i][j] = 0;
        }
    }
    return Steps(1, n);
}