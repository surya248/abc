#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;


class lru{
    private:
    int capacity;
    int countFaults;
    int now;
    vector<int> pages;
    vector<int> timeCount;
    int sz;
    void checkOverFlow(){
        if(now + 5 ==  (1<<30)){
            int timeMin = *min_element(timeCount.begin(),timeCount.end());
            for(int i = 0; i<sz; i++){
                timeCount[i]-=timeMin;
            }
            now-=timeMin;
        }
    }
    public:
    lru(int cap){
        capacity = cap;
        countFaults = 0;
        sz = 0;
        now = 0;
        pages.resize(capacity);
        timeCount.resize(capacity);
    }
    void access(int page){
        now++;
        int minCountIndex = 0;
        for(int i=0;i<sz;i++){
            if(pages[i] == page){
                timeCount[i] = now;
                this->checkOverFlow();
                return;
            }
            else if(timeCount[i]<timeCount[minCountIndex]){
                minCountIndex = i;
            }
        }
        countFaults++;
        if(sz<capacity){
            pages[sz] = page;
            timeCount[sz] = now;
            sz++;
        }
        else{
            pages[minCountIndex] = page;
            timeCount[minCountIndex] = now;
        }
        this->checkOverFlow();
    }
    int getCountOfFaults(){
        return countFaults;
    }};
    //useful to debug
    /*
    void printCounter(){
        for(int i = 0; i<sz; i++){
            cout<<pages[i] << "   " << timeCount[i] << endl;;
        }    
    }
    */

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
