#include <stdio.h>
void reverse(int a[], int l, int r){
    int temp;
    while (r > l)
    {
        temp = a[l];
        a[l] = a[r];
        a[r] = temp;
        r--;
        l++;
    }
}

void move(int a[], int m, int n){ // m为右移的次数，n为数组元素的个数
    if (n % m == 0)
    {
        return;
    }
    else
    {
        m = m % n;
    }
    reverse(a, 0, n-m-1); // 将数组的第0位到第n-m-1位进行转置
    reverse(a, n-m, n-1); // 将数组的第n-m位到最后一位进行转置
    reverse(a, 0, n-1);   // 将这个数组进行转置
}

int main(){
    int array[5] = {1,2,3,4,5};
    int m; // 需要右移的次数
    printf("右移前的数组为");
    for(int i = 0; i < 5; i++){
        printf("%d",array[i]);
    }
    printf("\n");
    printf("请输入需要向右移动多少位\n");
    scanf("%d",&m);
    move(array, m, 5);
    printf("右移后的数组为\n");
        for(int i = 0; i < 5; i++){
        printf("%d",array[i]);
    }
    return 0; 
}