#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stack>

using namespace std;
using namespace std::chrono;


class lru{
    private:
    int capacity;
    int countFaults;
    stack<int> pages;
    public:
    lru(int cap){
        capacity = cap;
        countFaults = 0;
    }
    void access(int page){
        int num = pages.size();
        if(num == 0 && capacity == 0){
            countFaults++;
            return;
        }
        bool found = false;
        stack<int> tmp;
        while(!pages.empty() && (!found || capacity == 0)){
            if(pages.top() == page){
                found = 1;
            }
            else{
                tmp.push(pages.top());
            }
            pages.pop();
        }
        if(capacity == 0 && !found){
            if(!tmp.empty()){
                tmp.pop();
            }
        }
        while(!tmp.empty()){
            pages.push(tmp.top());
            tmp.pop();
        }
        pages.push(page);
        if(!found) countFaults++;
        if(!found && capacity>0) capacity--;
    }
    int getCountOfFaults(){
        return countFaults;
    }
    //useful to debug
    /*
    void printStack(){
        stack<int> tmp;
        while(!pages.empty()){
            tmp.push(pages.top());
            cout<<pages.top()<<"  "; 
            pages.pop();
        }
        cout<<endl;
        while(!tmp.empty()){
            pages.push(tmp.top());
            tmp.pop();
        }
    }
    */
};

int main(){

    int sum = 0;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int k=0;k<100;k++)
    {
        lru l(25);
       int q;
       cin>>q;
       int v[q];
    for(int j=0;j<q;j++)
    {
        cin>>v[j];
    }
    vector<int> page_access_slot;
    for(int i = 0;i<q;i++){
	l.access(v[i]);
        
    }
        cout<<l.getCountOfFaults()<<endl;
        sum+=l.getCountOfFaults();
    }
    cout<<sum<<endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << duration;

    return 0;
}
