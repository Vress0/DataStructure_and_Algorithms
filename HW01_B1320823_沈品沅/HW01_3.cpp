
//==========SOP===========
// 1.輸入人數
// 2.建立暫存陣列
// 3.輸入姓名
// 4.計算最長姓名長度 y
// 5.找出第一個空格的「最大位置」maxSpacePos
// 6.建立最終二維陣列 studentNames
// 7.對齊並拷貝字串
// 8.輸出結果
// 9.釋放記憶體


#include <iostream>
#include <cstring>  
using namespace std;

int main() {
    int x;
    cout << "please enter the number of students: ";
    cin >> x;
    cin.ignore(); // 清除輸入緩衝區中的換行符號，避免影響後續getline()的讀取
    
    // ===================步驟1: 建立暫時的字元陣列儲存姓名===================
    char** tempNames = new char*[x];  // 建立指標陣列，每個指標指向一個學生姓名
    for (int i = 0; i < x; i++) {
        tempNames[i] = new char[100]; // 為每個學生分配100字元的空間（假設姓名不超過100字元）
    }
    
    // ===================步驟2: 輸入所有學生姓名===================
    for (int i = 0; i < x; i++) {
        cout << "please enter " << (i + 1) << " student name: ";
        cin.getline(tempNames[i], 100);  // 使用getline讀取完整姓名（包含空格）
    }
    
    // ===================步驟3: 找出最長的姓名長度===================
    int y = 0;  // 儲存最長姓名的長度
    for (int i = 0; i < x; i++) {
        int len = strlen(tempNames[i]);  // 計算當前姓名的長度
        if (len > y) {
            y = len;  // 更新最長長度
        }
    }
    cout << "\n long name lens: " << y << endl;
    
    // ===================步驟4: 找出第一個空格的最大位置===================
    int maxSpacePos = 0;  // 儲存所有姓名中第一個空格的最大位置
    for (int i = 0; i < x; i++) {
        // 在每個姓名中尋找第一個空格
        for (int j = 0; j < strlen(tempNames[i]); j++) {
            if (tempNames[i][j] == ' ') {  // 找到空格
                if (j > maxSpacePos) {
                    maxSpacePos = j;  // 更新最大空格位置
                }
                break; // 找到第一個空格就跳出內層迴圈
            }
        }
    }
    cout << "maxSpacePos " << maxSpacePos << endl;
    
    // ===================步驟5: 建立最終的二維字元陣列===================
    char** studentNames = new char*[x];  // 建立最終儲存對齊姓名的二維陣列
    for (int i = 0; i < x; i++) {
        studentNames[i] = new char[y + 1];  // 每個姓名分配最長長度+1的空間（+1是為了字串結尾的'\0'）
    }
    
    // ===================步驟6: 將姓名放入二維陣列並對齊第一個空格===================
    //對齊處理
    
    for (int i = 0; i < x; i++) {
        // 先將整個陣列填滿空格字元
        for (int j = 0; j < y; j++) {
            studentNames[i][j] = ' ';   //把第 i 個學生姓名字串的第 j 個位置，填上空白字元 ' '
        }
        studentNames[i][y] = '\0';  // 在最後加上字串結尾符號(要標記結束)
        
        // 找出這個姓名的第一個空格位置
        int currentSpacePos = -1; // 預設為-1表示沒找到空格
        for (int j = 0; j < strlen(tempNames[i]); j++) { //學生的名子長度
            if (tempNames[i][j] == ' ') {
                currentSpacePos = j;  // 記錄第一個空格的位置
                break;
            }
        }
        
        // 計算姓名在對齊陣列中的開始位置
        int startPos;
        if (currentSpacePos == -1) {
            // 如果姓名沒有空格，就將整個姓名靠右對齊
            startPos = y - strlen(tempNames[i]);
        } else {
            // 如果有空格，計算要往右偏移多少位置才能讓第一個空格對齊到maxSpacePos
            startPos = maxSpacePos - currentSpacePos;
        }
        
        // 將原始姓名複製到對齊後的位置
        for (int j = 0; j < strlen(tempNames[i]); j++) {
            //因為 studentNames[i] 的長度是 y，要避免放超出範圍
            if (startPos + j < y) { // 確保不會超出陣列範圍
                studentNames[i][startPos + j] = tempNames[i][j];
                //從 tempNames 拿字，按照算好的位置，放到 studentNames 裡
                //startPos 這個名字應該從哪裡開始排
                //j = 正在處理第幾個字元
            }
        }
    }
    
    // ===================步驟7: 顯示格式化後的結果===================
    cout << "\nStudent list (aligned by first space):" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < x; i++) {
        cout << studentNames[i] << endl;  
    }
    cout << "-----------------------------------" << endl;
    
    // ===================步驟8: 釋放動態分配的記憶體===================
    // 先釋放每個字串的記憶體
    for (int i = 0; i < x; i++) {
        delete[] studentNames[i];  // 釋放最終陣列中每個字串的記憶體
        delete[] tempNames[i];     // 釋放暫時陣列中每個字串的記憶體
    }
    // 再釋放指標陣列的記憶體
    delete[] studentNames;  // 釋放最終指標陣列的記憶體
    delete[] tempNames;     // 釋放暫時指標陣列的記憶體
    
    return 0;
}