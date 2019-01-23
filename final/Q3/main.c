#include "stdlib.h"
#include "stdio.h"

int max(int a, int b);

int main(){
    int A[12] = {0,1,0,2,1,0,1,3,2,1,2,1};
    
    int left = 0;
    int right = 11;
    int leftmax = A[0];
    int rightmax = A[11];
    int res = 0;
    
    while(left<right){
        if(A[left]<A[right]){
            leftmax = max(leftmax,A[left]);
            res += leftmax - A[left];
            left++;
        }else{
            rightmax = max(A[right],rightmax);
            res += rightmax - A[right];
            right--;
        }
    }
    printf("%d\n",res);
    return res;
    
}

int max(int a, int b){
    if(a>=b) return a;
    if(a<b) return b;
    return 0;
}
