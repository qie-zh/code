#include <stdio.h>
#include <string.h>

void swap(int *a,int *b) // 交换两个变量
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int *bubble_sort(int nums[],int length){  //冒泡排序
    for(int i = 0; i < length-1; i++){
        for(int j = 0; j < length-1; j++){
            if(nums[j] > nums[j+1]){
                swap(&nums[j],&nums[j+1]);
            }
        }
    }
    return nums;

}


int *selection_sort(int nums[],int length){    //选择排序
    int max = 0;
    for( int i = 0; i< length; i++){
        
        for(int j = 0; j< length-i; j++){
            if(nums[j] > nums[max]){
                max = j;
            }
        }

        swap(&nums[length-1-i],&nums[max]);
        max = 0;
    }
    return nums;

}

int *insertion_sort(int nums[],int length){     //插入排序
    int s;

    for(int i = 0; i < length-1; i++){
        s = i+1;
        for(int j = i; j >= 0; j--){
            
            if(nums[j] > nums[s]){
                
                swap(&nums[j],&nums[s]);
                s = j;
            }
            else break;
        }   
    }
    return nums;
}


void merge_sort_recursiver(int arr[], int reg[],int start, int end){    //归并排序
    if(start >= end){
        return;
    }
    int len = end - start;
    int mid = len / 2 + start;
    int end1 = mid,end2 = end;
    int start1 = start;
    int start2 = mid + 1;

    merge_sort_recursiver(arr,reg,start1,end1);
    merge_sort_recursiver(arr,reg,start2,end2);

    int k = start;

    while(start1 <= end1 && start2 <= end2){
        if(arr[start1] <= arr[start2]){
            reg[k++] = arr[start1++];
        }
        else{
            reg[k++] = arr[start2++];
        }
    }

    while(start2 <= end2){
        reg[k++] = arr[start2++];
    }

    while(start1 <= end1){
        reg[k++] = arr[start1++];
    }
    for (k = start; k <= end; k++)
        arr[k] = reg[k];

    

}

int *merge_sort(int nums[],int len){
    int reg[len];
    merge_sort_recursiver(nums,reg,0,len-1);

    return nums;

}

void quick_sort_recursiver(int nums[],int start, int end){
    int left = start,right = end - 1;
    int piv = nums[end];


    if (start >= end){
        return;
    }
    
    while( left < right){
        while (nums[left] <= piv && left < right)  //找到比piv大
        {
            left++;
        }
        while(nums[right] >= piv && left < right){  //找到比piv小
            right--;
        }
        swap(&nums[left],&nums[right]);
    }

    if(nums[left] >= nums[end]){
        swap(&nums[left],&nums[end]);
    }
    else{
        left++;
    }

    if (left){
        quick_sort_recursiver(nums,start,left-1);
    }
    quick_sort_recursiver(nums,left+1,end);

}

int *quick_sort(int nums[],int len){
    quick_sort_recursiver(nums,0,len-1);

    return nums;

}

int main(){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int a = 1;
    int *ret = &a;

    //ret = bubble_sort(arr,14);
    //ret = selection_sort(arr,14);
    //ret = insertion_sort(arr,14);
    //ret = merge_sort(arr,14);
    ret = quick_sort(arr,14);

    for( int i = 0; i < 14; i++){
        printf("%d.%d  ",i,*(ret+i));
    }

    return 0;

}