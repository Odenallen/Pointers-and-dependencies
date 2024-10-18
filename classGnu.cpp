#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <sstream>
#include <atomic>
#include <unordered_map>
using namespace std;

class WaterManager {
public:
    void hyenaEnters();
    void gnuEnters();
    void hyenaLeaves();
    void gnuLeaves();
    int getRandomInt(int min, int max);
    condition_variable cv;
    mutex m;
    atomic<int> nrH = 0;
    atomic<int> nrG = 0;
};
// Global variables
bool output = true;
unordered_map<thread::id, string> threadMap;
int nrHyenas = 4;
int idHyenas = 1;
WaterManager wm;

class Gnu{
    public:
    int id;
    Gnu(int givenId): id(givenId){};
    void operator()();
    int getRandomInt(int min, int max);
    friend ostream & operator<<(ostream & os, const Gnu & g);

};
ostream & operator<<(ostream & os, const Gnu & g){os<< "Gnu nr "<< g.id << " is thirsty\n"<< endl; return os;}

void Gnu::operator()(){
    if (output){
        
        cout << *this;
        }
    
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(getRandomInt(1,5)));
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    //cout << "The new Gnu slept for : " << elapsed_seconds.count() << "s\n";
    int i = 0;
    while (true) {
        wm.gnuEnters();
        // see monitoring class below
        // drink water for a while i.e. sleep for a short while
        auto s2 = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(getRandomInt(1,3)));
        auto e2 = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = e2-s2;
        wm.gnuLeaves();
        //cout <<"Gnu leaves the waterhole after drinking for " <<  elapsed_seconds.count() <<"s\n";
        i++;
        if (i == 1) break;
    }
}

int Gnu::getRandomInt(int min, int max){
    //Returns a random integer between min and max (inclusive)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
};


void WaterManager::hyenaEnters(){
    std::unique_lock<std::mutex> lock(m);
    //cout << nrH << " Hyenas and " << nrG << " Gnus\n)" << endl;
    cv.wait(lock, [this] { return nrG == 0; });
    nrH++;
    if (output){
    cout << "Hyena enters the waterhole.                       Hyenas = " << nrH  << ", Gnus = "<< nrG << endl;}
    cv.notify_all();
};

void WaterManager::gnuEnters() {
    std::unique_lock<std::mutex> lock(m);
    //cout << "a Gnu wants to enter the waterhole. There are now " << nrH << " Hyenas and " << nrG << " Gnus\n)" << endl;
    cv.wait(lock, [this] { return nrH == 0; });
    nrG++;
    if (output){
    cout << "Gnu enters the waterhole.                       Hyenas = " << nrH  << ", Gnus = "<< nrG << endl;}
    cv.notify_all();
    
 };

void WaterManager::hyenaLeaves() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [this] { return nrG == 0; });
    nrH-=1;
    if (output){cout << "Hyena leaves the waterhole.                       Hyenas = " << nrH  << ", Gnus = "<< nrG << endl;}
    cv.notify_all();
    
};

void WaterManager::gnuLeaves() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [this] { return nrH == 0; });
    nrG-=1;
    if (output){cout << "Gnu leaves the waterhole.                       Hyenas = " << nrH  << ", Gnus = "<< nrG << endl;}
    cv.notify_all();
};


int getRandomInt(int min, int max){
    //Returns a random integer between min and max (inclusive)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
};

//void hyena(WaterManager& wm){
void hyena(){

    //auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(getRandomInt(1,5)));
    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end-start;
    //cout << "The new Hyena slept for : " << elapsed_seconds.count() << "s\n";

    int i = 0;
    while (true) {
        if (output){
            threadMap[std::this_thread::get_id()] = "Hyena nr " + to_string(idHyenas);
            idHyenas++;

            cout << threadMap[std::this_thread::get_id()] <<" is thursty\n";}
        

        wm.hyenaEnters();
        auto s2 = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::seconds(getRandomInt(1,3)));
        auto e2 = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = e2-s2;
        wm.hyenaLeaves();
        i++;
        if (i == 1) break;
    }
};


int main(int argc, char* argv[]){

    cout << "Starting simulation ";

    if (argc > 1)   // If there is an argument, we will show output
       { output = false;
        cout <<"without output: \n" << endl;}
    else{
        cout <<"with output: \n" << endl;}

    


    vector<thread> threadvec;

    Gnu firstG(1);
    std::function<void(void)> threadjob1 = firstG;
    threadvec.push_back(thread(threadjob1));
    
    Gnu secG(2);
    std::function<void(void)> threadjob2 = secG;
    
    threadvec.push_back(thread(threadjob2));

    Gnu thirdG(3);
    std::function<void(void)> threadjob3 = thirdG;
    
    threadvec.push_back(thread(threadjob3));

    for (int i = 0; i < nrHyenas; i++)
    threadvec.push_back(thread(hyena));


    for (auto& thread : threadvec)
        thread.join();
    cout << "\n Key and value pairs: \n";
    for (auto& thread: threadMap)
        cout << thread.second << " has id " << thread.first << endl;

    cout << "\n Simulation finished\n";
    return 0;
};