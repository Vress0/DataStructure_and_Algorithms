#include <iostream>
#include <cstring>  
using namespace std;

int main() {
    int x;
    cout << "please enter the number of students: ";
    cin >> x;
    cin.ignore(); // 清除緩衝區中的換行符號

    // 步驟1: 用char陣列暫時儲存姓名
    char** tempNames = new char*[x];
    for (int i = 0; i < x; i++) {
        tempNames[i] = new char[100]; // 假設姓名不超過100字元
    }

    // 步驟2: 輸入所有姓名
    for (int i = 0; i < x; i++) {
        cout << "please enter " << (i + 1) << " student name: ";
        cin.getline(tempNames[i], 100);
    }

    // 步驟3: 找出最長的姓名長度
    int y = 0;
    for (int i = 0; i < x; i++) {
        int len = strlen(tempNames[i]);
        if (len > y) {
            y = len;
        }
    }
    cout << "\n最長姓名長度: " << y << endl;

    // 步驟4: 找出第一個空格的最大位置
    int maxSpacePos = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < strlen(tempNames[i]); j++) {
            if (tempNames[i][j] == ' ') {
                if (j > maxSpacePos) {
                    maxSpacePos = j;
                }
                break; // 找到第一個空格就跳出
            }
        }
    }
    cout << "第一個空格最大位置: " << maxSpacePos << endl;

    // 步驟5: 建立最終的二維字元陣列
    char** studentNames = new char*[x];
    for (int i = 0; i < x; i++) {
        studentNames[i] = new char[y + 1];
    }

    // 步驟6: 將姓名放入二維陣列（第一個空格對齊）
    for (int i = 0; i < x; i++) {
        // 先填滿空格
        for (int j = 0; j < y; j++) {
            studentNames[i][j] = ' ';
        }
        studentNames[i][y] = '\0';

        // 找出這個姓名的第一個空格位置
        int currentSpacePos = -1; // 預設為-1表示沒找到空格
        for (int j = 0; j < strlen(tempNames[i]); j++) {
            if (tempNames[i][j] == ' ') {
                currentSpacePos = j;
                break;
            }
        }

        // 計算開始位置並複製姓名
        int startPos;
        if (currentSpacePos == -1) {
            // 如果沒有空格，從最右邊開始放置
            startPos = y - strlen(tempNames[i]);
        } else {
            startPos = maxSpacePos - currentSpacePos;
        }

        // 確保起始位置不會是負數
        if (startPos < 0) startPos = 0;

        for (int j = 0; j < strlen(tempNames[i]); j++) {
            if (startPos + j < y) { // 防止陣列越界
                studentNames[i][startPos + j] = tempNames[i][j];
            }
        }
    }

    // 步驟7: 顯示結果
    cout << "\nStudent list (aligned by first space):" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < x; i++) {
        cout << "|" << studentNames[i] << "|" << endl;
    }
    cout << "-----------------------------------" << endl;

    // 步驟8: 釋放記憶體
    for (int i = 0; i < x; i++) {
        delete[] studentNames[i];
        delete[] tempNames[i];
    }
    delete[] studentNames;
    delete[] tempNames;

    return 0;
}