/*
 * Powered By Quilt
 * 通用功能型 LinkedList
 * http://www.quilt.idv.tw/
 */

#include <iostream>
#include <bits/stdc++.h>
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

int getOSType() {
#ifdef _WIN32
    return 0;
#elif _WIN64
    return 1;
#elif __unix || __unix__
    return 2;
#elif __APPLE__ || __MACH__
    return 3;
#elif __linux__
    return 4;
#elif __FreeBSD__
    return 5;
#else
    return 6;
#endif
}

void init() {
    if (getOSType() <= 1) {
        system("title Homework - Linked List");
        system("color 3f");
    } else {
        system("echo \"\033]0;Homework - Linked List\007\"");
    }
    srand(time(NULL));
}

void helloWorld() {
    cout << "Hello World !" << endl;
}

template<typename T>
string showArray(T* data, size_t size) {
    stringstream ret;
    ret << "[ ";
    for (size_t i = 0; i < size; ++i) {
        ret << data[i];
        ret << " ";
    }
    ret << "]";
    return ret.str();
}

int main() {
    init();

    // 測試程式碼
    int arrayA[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};

    cout << "鏈結串列 :" << endl;
    LinkedList<int> LLA(arrayA), LLB, LLC(LLA), LLD, LLE;
    cout << "串列 A : " << LLA.show() << endl;
    cout << "串列 B : " << LLB.show() << endl;
    cout << "串列 C : " << LLC.show() << endl;

    cout << "串列 B 是否為空 : " << LLB.isEmpty() << endl;

    LLA.insert(2, 6987);
    cout << "串列 A 註標 2 插入 6987 : " << LLA.show() << endl;

    LLA.remove(7);
    cout << "串列 A 移除註標 7 元素 : " << LLA.show() << endl;

    for (int i = 0; i <= 20; ++i) {
        LLB.add(i + 10);
    }
    cout << "串列 B 大量插入 : " << LLB.show() << endl;
    cout << endl;

    cout << "串列 B 詳細情形 :" << endl;
    cout << LLB.showDetail() << endl;
    cout << endl;

    cout << "串列 B 是否存在 >= 29 數值 : " << (LLB.findGreaterEqual(29) != NULL) << endl;
    cout << "串列 A C 相等比較 : " << (LLA == LLC) << endl;
    cout << "串列 A B 小於比較 : " << (LLA < LLB) << endl;

    LLC.removeByValue(10);
    cout << "串列 C 移除元素 10 : " << LLC.show() << endl;

    cout << "串列 A 大小 : " << LLA.length() << " B 大小 : " << LLB.length() << " C 大小 : " << LLC.length() << endl;
    cout << "串列 A 註標 5 元素 : " << LLA[5] << endl;
    cout << "串列 B 查詢元素 15 位置 : " << LLB.indexOf(15) << endl;

    LLC.reverse();
    cout << "串列 C 反轉 : " << LLC.show() << endl;

    LLC.set(2, 123);
    cout << "串列 C 修改註標 2 位置元素 123 : " << LLC.show() << endl;

    int* output = LLC.toArray();
    cout << "串列 C 轉換為陣列 : " << showArray(output, LLC.size()) << endl;
    delete[] output;

    cout << "串列 A 疊代 : [ ";
    for (LinkedList<int>::iterator itr = LLA.begin(); itr != NULL; ++itr) {
        cout << *itr << " ";
    }
    cout << "]" << endl;

    LLC.clear();
    cout << "串列 C 清空 : " << LLC.show() << endl;

    for (int i = 0; i < 10; ++i) {
        LLD.push_back(rand() % 100);
    }
    cout << "串列 D 原始資料 : " << LLD.show() << endl;
    cout << "串列 D 最小值 : " << LLD.min() << endl;
    LLD.sort();
    cout << "串列 D 排序 : " << LLD.show() << endl;

    for (int i = 0; i < 10; ++i) {
        int value = rand() % 100;
        LLE.insertBefore(LLE.findGreaterEqual(value), value);
    }
    cout << "串列 E 自動插入排序 : " << LLE.show() << endl;
    cout << endl;

    cout << "堆疊 :" << endl;
    int arrayB[] = {20, 40, 60, 80, 100};
    Stack<int> STKA(arrayB, 1), STKB(1), STKC(STKA);
    cout << "堆疊 A : " << STKA.show() << endl;
    cout << "堆疊 B : " << STKB.show() << endl;
    cout << "堆疊 C : " << STKC.show() << endl;

    cout << "堆疊 B 是否為空 : " << STKB.isEmpty() << endl;

    STKA.push(6987);
    cout << "堆疊 A 壓入元素 6987 : " << STKA.show() << endl;

    for (int i = 0; i <= 20; ++i) {
        STKB.push(i * 5);
    }
    cout << "堆疊 B 大量壓入元素 : " << STKB.show() << endl;

    cout << "堆疊 B 堆疊頂元素 : " << STKB.top() << endl;

    STKC.pop();
    cout << "堆疊 C 彈出元素 : " << STKC.show() << endl;

    cout << "堆疊 A 大小 : " << STKA.size() << " 堆疊 B 大小 " << STKB.size() << " 堆疊 C 大小 : " << STKC.size() << endl;

    STKC.clear();
    cout << "堆疊 C 清空 : " << STKC.show() << endl;
    cout << endl;

    cout << "佇列 :" << endl;
    int arrayC[] = {30, 60, 90, 120, 150, 180};
    Queue<int> QEA(arrayC), QEB(1), QEC(QEA);
    cout << "佇列 A : " << QEA.show() << endl;
    cout << "佇列 B : " << QEB.show() << endl;
    cout << "佇列 C : " << QEC.show() << endl;

    QEA.push(1234);
    cout << "佇列 A 壓入元素 1234 : " << QEA.show() << endl;

    for (int i = 0; i <= 30; ++i) {
        QEB.push(i * 20);
    }
    cout << "佇列 B 大量壓入元素 : " << QEB.show() << endl;

    cout << "佇列 B 頭部元素 : " << QEB.front() << endl;
    cout << "佇列 B 尾端元素 : " << QEB.back() << endl;

    QEC.pop();
    cout << "佇列 C 彈出元素 : " << QEC.show() << endl;

    cout << "佇列 A 大小 : " << QEA.size() << " 佇列 B 大小 " << QEB.size() << " 佇列 C 大小 : " << QEC.size() << endl;

    QEC.clear();
    cout << "佇列 C 清空 : " << QEC.show() << endl;
    cout << endl;

    cout << "請按 Enter 鍵繼續 ... ";
    cin.get();
    return EXIT_SUCCESS;
}
