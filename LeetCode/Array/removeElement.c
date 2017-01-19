#include <stdio.h>

/**
 *  在原数组上, 利用新的索引来进行拷贝
 */
int removeElement(int arr[], int length, int element) {
	
	if(length == 0) {
	    return 0;
	}
	
	int i = 0, j = 0;
	
	for (;i<length;i++) {
		if (arr[i] != element) {
			arr[j] = arr[i];
			j++;
		}
	}
	
	return j;
}

/**
 * 在原数组进行拷贝
 */
int removeDuplicates(int nums[], int length) {
	if(length == 0) {
	    return 0;
	}
		
	int i = 1, j = 1;
	
	int elem = nums[0];
	for (;i<length;i++) {
		if (nums[i] != elem) {
			nums[j] = nums[i];
			j++;
			elem = nums[i];
		}
	}
	
	return j;
}

int removeMaxDuplicates(int nums[], int length, int timesAlow) {
	if(length == 0) {
	    return 0;
	}
		
	int i = 1, j = 1, curT = 0;
	
	int elem = nums[0];
	for (;i<length;i++) {
		if (nums[i] != elem || (nums[i] == elem && curT < timesAlow) ) {   //执行复制, 增加新数组元素
			nums[j] = nums[i];
			elem = nums[i];
			j++;
			if(nums[i] != elem) {
				curT = 1;
			}
			else {
				curT++;
			}
		}
	}
	
	return j;
}

void printArr(int nums[], int length) {
	for(int i = 0; i < length; i++) {
		printf("%d\t", nums[i]);
	} 
	printf("\n");
}

int main() {
//  int nums[] = {1, 2, 3, 4, 3, 2, 5, 2};
//	int newLen = removeElement(nums, 8, 2);
//	printf("after remove 2, new Len: %d", newLen); 
	
//	int nums[] = {1, 2, 2, 3, 3, 3, 4, 5, 5, 6};
//	int newLen = removeDuplicates(nums, 9);
//	printf("after remove duplecates, new Len: %d\n", newLen);
//	printArr(nums, newLen);

	int nums[] = {1, 2, 2, 3, 3, 3, 4, 5, 5, 6};
	int newLen = removeMaxDuplicates(nums, 10, 1);
	printf("after remove duplecates, new Len: %d\n", newLen);
	printArr(nums, newLen);
}
