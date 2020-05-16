/*
解题思路
假设交点（x,y）
代入方程 a1x+b1y+c1 = 0 a2x+b2y+c2 = 0 最后计算出
x = (c2b1 - c1b2)/(a1b2 - (double)a2b1); //要把类型转成double 不然小数点没了
y = (a1c2 - a2c1)/(a2b1 - (double)a1b2);
分母不能为0 单独处理下 分母为0 的情况 也就是斜率相等 c如果相等就是一条直线的2个线段了
判断开始位置有没有在另一个线段里面包含，checkin这个我之前只判断了一种情况 真的是笨死了
有就是被包含的那个开始点 没有就没有

分母不为0 就可以计算交点 计算完判断下有没有在同时包含在2个线段里面
我有病，我一个嵌入式的为什么被忽悠来看这个，好打击自信心。
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 static int checkin(int a,int b,int c);
double* intersection(int* start1, int start1Size, int* end1, int end1Size, int* start2, int start2Size, int* end2, int end2Size, int* returnSize)
{
   int x1 = start1[0], y1 = start1[1], x2 = end1[0], y2 = end1[1];
   int x3 = start2[0], y3 = start2[1], x4 = end2[0], y4 = end2[1];
   //ax + by + c = 0
   int a1 = y2 -y1, b1 = x1 - x2;
   int c1 = 0 - (a1*x1 + b1*y1);

   int a2 = y4 -y3, b2 = x3 - x4;
   int c2 = 0 - (a2*x3 + b2*y3);
   double *ret = malloc(sizeof(double)*2);
   if(NULL == ret)
   {
      *returnSize = 0;
      return NULL; 
   }
   if(a2*b1 == a1*b2)//斜率相等
   {
       if(c1 == c2 )//
       {
          if(checkin(x3,x1,x2)&&checkin(y3,y1,y2))
          {
             *returnSize = 2; 
             ret[0] = x3;
             ret[1] = y3;
             return ret;
          }
          if(checkin(x1,x3,x4)&&checkin(y1,y3,y4))
          {
            *returnSize = 2; 
             ret[0] = x1;
             ret[1] = y1;
             return ret;
          }
         *returnSize  = 0;
          return ret;
       }
       else
       {
          *returnSize  = 0;
          return ret;
       }
   }
   //斜率不等
    double y = (a1*c2 - a2*c1)/(a2*b1 - (double)a1*b2);
    double x = (c2*b1 - c1*b2)/(a1*b2 - (double)a2*b1);
    if(checkin(x,x1,x2) && checkin(x,x3,x4) && checkin(y,y1,y2) && checkin(y,y3,y4))
    {
        *returnSize  = 2;
         ret[0] = x;
         ret[1] = y;
         return ret;
    }
   *returnSize  = 0;
    return ret;
}

static int checkin(int a,int b,int c)
{
   if(a>=b && a<=c)
      return 1;
    if(a>=c && a<=b)
      return 1;
    return 0;
}

/*
使用高中数学必修课中的解法，线段一根据两点(x1, y1),(x2, y2)求出对应直线方程的一般式为：
(y - y1)(x2 - x1) = (y2 - y1)(x - x1)，同样，线段二对应直线的方程为：
(y - y3)(x4 - x3) = (y4 - y3)(x - x3)，然后连立方程组。然后分类讨论：

如果两直线不平行，直接联立方程组，解出直线的交点，然后判断交点是否同时在两线段上即可。
如果两直线平行，分别找出两直线中x更小的点，x相同就找y更小的，比如分别为A(xa, ya),B(xb, yb)，在纸上画一下两线段部分重合以及平行但不重合的图很容易知道，只要A点在线段2上，那么A点就是我们要找的点，否在再判断如果B点在线段1上，则B就是我们要找的点，如果都不满足，则两线段虽然在同一直线上，但他们没交点。

*/
double* intersection(int* start1, int start1Size, int* end1, int end1Size, int*      start2, int start2Size, int* end2, int end2Size, int* returnSize)
{
    int x1 = start1[0], y1 = start1[1], x2 = end1[0], y2 = end1[1];
    int x3 = start2[0], y3 = start2[1], x4 = end2[0], y4 = end2[1];
    double x, y;
    double *result = malloc(2 * sizeof(double));
    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }
    // 线段一方程的一般式: (y - y1)(x2 - x1) = (y2 - y1)(x - x1)
    // 线段二方程的一般式: (y - y3)(x4 - x3) = (y4 - y3)(x - x3)
    if ((y2 - y1) * (x4 - x3) != (x2 - x1) * (y4 - y3)) {
        // 线段不平行的情况
        /*
          解得 x = [(y3 - y1)(x2 - x1)(x4 - x3) + x1(y2 - y1)(x4 - x3) 
          - x3(y4 - y3)(x2 - x1)] / [(y2 - y1)(x4 - x3) - (y4 - y3)(x2 - x1)]
          解得 y = [(x3 - x1)(y2 - y1)(y4 - y3) + y1(x2 - x1)(y4 - y3) 
          - y3(x4 - x3)(y2 - y1)] / [(x2 - x1)(y4 - y3) - (x4 - x3)(y2 - y1)]
        */
        
        x = (double)((y3 - y1) * (x2 - x1) * (x4 - x3) + x1 * (y2 - y1) * (x4 - x3)
            - x3 * (y4 - y3) * (x2 - x1))
            / ((y2 - y1) * (x4 - x3) - (y4 - y3) * (x2 - x1));
        y = (double)((x3 - x1) * (y2 - y1) * (y4 - y3) + y1 * (x2 - x1) * (y4 - y3)
            - y3 * (x4 - x3) * (y2 - y1))
            / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));

        // 判断直线交点是否同时在两线段上
        if ((((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) 
                && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1)))
                && (((x >= x3 && x <= x4) || (x >= x4 && x <= x3))
                && ((y >= y3 && y <= y4) || (y >= y4 && y <= y3)))) {
            
            result[0] = (x <= 0 && x > -1e-6) ? x + 1e-6 : x;
            result[1] = (y <= 0 && y > -1e-6) ? y + 1e-6 : y;
            *returnSize = 2;
        } else {
            *returnSize = 0;
        }
        
    } else {
        // 线段平行情况
        /* 
          先判断是否为同一条直线，只需判断一条直线上的点是否在另一条直线上
          把 (x3, y3) 带入线段一的方程一般式中
        */
        if ((y3 - y1) * (x2 - x1) == (y2 - y1) * (x3 - x1)) {
            // 如果是同一条直线，考虑线段相交部分，
            /* 
              只需分别找更小的那个点，看在不在另一条线段上，如果在就说明这个点就是答案，
            */
            int xa, ya, xb, yb;
            if (x1 < x2 || (x1 == x2 && y1 < y2)) {
                xa = x1;
                ya = y1;
            } else {
                xa = x2;
                ya = y2;
            }

            if (x3 < x4 || (x3 == x4 && y3 < y4)) {
                xb = x3;
                yb = y3;
            } else {
                xb = x4;
                yb = y4;
            }
            
            if(((xa >= x3 && xa <= x4) || (xa >= x4 && xa <= x3))
                    && ((ya >= y3 && ya <= y4) || (ya >= y4 && ya <= y3))) {
                x = xa;
                y = ya;
                result[0] = (x <= 0 && x > -1e-6) ? x + 1e-6 : x;
                result[1] = (y <= 0 && y > -1e-6) ? y + 1e-6 : y;
                *returnSize = 2;
            } else if (((xb >= x1 && xb <= x2) || (xb >= x2 && xb <= x1))
                    && ((yb >= y1 && yb <= y2) || (yb >= y2 && yb <= y1))) {
                x = xb;
                y = yb;
                result[0] = (x <= 0 && x > -1e-6) ? x + 1e-6 : x;
                result[1] = (y <= 0 && y > -1e-6) ? y + 1e-6 : y;
                *returnSize = 2;
            } else {
                // 两直线重合，但是线段无交点
                *returnSize = 0;
            }
            
        } else {
            // 如果不是同一条直线，说明没交点
            *returnSize = 0;
        }
    }
    return result;
}