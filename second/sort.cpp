#include<iostream>
#include<math.h>
using namespace std;

int threshold;

void insertionSort(int *R, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = R[i];
        int j = i - 1;
        while (j >= left && R[j] > temp) {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = temp;
    }
}

void heapify(int *R, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 找出左右子节点中的最大值（如果存在）
    if (left < n && R[left] > R[largest])
        largest = left;

    if (right < n && R[right] > R[largest])
        largest = right;

    // 如果最大值不是当前节点，则进行交换并递归调整
    if (largest != i) {
        swap(R[i], R[largest]);
        heapify(R, n, largest);
    }
}

void buildMaxHeap(int *R, int n) {
    // 从最后一个非叶子节点开始，逐个进行堆化
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(R, n, i);
}

void heapSort(int *R, int n) {

    // 构建最大堆
    buildMaxHeap(R, n);
    
    cout<<"Heap:";
    for(int i=0;i<n;i++){
        cout<<R[i]<<" ";
    }
    cout<<endl;

    // 依次将堆顶元素与最后一个元素交换，并调整堆
    for (int i = n - 1; i > 0; i--) {
        swap(R[0], R[i]);
        heapify(R, i, 0);
    }
}

int partition(int *R, int left, int right) {

    int i = left;
    int j= right + 1;
    while(i < j){
        i++;
        while(*(R + i)<= *(R + left)){
            i++;
        }
        j--;

        while(*(R+ j)>*(R + left)){
            j--;
        }

        if(i < j){
            int tmp =*(R + i);
            *(R+i)=*(R+j);
            *(R + j)= tmp;
        }
    }
    int tmp =*(R + left);
    *(R + left)=*(R+j);
    *(R + j)= tmp;
    return j;
}


// 快速排序函数
void quickSort(int *arr, int left, int right, int depth) {

    if(left<right){

        // 留着等插入排序
        if (right-left+1<=threshold)
            return;

        else if (depth <= 0) {
            heapSort(arr + left, right - left + 1);
            return;
        }

        int j=partition(arr, left, right);


        quickSort(arr,left,j-1,depth-1);
        quickSort(arr,j+1,right,depth-1);

    }
    

}


void sort(int *R, int n) {
    int depth_limit = floor(2 * log2(n));
    cout << "depth_limit:" << depth_limit << endl;

    quickSort(R, 0, n - 1, depth_limit);

    cout << "Intermediate:";
    for (int i = 0; i < n; i++) {
        cout << R[i] << " ";
    }

    insertionSort(R, 0, n - 1);

    cout << endl;
}

int main() {
    int n;
    cin >> n >> threshold;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    sort(a, n);
    
    cout << "Final:";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
    delete[] a;
    return 0;
}
