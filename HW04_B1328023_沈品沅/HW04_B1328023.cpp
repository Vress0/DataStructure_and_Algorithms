#include<iostream>
using namespace std;

struct Node{
    int coef; //係數
    int exp; //指數
    Node* next; // next是一個pointer，裡面存的是下一個Node的位址
};


// 建立一個空的，回傳頭節點指標
Node* createPoly() {
    Node* head = new Node();    //在記憶體裡新建一個 Node，名稱叫 head
    head->next = 0;
    head->coef = -1;
    head->next = head; // 讓頭節點的next指向自己，形成環狀結構
    return head;
}


// 插入一個新節點到多項式中，保持指數由大到小的順序
void insertTerm(int coef,int exp,Node* c){
    if (coef == 0) return; // 如果係數為0，不插入

    Node* prev = c;
    Node* curr = c->next;

    // 找到插入位置
    //只要還沒掃回頭，而且目前節點的 exponent 還比你要插入的 exponent 大，就繼續往後移動
    while (curr->exp >exp && curr != c){ 
        prev = curr;
        curr = curr->next;
    }

    //同指數合併
    if (curr->exp == exp && curr != c) {
        curr->coef += coef;

        // 如果合併後係數為0，刪除該節點
        if (curr->coef == 0) { 
            prev->next = curr->next;
            delete curr;
        }
        return;
    }

    // 若沒有相同的exponent，則插入新節點
    Node* newNode = new Node(); 
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = curr;   // 新node指向目前的節點
    prev->next = newNode;   // 前一個node指向新node
}



// 多項式相乘
Node* multiply(Node* a,Node* b){
    Node* c = createPoly(); //先建立一個空的多項式C

    Node* pa = a->next; //指向多項式A的第一個節點
    while(pa != a){ //只要還沒回到頭節點，就繼續往下走
        
        Node* pb = b->next; //指向多項式B的第一個節點
        while(pb != b){

            int newcoef = pa->coef * pb->coef; // 計算新係數相乘
            int newexp = pa->exp + pb->exp; //計算新指數相加

            insertTerm(newcoef,newexp,c); //將新項插入多項式C中
            pb = pb->next; //移動到多項式B的下一個節點
        }
        pa = pa->next; //移動到多項式A的下一個節點
    }

    return c; //回傳結果多項式C
}

// 列印多項式
void printPoly(Node* p) {
    Node* curr = p->next; //指向第一個節點
    bool first = true; //用來判斷是否為第一個項

    while (curr != p){
        if (!first)
            cout << " + "; //非第一項前面加上加號
        cout << curr->coef << "x^" << curr->exp; 
        first = false; //標記已經處理過第一項
        curr = curr->next; //移動到下一個節點
    }
    cout << endl;
}



int main(){

    int m;
    cout << "Enter number of terms in polynomial A: ";
    cin >> m;

    Node* polyA = createPoly(); //建立多項式A

    for (int i = 0; i < m;i++){
        int c, e;
        cout << "Enter coef exp for A:\n";
        cin >> c >> e;
        insertTerm(c, e, polyA);
    }


    int n;
    cout << "Enter number of terms in polynomial B: ";
    cin >> n;

    Node* polyB = createPoly(); //建立多項式B

    for (int i = 0; i < n;i++){
        int c, e;
        cout << "Enter coef exp for B:\n";
        cin >> c >> e;
        insertTerm(c, e, polyB);
    }


    cout << "\nA(x) = ";
    printPoly(polyA);

    cout << "B(x) = ";
    printPoly(polyB);

    Node* c = multiply(polyA, polyB);

    cout << "\nC(x) = A(x) * B(x) = ";
    printPoly(c);


    return 0;
}









