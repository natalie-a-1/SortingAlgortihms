#include <iostream>
#include <vector>
#include<cmath>
#include <unordered_map>
using namespace std;
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
int main()
{
    vector<int> InputList;
    vector<int> TestList;
    int  mode, IdxBit;
    CountSort x;
    RadixSort y;
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
