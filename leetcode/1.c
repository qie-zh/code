/*给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int i,j;


/*int* twoSum(int* nums, int numsSize, int target, int* returnSize){

    for(i = 0; i <= numsSize ; i++){
        for(j = numsSize; j >= i ; j--){
            if (nums[i] + nums[j] == target){
                printf("%d %d\n",i,j);
            }
        }
    }
    return returnSize;
} */

int* twoSum(int* nums, int numsSize, int target, int* returnSize){

    for (int i = 0; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                int* ret = malloc(sizeof(int) * 2);
                ret[0] = i, ret[1] = j;
                *returnSize = 2;
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;

}


void main(){
    int nums[] = {1,2,3,4,5,6};
    int target = 7;
    int c = 1;
    int *returnsize  = &c;
    int numsSize;
    int *r = &c;


    //r = nums;
    //numsSize = sizeof(nums)/sizeof(nums[0]);
    r = twoSum(nums,6,target,returnsize);
    
    //twoSum(nums,numsSize,target,returnsize);
    
    printf("%d\n\n",*returnsize);
    for(i = 0; i <= *returnsize-1; i++){
        printf("%d\n",*r++);
    }
}