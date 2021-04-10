// ELEC 1520 : Spring 2021
// Student Name:Awdhah Rede
//
// CPP program to create a timer
#include <iomanip> 
#include <iostream> 
#include <stdlib.h> 
#include <unistd.h> 
#include <bitset>
#include <map>

// String processing
#include <algorithm>
#include <sstream>
#include <string.h>
#include<bits/stdc++.h>

using namespace std; 

map<unsigned int, unsigned char> SegmentTable;


// Return the binary encoding for the 7-segment display patterns
// Assume clock time of HH:MM:SS
// SS are bits 13..0
// MM are bits 27..14
// HH are bits 41..28
// bits 63..42 are 0

// Unsigned long is 64-bits: use bit manipulation and a system for eahc seven segment display
unsigned long generateClockControl(int hours, int minutes, int seconds)
{
    unsigned long h1=hours/10,h0=hours%10;  // 12   h1=1 h0=2
    unsigned long m1=minutes/10,m0=minutes%10;  // 34   m1=3 m0=4
    unsigned long s1=seconds/10,s0=seconds%10;  // 56   s1=5 s0=6
    
    map <unsigned int,unsigned char> SegmentTable;

    SegmentTable[0] = 0x00;
    SegmentTable[1] = 0X06;
    SegmentTable[2] = 0x5B;
    SegmentTable[3] = 0x4F;
    SegmentTable[4] = 0x66;
    SegmentTable[5] = 0x6D;
    SegmentTable[6] = 0x7D;
    SegmentTable[7] = 0x07;
    SegmentTable[8] = 0x67;
    SegmentTable[9] = 0x73;
    


    // Make a large 64 bit out ouf the 6 7-bit fields
    unsigned char buffer[8] = { SegmentTable[h1],SegmentTable[h0], SegmentTable[m1], SegmentTable[m0], SegmentTable[s1],SegmentTable[s0] };
    unsigned long long output;
    memcpy(&output, buffer, sizeof output);
    return output;
}

// function to display the timer 
void displayClock(int hours, int minutes, int seconds) 
{ 
    // system call to clear the screen
    system("clear");
    
    cout << setfill(' ') << setw(55) << "         TIMER         \n";
    cout << setfill(' ') << setw(55) << " --------------------------\n";
    cout << setfill(' ') << setw(29);
    cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
    cout << setfill('0') << setw(2) << minutes << " min | ";
    cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
    cout << setfill(' ') << setw(55) << " --------------------------\n";
    
    
    bitset<64> output(generateClockControl(hours, minutes, seconds));
    cout << ">" << output << '\n';
} 

void timer(int hours, int minutes, int seconds) 
{ 
    // infinte loop because timer will keep
    // counting. To kill the process press
    // Ctrl+c. If it does not work ask
    while (true) {
        
        // display the timer
        displayClock(hours, minutes, seconds);
        
        // sleep system call to sleep
        // for 1 second
        sleep(1);
        
        // increment seconds
        seconds++;
        
        // if seconds reaches 60
        if (seconds == 60) {
            
            // increment minutes
            minutes++;
            
            // if minutes reaches 60
            if (minutes == 60) {
                
                // increment hours
                hours++;
                minutes = 0;
            }
            seconds = 0;
        }
    }
} 

int main(int argc, char *argv[]) 
{ 
    // hours, minutes, seconds of timer
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    
    if (argc != 2) {
        cout << "This program takes one argument\n";
        exit(-1);
    }
    
    string time_of_day = string(argv[1]);
    // Decode the string into hours and minutes and seconds
    int temp=0;
    vector<int>store;
    for(auto x:time_of_day){
      if(x==':'){
        store.push_back(temp);
        cout<<temp<<endl;
        temp=0;
      }else temp=10*temp+( x-'0');
    }
    store.push_back(temp);
    hours=store[0];
    minutes=store[1];
    seconds=store[2];
    // Decode the string into the 4 digits
    timer(hours, minutes, seconds);
    
    return 0;
}
