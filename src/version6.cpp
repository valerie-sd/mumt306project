#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <stdbool.h>
#include <vector>
//#include <boost/thread/thread.hpp>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <fstream>
//#include <boost/system/error_code.hpp>
////////////////////////////////////////////////////////////////////////////////
// MAC: Comment in srandomdev(); comment out rand() (one occurrence)
// LINUX: Comment out srandomdev(); comment in ran() 
///////////////////////////////////////
// TO RUN WITH C++11
// -Comment out all boost:: lines, commenting in the std:: version next to them.
// -Comment out boost in #include statements, and comment in #include <thread>

// TO RUN WITHOUT C++11
// -Install boost thread and system libraries
// -Comment in all places using boost::, while commenting out the adjacent std:: versions.
// -Comment in the two boost #include lines, and comment out the #include <thread> line.
///////////////////////////////////////////////////////////////////////////////


#define DIVISION 600 //number of clock pulses per quarter note; for header

//#include <unistd.h>
//#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )


std::vector<int> factors;
std::vector<int> sorted_factors;
std::vector<int> dupes_out;
std::vector<int> to_run (13, 0);

int low;
int med;
int high;

int chords[3][7];

int this_key = 21;
int this_chord = 0;



void randomize(){
    //srandomdev();
    //srand (time(NULL));
    int number = random() % 100;
    //std::cout<<"Random number: "<<number<<"\n";
    int tenth = number/10;
    if(tenth<2){
        this_chord = 0;
    }
    else if(tenth==2 || tenth==3){
        this_chord = 1;
    }
    else if(tenth==4){
        this_chord = 2;
    }
    else if(tenth==5){
        this_chord = 3;
    }
    else if(tenth==6){
        //this_chord = 4;
        this_chord = 6;
    }
    else if(tenth==7 || tenth==8){
        this_chord = 5;
    }
    else{
        this_chord = 6;
    }
    //std::cout<<"This chord: "<<this_chord<<"\n";
    low = this_key+chords[0][this_chord];
    med = this_key+chords[1][this_chord];
    high = this_key+chords[2][this_chord];

}
void one(){//channel 11 in 0-index, 12 in 1-index
    std::fstream channel_12 ("ch12.csv", std::fstream::out | std::fstream::trunc);//These are one-indexed!

    //for A: use 33 or 45
    if(to_run[1]==1){

        int iterations = 0;
        int elapsed = 0;
        channel_12<<"11, 0, Start_track\n11, 0, Program_c, 11, "<<35<<"\n";
        //std::cout<<"in one\n";

        while(iterations<23){
            //std::cout<<"bass iterations: "<<iterations<<"\n";
            randomize();
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 0\n";
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";

            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";

            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";

            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<med<<", 0\n";

            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";

            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
            elapsed += 200;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
            
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 80\n";
            elapsed += 400;
            channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<high<<", 0\n";

            iterations++;
        }
        low = this_key+12;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
        elapsed += 400;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
        elapsed += 400;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
        elapsed += 400;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
        elapsed += 400;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 80\n";
        elapsed += 1600;
        channel_12<<"11, "<<elapsed<<", Note_on_c, 11, "<<low<<", 0\n";

        channel_12<<"11, "<<elapsed<<", End_track\n";
    }
    channel_12.close();

}
void two(){//channel 1 in 0-index, 2 in 1-index
    std::fstream channel_3 ("ch3.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[2]==1){
        //std::cout<<"two should go...";
        int iterations = 0;
        int elapsed = 0;
        //elapsed_1.push_back(elapsed);
        channel_3<<"2, 0, Start_track\n2, 0, Program_c, 2, "<<11<<"\n";

        //channel_3<<"3, 0, Control_c, 2, 7, 89\n3, 0, Control_c, 2, 10, 64\n3, 0, Control_c, 2, 91, 70\n";


        //std::cout<<"in one\n";
        elapsed += 4800*2;
        int key = this_key;
        while(iterations<6){
            key = this_key;
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<36+key<<", 60\n";
            elapsed += 2000;
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<36+key<<", 0\n";
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<43+key<<", 60\n";
            elapsed += 400;
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<43+key<<", 0\n";
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<34+key<<", 60\n";
            elapsed += 50;
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<41+key<<", 60\n";
            elapsed += 50;
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<38+key<<", 60\n";
            elapsed += 7100;//2300+4800
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<34+key<<", 0\n";
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<41+key<<", 0\n";
            channel_3<<"2, "<<elapsed<<", Note_on_c, 2, "<<38+key<<", 0\n";
        
            iterations++;
        }
        channel_3<<"2, "<<elapsed<<", End_track\n";
    }
    channel_3.close();
}
void three(){
    std::fstream channel_4 ("ch4.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[3]==1){
        int iterations = 0;
        int elapsed = 0;
        channel_4<<"3, 0, Start_track\n3, 0, Program_c, 3, "<<50<<"\n";
        elapsed += 4800*3;
        int key = this_key;
        int chord = this_chord;
        while(iterations<8){
            key = this_key;
            chord = this_chord;
            channel_4<<"3, "<<elapsed<<", Note_on_c, 3, "<<24+key<<", 80\n";
            elapsed += 2400;
            channel_4<<"3, "<<elapsed<<", Note_on_c, 3, "<<24+key<<", 0\n";
            
            channel_4<<"3, "<<elapsed<<", Note_on_c, 3, "<<12+chords[2][chord]+key<<", 80\n";
            elapsed +=7200;
            channel_4<<"3, "<<elapsed<<", Note_on_c, 3, "<<12+chords[2][chord]+key<<", 0\n";

            iterations++;
        }
        channel_4<<"3, "<<elapsed<<", End_track\n";
    }
    channel_4.close();
}
void nine(){
    std::fstream channel_5 ("ch5.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[9]==1){
        int iterations = 0;
        int elapsed = 0;
        channel_5<<"4, 0, Start_track\n4, 0, Program_c, 4, "<<26<<"\n";
        elapsed += 4800*4;
        while(iterations<8){
            for(int a=0; a<4; a++){
                channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<59<<", 60\n";
                elapsed += 300;
                channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<59<<", 0\n";
            }
            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<55<<", 60\n";
            elapsed += 300;
            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<59<<", 60\n";
            elapsed += 300;
            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<55<<", 0\n";
            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<59<<", 0\n";

            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<62<<", 60\n";
            elapsed += 600;
            channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<62<<", 0\n";

            
            for(int b=0; b<8; b++){
                channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<55<<", 60\n";
                elapsed += 300;
                channel_5<<"4, "<<elapsed<<", Note_on_c, 4, "<<55<<", 0\n";
            }
            elapsed += 300;

            iterations++;
        }
        channel_5<<"4, "<<elapsed<<", End_track\n";
    }
    channel_5.close();
}
void five(){
    std::fstream channel_6 ("ch6.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[5]==1){
        int elapsed = 0;
        int iterations = 0;
        channel_6<<"5, 0, Start_track\n5, 0, Program_c, 5, "<<77<<"\n";
        elapsed += 4800*5;
        int key = this_key;
        int chord = this_chord;
        int value, new_value;
        while(iterations<8){
            value = random() % 3;
            new_value = value+1;
            if(new_value>3){
                new_value=0;
            }
            key = this_key;
            chord = this_chord;
            channel_6<<"5, "<<elapsed<<", Note_on_c, 5, "<<key+chords[value][chord]+12<<", 80\n";
            channel_6<<"5, "<<elapsed<<", Note_on_c, 5, "<<key+chords[new_value][chord]+12<<", 80\n";
            int interval = random () % 3;
            interval = (interval+1)*400;
            elapsed += interval;

            channel_6<<"5, "<<elapsed<<", Note_on_c, 5, "<<key+chords[value][chord]+12<<", 0\n";
            channel_6<<"5, "<<elapsed<<", Note_on_c, 5, "<<key+chords[new_value][chord]+12<<", 0\n";
            elapsed += 3600;

            iterations++;
        }
        channel_6<<"5, "<<elapsed<<", End_track\n";
    }
    channel_6.close();
}
void twelve(){
    std::fstream channel_7 ("ch7.csv", std::fstream::out | std::fstream::trunc);
    //a lot like 5; just vary the values longer. (gives a distribution determined by the chord)
    if(to_run[12]==1){
        int iterations = 0;
        int elapsed = 0;
        channel_7<<"6, 0, Start_track\n6, 0, Program_c, 6, "<<61<<"\n";
        elapsed += 4800*3;
        int key = this_key;
        int chord = this_chord;
        while(iterations<8){
            int value = random() % 3;
            int new_value = (value+1)%3;
            //if(new_value==4){new_value=0;} 
            key = this_key;
            chord = this_chord;
            channel_7<<"6, "<<elapsed<<", Note_on_c, 6, "<<key+chords[value][chord]+12<<", 80\n";
            elapsed += 300;
            channel_7<<"6, "<<elapsed<<", Note_on_c, 6, "<<key+chords[new_value][chord]+12<<", 80\n";
            int interval = random () % 3;
            interval = (interval+1)*200;
            elapsed += interval;

            channel_7<<"6, "<<elapsed<<", Note_on_c, 6, "<<key+chords[value][chord]+12<<", 0\n";
            elapsed += (interval*3);
            channel_7<<"6, "<<elapsed<<", Note_on_c, 6, "<<key+chords[new_value][chord]+12<<", 0\n";
            elapsed += 3600;

            iterations++;
        }
        channel_7<<"6, "<<elapsed<<", End_track\n";
    }
    channel_7.close();
}
void ten(){
    std::fstream channel_8 ("ch8.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[10]==1){
        int iterations = 0;
        int elapsed = 0;
        channel_8<<"7, 0, Start_track\n7, 0, Program_c, 7, "<<26<<"\n";
        elapsed += 4800*6;
        int key = this_key;
        while(iterations<3){
            key = this_key;
            for(int a=0; a<5; a++){
                channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
                elapsed += 200;
                channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            }
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";

            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<36+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<36+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";

            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 0\n";

            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 0\n";

            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 200;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";

            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 100\n";
            elapsed += 400;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<43+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<36+key<<", 100\n";
            elapsed += 400;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<36+key<<", 0\n";
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 100\n";
            elapsed += 400;
            channel_8<<"7, "<<elapsed<<", Note_on_c, 7, "<<40+key<<", 0\n";
            elapsed += 14400;

            iterations++;
        }
        channel_8<<"7, "<<elapsed<<", End_track\n";
    }
    channel_8.close();
}
void eight(){
    std::fstream channel_11 ("ch11.csv", std::fstream::out | std::fstream::trunc);
    if(to_run[8]==1){
        int iterations = 0;
        int elapsed = 0;
        channel_11<<"10, 0, Start_track\n10, 0, Program_c, 10, "<<116<<"\n";
        elapsed += 2400*5;
        int key = this_key;
        int chord = this_chord;
        while(iterations<18){
            int value = random() % 3;
            int new_value = (value+1)%3;
            //if(new_value==4){new_value=0;} 
            key = this_key;
            chord = this_chord;
            channel_11<<"10, "<<elapsed<<", Note_on_c, 10, "<<key+chords[value][chord]+12<<", 80\n";
            channel_11<<"10, "<<elapsed<<", Note_on_c, 10, "<<key+chords[new_value][chord]+12<<", 80\n";
            elapsed += 400;

            iterations++;
        }
        channel_11<<"10, "<<elapsed<<", End_track\n";
    }
    channel_11.close();
}

void mandatory(){
    std::fstream channel_9 ("ch9.csv", std::fstream::out | std::fstream::trunc);
    //std::cout<<"in mandatory thread\n";
    //shifts the key
    int elapsed = 0;
    elapsed += 2400*26;
    //std::cout<<"key changed\n";
    //this_key += 7;
    elapsed += 2400*8;
    //this_key -= 7;
    //std::cout<<"key changed again\n";
    elapsed += 2400;

    channel_9<<"8, 0, Start_track\n8, 0, Program_c, 8, "<<119<<"\n";

    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 30\n";
    elapsed += 200;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 40\n";
    elapsed += 150;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 50\n";
    elapsed += 120;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 60\n";
    elapsed += 90;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 70\n";
    elapsed += 90;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 80\n";
    elapsed += 90;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", 90\n";
    elapsed += 90;
    for(int b=100; b>19; b-=20){
        for(int a=0; a<4; a++){
            channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<59<<", "<<b<<"\n";
            elapsed += 100;
        }
    }
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<46<<", 80\n";
    elapsed += 100;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<46<<", 0\n";
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<51<<", 80\n";
    elapsed += 100;
    channel_9<<"8, "<<elapsed<<", Note_on_c, 8, "<<51<<", 0\n";

    channel_9<<"8, "<<elapsed<<", End_track\n";
    channel_9.close();
}
void percussion(){
    std::fstream channel_10 ("ch10.csv", std::fstream::out | std::fstream::trunc);
    int elapsed = 0;
    elapsed += 2400;
    channel_10<<"9, 0, Start_track\n";
    int iterations = 0;
    while(iterations < 30){
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<36<<", 60\n";
        elapsed += 400;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<36<<", 60\n";
        elapsed += 400;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<38<<", 60\n";
        elapsed += 400;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<36<<", 60\n";
        elapsed += 400;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<36<<", 60\n";
        elapsed += 400;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<38<<", 60\n";
        elapsed += 200;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<38<<", 60\n";
        elapsed += 200;
        channel_10<<"9, "<<elapsed<<", Note_on_c, 9, "<<38<<", 60\n";
        elapsed += 400;

        iterations ++;
    }
    channel_10<<"9, "<<elapsed<<", End_track\n";
    channel_10.close();
}
void chord_init(){//based from the octave below the desired one, for the -1s.
    //chords[3][7]
    chords[0][0] =12;
    chords[1][0] =16;
    chords[2][0] =19;
    
    chords[0][1] =12;
    chords[1][1] =17;
    chords[2][1] =21;
    
    chords[0][2] =11;
    chords[1][2] =17;
    chords[2][2] =19;
    
    chords[0][3] =11;
    chords[1][3] =14;
    chords[2][3] =19;
    
    chords[0][4] =12;
    chords[1][4] =15;
    chords[2][4] =19;
    
    chords[0][5] =12;
    chords[1][5] =16;
    chords[2][5] =22;
    
    chords[0][6] =14;
    chords[1][6] =17;
    chords[2][6] =21;
    
    low = 45;
    med = low;
    high = low;
    
}
void sort(){
    for(int y = 0; y<100; y++){
        for(unsigned int x=0; x<factors.size(); x++){
            if(factors[x] == y){
                sorted_factors.push_back(y);
            }
        }
    }
}
void remove_dupes(){
    dupes_out.push_back(sorted_factors[0]);
    for(unsigned int x=1; x<sorted_factors.size(); x++){
        if(sorted_factors[x]!=sorted_factors[x-1]){
            dupes_out.push_back(sorted_factors[x]);
        }
    }
}
int main(){
    chord_init();
    srand (time(NULL));

    bool input_done = false;
    int input;
    while(!input_done){
        std::cout<<"Input a number of 6 digits or less\n";
        std::string in;
        std::getline(std::cin, in);
        //int input = stoi(in, NULL, 10);
        input = atoi(in.c_str());
        if(input/1000000 == 0){
            input_done = true;
        }
    }
    std::cout<<input<<"\nFactors:\n";
    bool factoring_done = false;
    int divisor = 1;
    int count_factors = 0;
    while(!factoring_done){
        if (input % divisor == 0) {
            std::cout<<divisor<<"\n";
            factors.push_back(divisor);
            divisor ++;
            count_factors++;
        }
        else{
            std::cout<<"\t"<<divisor<<" is not a factor.\n";
            divisor++;
        }
        if (divisor > sqrt(input)) {
        //if(divisor>input/2){
            factoring_done = true;
        }
    }
    std::cout<<"Number of factors for "<<input<<": "<<count_factors<<"\n";
    std::cout<<"Factors: ";
    for (unsigned int i = 0; i < factors.size(); i++){
        //std::cout<<factors[i]<<", ";
        //factors[i] = factors[i] % 100;
        std::cout<<factors[i]<<", ";
    }
    std::cout<<"\n";
    sort();
    std::cout<<"Sorted: ";

    for (unsigned int j = 0; j < sorted_factors.size(); j++){
        std::cout<<sorted_factors[j]<<", ";
    }
    std::cout<<"\n";
    remove_dupes();
    std::cout<<"Duplicates removed.\n ";
    fflush(stdout);


    //boost::thread t_mandatory(mandatory);
    std::thread t_mandatory(mandatory);
    //std::cout<<"thread initiated\n";
    
    for (unsigned int k = 0; k < dupes_out.size(); k++){
        std::cout<<dupes_out[k]<<", ";
        to_run[dupes_out[k]] = 1;
    }
    std::cout<<"\n";
    for(unsigned int n = 0; n<to_run.size(); n++){
        //std::cout<<to_run[n]<<",";
    }
    //std::cout<<"\n";




    //boost::thread t_one(one);
    std::thread t_one(one);

    //boost::thread t_two(two);
    std::thread t_two(two);

    //boost::thread t_three(three);
    std::thread t_three(three);

    //boost::thread t_five(five);
    std::thread t_five(five);

    //boost::thread t_eight(eight);
    std::thread t_eight(eight);

    //boost::thread t_nine(nine);
    std::thread t_nine(nine);

    //boost::thread t_ten(ten);
    std::thread t_ten(ten);

    //boost::thread t_twelve(twelve);
    std::thread t_twelve(twelve);

    //boost::thread t_else(percussion, dupes_out[k]);
    std::thread t_else(percussion);
            

    t_mandatory.join();//9
    t_one.join();//12 CHANNEL (1-index)
    t_two.join();//3
    t_three.join();//4
    t_five.join();//6
    t_eight.join();//11
    t_nine.join();//5
    t_ten.join();//8
    t_twelve.join();//7
    t_else.join();//10

    int count_threads = 2;
    for(int a=0; a<13; a++){
        if(to_run[a]==1){
            if(a==1 || a==2 || a==3 || a==5 || a==8 || a==9 || a==10 || a==12){
                count_threads++;
                //std::cout<<"count_threads: "<<count_threads<<"\n";
            }
        }
    }

    std::cout<<"\n";
    std::cout<<"Number of unique factors after mod 100: "<<dupes_out.size()<<"\n";
    
    //std::cout<<"back to file ops\n";
    std::fstream main_file ("final_test.csv", std::fstream::in | std::fstream::out | std::fstream::trunc);

    main_file << "0, 0, Header, 1, "<< 1+count_threads <<", " << DIVISION << std::endl;

    main_file<<"1, 0, Start_track\n";
    main_file<<"1, 0, Title_t, \"Test program\"\n";
    main_file<<"1, 0, Time_signature, 4, 2, 24, 8\n";
    main_file<<"1, 0, Tempo, 600000\n";
    main_file<<"1, 0, End_track\n";

    

    std::ifstream ch_3 ("ch3.csv", std::fstream::in);
    if(to_run[2]==1){
        main_file << ch_3.rdbuf();
    }
    ch_3.close();

    std::fstream ch_4 ("ch4.csv", std::fstream::in);
    if(to_run[3]==1){
        main_file << ch_4.rdbuf();
    }
    ch_4.close();

    std::fstream ch_5 ("ch5.csv", std::fstream::in);
    if(to_run[9]==1){
        main_file << ch_5.rdbuf();
    }
    ch_5.close();

    std::fstream ch_6 ("ch6.csv", std::fstream::in);
    if(to_run[5]==1){
        main_file << ch_6.rdbuf();
    }
    ch_6.close();

    std::fstream ch_7 ("ch7.csv", std::fstream::in);
    if(to_run[12]==1){
        main_file << ch_7.rdbuf();
    }
    ch_7.close();

    std::fstream ch_8 ("ch8.csv", std::fstream::in);
    if(to_run[10]==1){
        main_file << ch_8.rdbuf();
    }
    ch_8.close();

    std::fstream ch_9 ("ch9.csv", std::fstream::in);
    main_file << ch_9.rdbuf();
    ch_9.close();

    std::fstream ch_10 ("ch10.csv", std::fstream::in);
    main_file << ch_10.rdbuf();
    ch_10.close();

    std::fstream ch_11 ("ch11.csv", std::fstream::in);
    if(to_run[8]==1){
        main_file << ch_11.rdbuf();
    }
    ch_11.close();

    std::fstream ch_12 ("ch12.csv", std::fstream::in);
    if(to_run[1]==1){
        main_file << ch_12.rdbuf();
    }
    ch_12.close();

    main_file << "0, 0, End_of_file\n";
    main_file.close();

    return 0;
}
