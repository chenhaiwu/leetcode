/* 
 * 双指针[三数之和、四数之和、] 
 * 双指针，可以一头一尾，也可以一前一后。
 */
int comp(const void *a,const void *b)
{
    return *(int *)a - *(int *)b;
}

// 四数之和
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (numsSize == 0) {
        return 0;
    }
    int **ret = (int **)malloc(sizeof(int *) * (numsSize + 1) * 6);
    *returnSize = 0;
    short left = 0;
    short right = numsSize - 1;
    int target = 0;

    *returnColumnSizes = malloc(sizeof(int) * (numsSize + 1) * 6);
    qsort(nums, numsSize, sizeof(int), comp);
    ret[*returnSize] = malloc(sizeof(int) * 3);

    while (left + 1 < right) {
        int i = left + 1;
        int j = right;
        target = 0 - nums[left];
        while (i < j) {
            if (nums[i] + nums[j] < target) {
                i++;
            } else if (nums[i] + nums[j] > target) {
                j--;
            } else {
                ret[*returnSize][0] = nums[left];
                ret[*returnSize][1] = nums[i];
                ret[*returnSize][2] = nums[j];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;
                ret[*returnSize] = malloc(sizeof(int) * 3);

                while(nums[i] == nums[++i] && i < j) {}
                while(nums[j] == nums[--j] && i < j) {}
            }
        }
        while(nums[left] == nums[++left] && left + 1 < right) {}
    }
    
    return ret;
}

// 4数之和
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (numsSize < MAX_FOUR) {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), Cmp);

    int **ret = (int **)malloc(sizeof(int *) * numsSize * 6);
    *returnColumnSizes = malloc(sizeof(int) * numsSize * 6);
    int retSize = 0;

    int first = 0;
    int right = numsSize - 1;

    while (first + 2 < right) {
        int second = first + 1;
        int t3 = target - nums[first];
        while (second + 1 < right) {
            int i = second + 1;
            int j = right;
            int t2 = t3 - nums[second];
            while (i < j) {
                if (nums[i] + nums[j] < t2) {
                    i++;
                } else if (nums[i] + nums[j] > t2) {
                    j--;
                } else {
                    ret[retSize] = malloc(sizeof(int) * MAX_FOUR);
                    ret[retSize][0] = nums[first];
                    ret[retSize][1] = nums[second];
                    ret[retSize][2] = nums[i];
                    ret[retSize][3] = nums[j];
                    (*returnColumnSizes)[retSize] = MAX_FOUR;
                    retSize++;

                    while(nums[i] == nums[++i] && i < j) {}
                    while(nums[j] == nums[--j] && i < j) {}
                }
            }
            while(nums[second] == nums[++second] && second + 1 < right) {}
        }
        while(nums[first] == nums[++first] && first + 2 < right) {}
    }

    *returnSize = retSize;
    return ret;
}