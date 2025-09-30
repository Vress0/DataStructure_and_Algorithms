// Part 1: 使用者可輸入學生人數n及姓名長度m
// 使用new和malloc兩種方式建立二維動態陣列
// 兩種動態宣告方式都要實作(沒用動態陣列，最多僅能得15分)
// 讓使用者輸入n個學生的姓名(長度不可以超過m個字元)
// 將學生姓名存入動態二維字元陣列


// Part 2: 接續使用指標處理(沒用指標處理，最多僅能得15分)
// 排序：根據學生姓名的最後一個字元ASCII code，利用bubble sort
// 由小到大排序
// 印出排序後的學生名單
// 釋放動態記憶體

#include <iostream>
#include <cstring>
using namespace std;


int n, m;
char** names_malloc;

void bubbleSort(){

    // 排序規則：根據姓名最後一個字元的 ASCII code 由小到大
    
    // i代表右邊已排序的元素個數
    for (int i = 0; i < n - 1;i++)    // n個數只需比較n-1次
    {
        // 比較起始位置的index
        for (int j = 0; j < n - i - 1;j++)   // 為什麼是n-i-1? ==> n個數只需比較n-1次，且每次需扣掉已排序元素個數
        {
            
            // 取得兩個相鄰字串的最後一個字元
            int lens1 = strlen(names_malloc[j]);
            int lens2 = strlen(names_malloc[j + 1]);

            char lastletter1 = names_malloc[j][lens1 - 1];
            char lastletter2 = names_malloc[j + 1][lens2 - 1];

            if(lastletter1>lastletter2){
                char* temp = names_malloc[j];        // 暫存指標
                names_malloc[j] = names_malloc[j+1];    // 第一個指標指向第二個字串
                names_malloc[j+1] = temp;            // 第二個指標指向第一個字串
            }
        }
    }
}





int main(){
    


    //n 輸入學生人數
    cout << "the number of students" << endl;
    cin >> n;
    
    // m 輸入姓名最大長度
    cout << "the max lens of name" << endl;
    cin >> m;
    

    // malloc 建立
    // 先準備 n 個姓名牌架子 (char**)
    // char* ->可以當成是一個姓名牌

    //----------new 建立 Sop-----------------
    // 1.先準備 n 個姓名牌架子 (char**)
    // 2.為每個架子準備實際的姓名牌，並貼上標籤
    //------------------------------------

    // 姓名牌架子 = 準備 n 個架子
    // 使用malloc建立二維動態陣列
    names_malloc = (char**)malloc(n * sizeof(char*));

    // 為每個架子準備實際的姓名牌
    for (int i = 0; i < n;i++){
        // 第i個學生的姓名牌位置 =(貼上) 去商店買一張姓名貼紙，這張貼紙有 m+1 個格子可以寫字母
        // malloc 回傳的是 void*，在 C++ 中不能直接指定給 char*，所以要用 (char*) 做轉型
        names_malloc[i] = (char*)malloc((m + 1) * sizeof(char));
    }

    // 讓使用者在每個姓名牌上寫名字，並檢測是否在規定的字數內

    for (int i =0; i < n;i++){

        bool inputOK = false;
    
        while(!inputOK){

            cout << "enter the "<< i+1 << " names" << endl;
            cin >> names_malloc[i];

            if (strlen(names_malloc[i]) <= m){
                inputOK = true;
                
            }
            else{
                cout << "too long" << endl;
            }
        } 
    }

    
    // 顯示所有學生姓名
    cout << "\n=== Student list ===" << endl;
    for (int i = 0; i < n; i++){
        cout << "student " << i+1 << ": " << names_malloc[i] << endl;
    }

    //
    bubbleSort();
    cout << "\n=== New Student list ===" << endl;
    for (int i = 0; i < n; i++){
        cout << "student " << i+1 << ": " << names_malloc[i] << endl;
        
        // 1.count the word's lens
        // 2.減去1即可得到最後一個字的index
        // 3.get the value of last index
        // 4. "(int)" can let the number become ASCII Code
        cout << names_malloc[i][strlen(names_malloc[i]) - 1] << ", ASCII: " << (int)names_malloc[i][strlen(names_malloc[i]) - 1] << endl;
    }


    
    // 釋放記憶體 : 先收名牌，再收名牌架    

    for (int i = 0; i < n;i++){
        free(names_malloc[i]);
    }

    free(names_malloc);

    return 0;
}