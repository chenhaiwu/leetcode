/*
�V??�E�ݭn�ϥ�?�s?�s?��?��?�G�A�b?���ڨϥΤ@�ĤG???dp[n+1][n+1]

?�_�V??�E??�A�ݭn����dp[i][j]���t��A�ҥH���U?��??��?dp[i][j]���t��:
dp[i][j]�O?�̦��H��i��j��?�r�@?���Θ�(�q��?)�A���w?����?�ҥ�?���̤p�ȡC
?���ݏ�?���G��?�z�ѡC

(1)��?dp[1][1]:
dp[1][1]�O���u���@��?�r1�A��?�H1�@?���Θ�(�q��?)�A?�o��?�ҥ�?���̤p�ȡA�@�ݴN���D�Adp[1][1]=0�C�]?��?�u��q1�A���פ]�u��O1�A���Ϊ�?

(2)��?dp[1][2]:
dp[1][2]�O���u���Ο�?�r1�A2
��?���H1�@?���Θ�(�q��?):

�q1�G    
���׬O1�A��?0��
���׬O2�A��?1��
���w?�o��?�A�̦h��?1��
��?�A�H2�@?���Θ�(�q��?):

�q2�G
���׬O1�A��?2��
���׬O2�A��?2��
���w?�o��?�A�̦h��?2��
?�W�A�u�n?�J[1,2]?��?�V�A��?�Ĥ@���q1�A�u�n��?1���A���w�i�H?�o��?�]���p�ݤ����A�A�ݤ@���A??���~�^
�ҥHdp[1][2]=1(�u�n��1�����w?�o��?�A?�Ĥ@���q1?)

(3)��?dp[2][3]:
dp[2][3]�O���u���Ο�?�r2�A3

���@�Ĥp??�A?���\���O��1?�l�O�H(���ժ����ά�)
��pn=3�A��?�Ĥ@���q�F1�A���O���׬O2�Ύ�3�A�ϥ����O1�A��?�O���O�n��[2,3]?�V??�䵪�סA�Y�D
dp[2][3]

��?���H2�@?���Θ�(�q��?):

�q2�G    
���׬O2�A��?0��
���׬O3�A��?2��
���w?�o��?�A�̦h��?2��
��?�A�H3�@?���Θ�(�q��?):

�q3�G
���׬O2�A��?3��
���׬O3�A��?0��
���w?�o��?�A�̦h��?3��
?�W�A�u�n?�J[2,3]?��?�V�A��?�Ĥ@���q2�A�u�n��?2���A���w�i�H?�o��?
�ҥHdp[2][3]=2(�u�n��2�����w?�o��?�A?�Ĥ@���q2?)

(4)��?dp[1][3]:
dp[1][3]�O���u���T��?�r1�A2�A3
��?���H1�@?���Θ�(�q��?):

�q1�G
���׬O1�A��?0��
���׬O2�Ύ�3�A?��?�ԉN?�J�t�@��?�V[2,3]�A��?1+dp[2][3]��
���w?�o��?�A�̦h��?max(0,1+dp[2][3])��
��?�A�H2�@?���Θ�(�q��?):

�q2�G
���׬O1�A��?2+dp[1][1]=2+0=2��
���׬O2�A��?0��
���׬O3�A��?2+dp[3][3]=2+0=2��
���w?�o��?�A�̦h��?max(0,2+dp[1][1],2+dp[3][3])��
��?�̦Z�H3�@?���Θ�(�q��?):

�q3�G
���׬O1�Ύ�2,��?3+dp[1][2]��
���׬O3�A��?0��
���w?�o��?�A�̦h��?max(0,3+dp[1][2])��
?�W�A�u�n?�J[1][3]?��?�V�A��?�u�n��?min( max(0,1+dp[2][3]) , max(0,2+dp[1][1],2+dp[3][3]) , max(0,3+dp[1][2]) )�����w�i�H?����?
��dp[1][3]�]�N���_����min���ȡC

�i�H�Y?�A�u�n���dp[1][n]�Y�i�C
(���p�������dp[i][j]�i�H��^�W��?�e�ݨҤl�A���զZ�A���U??)

3.???����{
???����{��\?�O�H
�ݲ�4�ĨҤl�Adp[1][3]��?�N�i�H�Y?�G
?�_�C�@�Ĥ��Θ�A��?�������k�Ν�?�V���̤j�ȥ[�W���Θ򥻨��@?�������Θ�dp[i][j]��
?�_�C�@��?�V�A��?���Ҧ����Θ�dp[i][j]���̤p�ȧ@?dp[i][j]���u������
�S?�a�A?�_�Hi�@?���Θ�dp[i][j]�A�u��i�k����?�V�F?�_�Hj�@?���Θ�dp[i][j]�A�u��j������?�V

?�ħ�?�o����dp[1][3]��?�z�ѡA�n�O�z�Ѥ��F��?�A��?����?�@�U(���ժ����ά�)�G

i i+1 i+2 ... ... j-2 j-1 j
�Hi+1?���Θ�??���Gdp1=max(dp[i][i],dp[i+2][j])+i+1
�Hj-1?���Θ�??��: dp2=max(dp[i][j-2],dp[j][j])+j-1
�S?�a,�Hi?���Θ�Gdp0=i+dp[i+1][j];�Hj?���Θ�: dp3=j+dp[i][j-1]
dp[i][j]=min(dp0,dp1,dp2,dp3)
4.??��R
?�X�@��dp�G????�ΥN?��R���A��\����ܥ���?

(1)��l�ơG         (2)����dp[i][i]=0   
| \ \ \ \ |         | 0 \ \ \ |
| \ \ \ \ |         | \ 0 \ \ |
| \ \ \ \ |         | \ \ 0 \ |
| \ \ \ \ |         | \ \ \ 0 |
���U?�n��?��\��R�x?�H�o��dp[1][n]:
�ܮe����?�Y?�i�H�Τ@�Ħ�m�����M�U���a?�u??�⥦�����A�]���i�H?����R

(3)��R1�C�G
| 0 1 \ \ |  dp[1][2]?��B?�V�W��
| \ 0 \ \ |
| \ \ 0 \ |
| \ \ \ 0 |
(4)�A��R1�C�G
| 0 1 x \ |  dp[1][3]?��B?�V�W��
| \ 0 2 \ |  dp[2][3]?��B?�V�W��(����R)
| \ \ 0 \ |
| \ \ \ 0 |
(5)�A��R�̦Z�@�C:
| 0 1 x x |  dp[1][4]?��B?�V�W��
| \ 0 2 x |  dp[2][4]?��B?�V�W��(�M�Z��R)
| \ \ 0 x |  dp[3][4]?��B?�V�W��(����R)
| \ \ \ 0 |
x�m�O�]?��?�o��F... ... ����?�A���R��i�H�ۤv��
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
    //�w��x?
    int dp[n+1][n+1];
    //��l�ơ�\��
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=INT_MAX;
        }
    }
    //�w���?��dp[i][i]
    for(int i=0;i<=n;i++){
        dp[i][i]=0;
    }

    //���C?�A�ϲ�2�C?�l
    for(int j=2;j<=n;j++){
        //����?�A�ϤU���W
        for(int i=j-1;i>=1;i--){
            //�Ⱓ�F�κݪ��C�@�Ĥ��Θ�
            for(int k=i+1;k<=j-1;k++){
                dp[i][j]=MIN(k+MAX(dp[i][k-1],dp[k+1][j]),dp[i][j]);
            }
            //��κ�
            dp[i][j]=MIN(dp[i][j],i+dp[i+1][j]);
            dp[i][j]=MIN(dp[i][j],j+dp[i][j-1]);
        }
    }
    return dp[1][n];
}

// �y?��k
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