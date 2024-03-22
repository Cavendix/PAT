#include<iostream>
#include<math.h>
using namespace std;

int threshold; // 全局变量，用于存储阈值

// 插入排序函数
void insertionSort(int *R, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = R[i];
        int j = i - 1;
        // 将当前元素依次与前面已排序的元素比较并插入正确位置
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


// 三路分划
void partition(int *R, int left, int right, int &i, int &j) {
    int m = left + (right - left) / 2;

    // 三数取中法选基准元素
    swap(R[left + 1], R[m]);
    if (R[left + 1] > R[right]) swap(R[left + 1], R[right]);
    if (R[left] > R[right]) swap(R[left], R[right]);
    if (R[left + 1] > R[left]) swap(R[left + 1], R[left]);

    int pivot = R[left];

    i = left, j = right;
    int k = left;

    while (k <= j) {
        if (R[k] < pivot) {
            swap(R[k++], R[i++]);
        } else if (R[k] > pivot) {
            swap(R[k], R[j--]);
        } else {
            k++;
        }
    }
}


// 尾递归转循环
void quickSort(int *arr, int left, int right, int depth) {
    // 当深度为零时，转为堆排序
    if (depth <= 0&&right - left + 1 > threshold) {
        heapSort(arr + left, right - left + 1);
        return;
    }

    while (right - left + 1 > threshold) {
        int i, j;
        partition(arr, left, right, i, j);
        if (i - left < right - j) {
            quickSort(arr, left, i, depth - 1);
            left = j + 1;
        } else {
            quickSort(arr, j + 1, right, depth - 1);
            right = i;
        }
    }
}


// 主排序函数
void sort(int *R, int n) {
    int depth_limit = floor(2 * log2(n)); // 计算递归深度限制
    cout << "depth_limit:" << depth_limit << endl;

    quickSort(R, 0, n - 1 ,depth_limit); // 调用快速排序

    cout << "Intermediate:";
    for (int i = 0; i < n; i++) {
        cout << R[i] << " ";
    }

    insertionSort(R, 0, n - 1); // 调用插入排序

    cout << endl;
}

// 主函数
int main() {
    int n;
    cin >> n >> threshold; // 输入数组大小和阈值
    int *a = new int[n]; // 动态分配数组空间
    for (int i = 0; i < n; i++)
        cin >> a[i]; // 输入数组元素
    
    sort(a, n); // 调用排序函数
    
    cout << "Final:";
    for (int i = 0; i < n; i++)
        cout << a[i] << " "; // 输出最终排序结果
    cout << endl;
    delete[] a; // 释放内存
    return 0;
}
