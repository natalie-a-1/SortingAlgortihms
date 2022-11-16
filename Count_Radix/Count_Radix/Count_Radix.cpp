#include <iostream>
#include <vector>
#include<cmath>
#include <unordered_map>
using namespace std;
// ---------------------------------------------------------------
// Task 1: Define a CountSort Class
// ---------------------------------------------------------------
// Below is a class for counting sort.
//
// It has a private vector "list" that holds the list to sort.
// All member functions should operate on "list".
//
// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. ListMax: return the maximum value in "list"
// 4. SortList: sort "list" based on the counting sort algorithm.
class CountSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    int ListMax();
    void SortList();
private:
    vector<int> list;
};

void CountSort::SetList(vector<int> InputList) {
    list = InputList;
}

vector<int> CountSort::GetList() {
    return list;
}
int CountSort::ListMax() {
    int max = 0;
    for (int i = 0; i < list.size(); i++) {
        max = std::max(list[i], max);
    }
    return max;
}
void CountSort::SortList() {
    int max = ListMax();
    vector<int> countVector(max+1);
    vector<int> output(list.size());
    for (int i = 0; i < countVector.size(); i++) {
        countVector[i] = 0;
    }
    for (int i = 0; i < list.size(); i++) {
        countVector[list[i]]++;
    }
    for (int i = 1; i <= max; i++) {
        countVector[i] += countVector[i - 1];
      }
    for (long i = list.size() - 1; i >= 0; i--) {
        output[countVector[list[i]] - 1] = list[i];
        countVector[list[i]]--;
      }
    for (int i = 0; i < list.size(); i++) {
        list[i] = output[i];
    }
}
// ..............................................................
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// Task 2: Define a RadixSort Class
// ---------------------------------------------------------------
// Below is a class for RadixSort.
//
// It has a private vector "list" that holds the list to sort.
// All member functions should operate on "list".
//
// It has several public member functions.
// 1. SetList: assign a vector (to sort) to "list".
// 2. GetList: return the current "list"
// 3. GetNumBit: return the maximum number of bits of any element in "list"
//    Example: if "list"={35,27,9}, then return 2
//    Example: if "list"={352,22027,19}, then return 5
// 4. GetList_ByBit (int IdxBit): return the "IdxBit"_th LSB's in "list"
//    Example: if "list"={35,27,9} & IdxBit=1, then return a list {5,7,9}
//    Example: if "list"={35,27,9} & IdxBit=2, then return a list {3,2,0}
//    The returned list should be stored in an integer vector (not string or other)
// 5. SortList_byBit (int IdxBit): sort "list" based on the IdxBit_th LSB in "list"
//    Need to call counting sort to do the sorting.
//    If there is a tie between two elements, preserve their order
//    Example: if "list"={42,22,7} & IdxBit=1, then return 42,22,7
//    Example: if "list"={42,22,7} & IdxBit=2, then return 7,22,42
class RadixSort {
public:
    void SetList(vector<int> InputList);
    vector<int> GetList();
    int GetNumBit();
    vector<int> GetList_byBit(int IdxBit);
    void SortList_byBit(int IdxBit);
private:
    vector<int> list;
};

void RadixSort::SetList(vector<int> InputList) {
    list = InputList;
}
vector<int> RadixSort::GetList() {
    return list;
}
int RadixSort::GetNumBit(){
    int maxBit = 0;
    int size = 0;
    for (int i = 0; i < list.size(); i++) {
        size = trunc(log10(list[i])) + 1;
        maxBit = std::max(maxBit, size);
    }
    return maxBit;
}
vector<int> RadixSort::GetList_byBit(int IdxBit) {
    vector<int> bitVector(list.size());
    int power = pow(10, IdxBit);
    int tempVal = 0;
    int div = pow(10, IdxBit-1);
    for (int i = 0; i < list.size(); i++) {
        tempVal = list[i] % power;
        bitVector[i] = tempVal / div;
    }
    return bitVector;
}

void RadixSort::SortList_byBit(int IdxBit) {
    vector<int> countList;
    countList = GetList_byBit(IdxBit);
    std::unordered_multimap<int,int> map;
    for (int i = 0; i < list.size(); i++) {
        map.insert(pair<int, int>(countList[i], list[i]));
    }
    
    vector<int> temp;
    CountSort count;
    count.SetList(countList);
    count.SortList();
    temp = count.GetList();
    for (int i = 0; i < temp.size(); i++) {
        int tempVal = temp[i];
        auto iteratorX = map.find(tempVal);
        if (iteratorX != map.end()) {
            temp[i] = iteratorX -> second;
            map.erase(iteratorX);
        }
    }
    SetList(temp);
}
// ..............................................................
// ---------------------------------------------------------------
int main()
{
    // The main function is given to you.
    // We first input the testing mode, IdxBit and an arbitrary number of non-
    //repeated integers into a vector.
    // The input of this list will terminate when we give an non-integer input
    //e.g., letter 'a'.
    // Then, we pass this vector to the CountSort and RadixSort objects.
    // Then, we test your implemented member functions.
    vector<int> InputList;
    vector<int> TestList;
    int  mode, IdxBit;
    CountSort x;
    RadixSort y;
    // takie inputs
//    cin >> mode >> IdxBit;
//    while (cin >> temp) {
//        InputList.push_back(temp);
//    }
    // pass inputs to class objects
    mode = 7;
    IdxBit = 2;
    InputList = { 233, 425, 22023, 9071, 42};
    x.SetList(InputList);
    y.SetList(InputList);
    // start testing functions
    switch (mode) {
        case 1: // check if input of CountSort is corret
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 2: // check if input of RadixSort is corret
            TestList = y.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 3: // check if ListMax of CountSort is correct
            cout << x.ListMax() << endl;
            break;
        case 4: // check if SortList of CountSort is correct
            x.SortList();
            TestList = x.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
            
        case 5: // check if GetNumBit of RadixSort is correct
            cout << y.GetNumBit() << endl;
            break;
        case 6: // check if GetNumBit of RadixSort is correct
            TestList = y.GetList_byBit(IdxBit);
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
        case 7: // check if SortList_byBit of RadixSort is correct
            y.SortList_byBit(IdxBit);
            TestList = y.GetList();
            for (int i = 0; i < TestList.size(); i++) {
                cout << TestList.at(i) << endl;
            }
            break;
    }
    return 0;
}
