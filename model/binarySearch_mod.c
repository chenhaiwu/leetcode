/* 
 * ¤G¤À¬d§ä[¤G¤À¬d§ä¬YŸÄ­È«e¦Z?šV¡B] 
 * ¤G¤À¬d§ä¡A¥i¥H§ä¦b??¤¤¤¸¯Àªº¤U?¡A¤£¦bªº?¡A¤@©w¦bleft¤¤þ˜ò¡C
 */

int FindLeft(int *nums, int left, int right)
{
   int target = nums[right];
   while (right >= left && nums[right] == target) {
       right--;
   }
   return right == left - 1 ? left : right + 1;
}

int FindRight(int *nums, int left, int right)
{
   int target = nums[left];
   while (left <= right && nums[left] == target) {
       left++;
   }
   return left == right + 1 ? right : left - 1;
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int *ret = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;
    int left = 0;
    int right = numsSize - 1;
    int mid;
    int retLeft = -1;
    int retRight = -1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            retLeft = FindLeft(nums, left, mid);
            retRight = FindRight(nums, mid, right);
            break;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    ret[0] = retLeft;
    ret[1] = retRight;
    return ret;
}
