#include <iostream>
using namespace std;

class CppArray {
private:
    float* arr; // 用來指向動態配置的浮點陣列
    int size;   // 用來記錄陣列長度

public:
    // (a) 建構子 : 幫你建立並初始化一個陣列
    CppArray(int s, float initvalue) {  // 需要使用者提供大小"s"與初始值"initvalue"
        size = s;
        arr = new float[size];          // 在記憶體中「動態開一塊空間」，大小是 size，裡面每個格子能放一個 float。
        for (int i = 0; i < size; i++) {
            arr[i] = initvalue;         // 把每一格都設定成使用者輸入的初始值
        }
    }

    // (b) 複製建構子 : 用另一個現有的物件，建立出一個新的物件
    CppArray(const CppArray& cp2) {     // 要建立一個新的 CppArray 物件，並且用「另一個現有的 CppArray 物件」 (cp2) 的內容來初始化它。
                                        // const：表示這個 cp2 不會被修改。
                                        // &：用「參考 (reference)」的方式傳入（效率比較高，不用整份複製進來）。

        size = cp2.size;                // 把「舊陣列的大小」複製過來。
        arr = new float[size];          // 它不是直接用舊的陣列，而是重新 new 出一份新的空間。這樣兩個物件的陣列不會共用同一塊記憶體。
        for (int i = 0; i < size; i++) {    // 一格一格把舊陣列的內容，複製到新的陣列裡。
            arr[i] = cp2.arr[i];
        }
    }

    // (c) 指派運算子 : 當你已經有兩個現成的物件，想要讓一個變得「和另一個一模一樣」時，它負責幫你安全地複製內容。(operator=)
    CppArray& operator=(const CppArray& cp2) {
        //當我們寫 a = b; 時，就會自動執行這個函式。
        //const CppArray& cp2：要複製的來源（右邊那個物件 b）
        //CppArray&：回傳自己（左邊那個物件 a）
        //cp2 永遠是右邊那個「被拿來複製的物件」
        if (this == &cp2) return *this; // 避免自我指派 a=a 的情況
        delete[] arr;   //清除「舊的陣列」
        size = cp2.size;    // 把右邊物件（b）的大小複製過來。
        arr = new float[size];
        for (int i = 0; i < size; i++) {   // 一格一格把右邊物件（b）的內容，複製到左邊物件（a）的陣列裡。
            arr[i] = cp2.arr[i];
        }
        return *this;  // 回傳自己（左邊那個物件 a）
    }

    // (d) 解構子 : 物件生命週期結束時自動呼叫，釋放動態記憶體
    ~CppArray() {
        delete[] arr;           // 釋放以 new[] 配置的陣列記憶體
    }

    // (e) 下標運算子（含範圍檢查）:　它讓你的物件看起來就像「陣列」一樣能用中括號操作(operator[])
    float& operator[](int i) {
        if (i < 0 || i >= size) {
            cerr << " Index out of range! (index = " << i << ")" << endl;
            exit(1);
        }
        return arr[i];
        // 檢查索引 2 是否有效 
        //         ↓
        // 回傳 arr[2] 的參考
        //         ↓
        // 把 9.9 寫進該位址

    }



// operator是定義[的關鍵字


    // (f) 取得陣列大小
    int GetSize() const {
        return size;
    }

    // (g) 友元運算子：輸出與輸入
    // 我允許這兩個函式進來看我的私有資料（arr、size）
    // 這兩個函式能直接存取私有成員
    friend ostream& operator<<(ostream& os, const CppArray& cp); // 輸出運算子多載宣告
    friend istream& operator>>(istream& is, CppArray& cp);       // 輸入運算子多載宣告
};

// 輸出 << ：逐元素輸出，元素間以空白分隔
ostream& operator<<(ostream& os, const CppArray& cp) {
    for (int i = 0; i < cp.size; i++) {      // 走訪每個元素
        os << cp.arr[i] << " ";             // 輸出元素值與一個空白
    }
    return os;                               // 回傳串流以支援連續輸出（e.g., cout << a << b）
}

/*
定義一個函式，
這個函式可以讓我把 CppArray 物件印出來。
它會接收兩個東西：
1. 一條輸出通道（os，例如 cout）
2. 一個要被印出的陣列物件（cp）
然後把 cp 的內容逐一送到 os 裡去。
*/



// 輸入 >> ：依序讀入 cp.size 個值並寫入陣列
istream& operator>>(istream& is, CppArray& cp) {
    for (int i = 0; i < cp.size; i++) {      // 走訪每個索引
        is >> cp.arr[i];                     // 從輸入串流讀入一個 float 值
    }
    return is;                               // 回傳串流以支援連續輸入（e.g., cin >> a >> b）
}

// ======================================================
//  主程式：完整測試 (a)~(g)
// ======================================================
int main() {

    cout << "========== (a) 建構子測試 ==========\n";
    int size;
    float initValue;
    cout << "請輸入陣列大小：";
    cin >> size;
    cout << "請輸入初始值：";
    cin >> initValue;
    CppArray a(size, initValue);
    cout << "建立完成：a = " << a << endl;

    cout << "\n========== (b) 複製建構子測試 ==========\n";
    CppArray b = a;      // ← 這裡就會呼叫「複製建構子」(會建立一個新陣列 b，內容跟 a 一樣)
    cout << "以 a 建立 b，b = " << b << endl;


    cout << "\n========== (c) 指派運算子測試 ==========\n";
    cout << "執行 a = b ..." << endl;
    a = b;  // ← 這裡就會呼叫「指派運算子」 
    cout << "指派完成：a = " << a << endl;


    cout << "\n========== (e) 下標運算子測試--修改 ==========\n";
    int index;
    float newValue;
    cout << "請輸入要修改的索引 (0 ~ " << a.GetSize() - 1 << "): ";
    cin >> index;
    cout << "請輸入新值：";
    cin >> newValue;
    a[index] = newValue; // 使用下標運算子回傳參考來賦值
    cout << "修改後的 a = " << a << endl;

    cout << "\n========== (e) 下標運算子測試--讀取 ==========\n";
    cout << "請輸入要查看的索引 (0 ~ " << a.GetSize() - 1 << "): ";
    cin >> index;
    cout << "a[" << index << "] = " << a[index] << endl;

    cout << "\n========== (f) GetSize() 測試 ==========\n";
    cout << "目前 a 的大小為：" << a.GetSize() << endl;

    cout << "\n========== (g) 輸入運算子測試 ==========\n";
    cout << "請依序輸入 " << a.GetSize() << " 個新值：";
    cin >> a;
    cout << "輸入完成，新 a = " << a << endl;

    cout << "\n==========  全部測試完成  ==========\n";
    return 0;
}
