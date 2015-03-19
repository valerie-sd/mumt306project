#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <stdbool.h>
#include <vector>
//#include <boost/thread/thread.hpp>
#include "RtMidi.h"
#include <unistd.h>
#include <thread>
#include <time.h>
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

#define NOTEON 144
#define PGMCH 192
#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3
#define CH5 4
#define CH6 5
#define CH7 6
#define CH8 7
#define CH9 8
#define CHDr 9
#define CH11 10
#define CH12 11
#define CH13 12
#define CH14 13
#define CH15 14
#define CH16 15

// Platform-dependent sleep routines.
#if defined(__WINDOWS_MM__)
#include <windows.h>
#define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds )
#else // Unix variants
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif
bool chooseMidiPort( RtMidiOut *rtmidi );
void one();
void two();

std::vector<unsigned int> factors;
std::vector<unsigned int> sorted_factors;
std::vector<unsigned int> dupes_out;
std::vector<unsigned char> low;
std::vector<unsigned char> med;
std::vector<unsigned char> high;
std::vector<unsigned char> low_off;
std::vector<unsigned char> med_off;
std::vector<unsigned char> high_off;

unsigned int chords[3][7];

RtMidiOut *midiout = 0;

//int * keys = [0, 7];

unsigned int this_key = 21;
unsigned int this_chord = 0;

void randomize(){
    //srandomdev();
    srand (time(NULL));
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
    low[1] = this_key+chords[0][this_chord];
    med[1] = this_key+chords[1][this_chord];
    high[1] = this_key+chords[2][this_chord];
    low_off[1] = this_key+chords[0][this_chord];
    med_off[1] = this_key+chords[1][this_chord];
    high_off[1] = this_key+chords[2][this_chord];

}
void one(){//channel 0 in 0-index, 1 in 1-index
    //for A: use 33 or 45
    int iterations = 0;
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(192);
    pgm_ch.push_back(35);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    //std::cout<<"in one\n";

    //SLEEP(2400);
    while(iterations<23){
        //std::cout<<"bass iterations: "<<iterations<<"\n";
        randomize();
        midiout->sendMessage( &low );
        SLEEP(380);
        midiout->sendMessage( &low_off );
        midiout->sendMessage( &low );
        SLEEP(200);
        midiout->sendMessage( &low_off );
        midiout->sendMessage( &low );
        SLEEP(200);
        midiout->sendMessage( &low_off );
        midiout->sendMessage( &high );
        SLEEP(380);
        midiout->sendMessage( &high_off );
        midiout->sendMessage( &low );
        midiout->sendMessage( &med );
        SLEEP(380);
        midiout->sendMessage( &low_off );
        midiout->sendMessage( &med_off );
        midiout->sendMessage( &high );
        SLEEP(200);
        midiout->sendMessage( &high_off );
        midiout->sendMessage( &med );
        SLEEP(200);
        midiout->sendMessage( &med_off );
        midiout->sendMessage( &high );
        SLEEP(380);
        midiout->sendMessage( &high_off );

        midiout->sendMessage( &high );
        SLEEP(380);
        midiout->sendMessage( &high_off );

        midiout->sendMessage( &high );
        SLEEP(200);
        midiout->sendMessage( &high_off );

        midiout->sendMessage( &med );
        SLEEP(200);
        midiout->sendMessage( &med_off );

        midiout->sendMessage( &low );
        SLEEP(200);
        midiout->sendMessage( &low_off );

        midiout->sendMessage( &low );
        SLEEP(200);
        midiout->sendMessage( &low_off );
        
        midiout->sendMessage( &high );
        SLEEP(380);
        midiout->sendMessage( &high_off );

        iterations++;
    }
    low[1] = this_key+12;
    midiout->sendMessage( &low );
    SLEEP(400);
    midiout->sendMessage( &low_off );
    midiout->sendMessage( &low );
    SLEEP(400);
    midiout->sendMessage( &low_off );
    midiout->sendMessage( &low );
    SLEEP(400);
    midiout->sendMessage( &low_off );
    midiout->sendMessage( &low );
    SLEEP(400);
    midiout->sendMessage( &low_off );
    midiout->sendMessage( &low );
    SLEEP(1600);
    midiout->sendMessage( &low_off );
    exit(1);

}
void two(){//channel 1 in 0-index, 2 in 1-index
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(193);
    pgm_ch.push_back(11);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    int iterations = 0;
    std::vector<unsigned char> send;
    send.push_back(145);
    send.push_back(36+this_key);
    send.push_back(100);
    SLEEP(2*4800);
    while(iterations<6){
        //std::cout<<"iterations for two: "<<iterations<<"\n";

        midiout->sendMessage( &send );
        SLEEP(2000);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 43+this_key;
        midiout->sendMessage( &send );
        SLEEP(400);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 34+this_key;
        midiout->sendMessage( &send );
        send[1] = 41+this_key;
        SLEEP(50);
        midiout->sendMessage( &send );
        send[1] = 38+this_key;
        SLEEP(50);
        midiout->sendMessage( &send );
        SLEEP(7100);//2300+4800
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = 41+this_key;
        midiout->sendMessage( &send );
        send[1] = 38+this_key;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 36+this_key;
        iterations++;
    }
}
void three(){
    int iterations = 0;
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH3);
    pgm_ch.push_back(50);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    
    std::vector<unsigned char> send;
    send.push_back(CH3+NOTEON);
    send.push_back(24+this_key);
    send.push_back(80);
    SLEEP(3*4800);
    while(iterations<8){
        //std::cout<<"iterations for three: "<<iterations<<"\n";

        midiout->sendMessage( &send );
        //send[1] = 45+chords[1][this_chord];
        //midiout->sendMessage( &send );
        //send[1] = 45+chords[1][this_chord];
        //midiout->sendMessage( &send );
        SLEEP(2400);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 80;
        send[1] = 12+this_key+chords[2][this_chord];
        //SLEEP(100);
        midiout->sendMessage( &send );
        //send[1] = 45+chords[1][this_chord];
        //SLEEP(300);
        //midiout->sendMessage( &send );
        //send[2] = 60;
        
        SLEEP(7200);//2400+4800
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 80;
        send[1] = 12+this_key+chords[2][this_chord];
        iterations++;
    }
}
void four(){
    int iterations = 0;
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH4);
    pgm_ch.push_back(26);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    SLEEP(4*4800);
    std::vector<unsigned char> send;
    send.push_back(CH4+NOTEON);
    send.push_back(59);
    send.push_back(60);
    //SLEEP(12000);//4800+2400
    while(iterations<8){
        for(int a = 0; a<4; a++){
            midiout->sendMessage( &send );
            SLEEP(300);
            send[2] = 0;
            midiout->sendMessage( &send );
            send[2] = 60;
        }
        send[1] = 55;
        midiout->sendMessage( &send );
        SLEEP(300);
        send[1] = 59;
        midiout->sendMessage( &send );
        SLEEP(300);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = 59;
        midiout->sendMessage( &send );

        
        send[2] = 60;
        send[1] = 62;
        midiout->sendMessage( &send );
        SLEEP(600);
        send[1] = 55;
        for(int b=0; b<8; b++){
            midiout->sendMessage( &send );
            SLEEP(300);
            send[2] = 0;
            midiout->sendMessage( &send );
            send[2] = 55;
        }
        
        SLEEP(300);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = 59;
        iterations++;
    }
}
void five(){
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH5);
    pgm_ch.push_back(77);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    int iterations = 0;
    std::vector<unsigned char> send;
    send.push_back(NOTEON+CH5);
    send.push_back(24+this_key);
    send.push_back(80);
    SLEEP(5*4800);
    //SLEEP(14400);
    while(iterations < 8){
        unsigned int value = random() % 3;
        send[1] = this_key+chords[value][this_chord]+12;
        midiout->sendMessage( &send );
        unsigned int new_value = value+1;
        if(new_value==4){
            new_value = 0;
        }
        send[1] = this_key+chords[new_value][this_chord]+12;
        midiout->sendMessage( &send );
        int interval = random () % 3;
        interval = (interval+1)*400;
        SLEEP(interval);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = this_key+chords[value][this_chord]+12;
        midiout->sendMessage( &send );
        send[2] = 80;
        SLEEP(3600);
        iterations++;
    }
}
void six(){
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH6);
    pgm_ch.push_back(54);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    int iterations = 0;
    std::vector<unsigned char> send;
    send.push_back(NOTEON+CH6);
    send.push_back(40+this_key);
    send.push_back(100);
    SLEEP(6*4800);
    //SLEEP(14400);
    while(iterations < 3){
        //std::cout<<"iterations for six: "<<iterations<<"\n";
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[1] = 36+this_key;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = 40+this_key;
        midiout->sendMessage( &send );
        
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[1] = 43+this_key;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[1] = 40+this_key;
        midiout->sendMessage( &send );
        send[2] = 100;
        
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        midiout->sendMessage( &send );
        SLEEP(200);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 43+this_key;
        midiout->sendMessage( &send );
        SLEEP(400);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 36+this_key;
        midiout->sendMessage( &send );
        SLEEP(400);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        send[1] = 40+this_key;
        midiout->sendMessage( &send );
        SLEEP(400);
        send[2] = 0;
        midiout->sendMessage( &send );
        send[2] = 100;
        SLEEP(14400);//1200 + 2400
        iterations++;
    }
}
void seven(){
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH7);
    pgm_ch.push_back(116);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    SLEEP(3*4800);
    int iterations = 0;
    std::vector<unsigned char> send;
    send.push_back(NOTEON+CH7);
    send.push_back(24+this_key);
    send.push_back(80);
    //SLEEP(14400);
    while(iterations < 18){
        unsigned int value = random() % 3;
        send[1] = this_key+chords[value][this_chord]+12;
        midiout->sendMessage( &send );
        unsigned int new_value = value+1;
        if(new_value==4){
            new_value = 0;
        }
        send[1] = this_key+chords[new_value][this_chord]+12;
        midiout->sendMessage( &send );
        SLEEP(400);
        iterations++;
    }
}

void mandatory(){
    //std::cout<<"in mandatory thread\n";
    //shifts the key
    SLEEP(2400*26);
    std::cout<<"key changed\n";
    this_key += 7;
    SLEEP(2400*8);
    this_key -= 7;
    std::cout<<"key changed again\n";
    SLEEP(2400);
    std::vector<unsigned char> pgm_ch;
    pgm_ch.push_back(PGMCH+CH8);
    pgm_ch.push_back(119);
    midiout->sendMessage( &pgm_ch );
    pgm_ch.clear();
    
    std::vector<unsigned char> send;
    send.push_back(CH8+NOTEON);
    send.push_back(59);
    send.push_back(30);
    midiout->sendMessage( &send );
    SLEEP(200);
    send[2] = 40;
    midiout->sendMessage( &send );
    SLEEP(150);
    send[2] = 50;
    midiout->sendMessage( &send );
    SLEEP(120);
    send[2] = 60;
    midiout->sendMessage( &send );
    SLEEP(90);
    send[2] = 70;
    midiout->sendMessage( &send );
    SLEEP(90);
    send[2] = 80;
    midiout->sendMessage( &send );
    SLEEP(90);
    send[2] = 90;
    midiout->sendMessage( &send );
    SLEEP(90);
    send[2] = 100;
    for(unsigned int b=100; b>19; b-=20){
        send[2] = b;
        for(int a=0; a<4; a++){
            midiout->sendMessage( &send );
            SLEEP(100);
        }
    }
    send[2] = 80;
    send[1] = 46;
    midiout->sendMessage( &send );
    SLEEP(100);
    send[2] = 0;
    midiout->sendMessage( &send );
    send[2] = 80;
    send[1] = 51;
    midiout->sendMessage( &send );
    SLEEP(100);
    send[2] = 0;
    midiout->sendMessage( &send );
}
void percussion(int n){
    //std::cout<<"drums playing\n";
    //if(n != 6){}else{
    int iterations = 0;
    std::vector<unsigned char> send;
    send.push_back(CHDr+NOTEON);
    send.push_back(36);
    send.push_back(60);
    SLEEP(2400);
    while(iterations<30){
        midiout->sendMessage( &send );
        SLEEP(400);
        midiout->sendMessage( &send );
        SLEEP(400);
        send[1] = 38;
        midiout->sendMessage( &send );
        send[1] = 36;
        SLEEP(400);
        midiout->sendMessage( &send );
        SLEEP(400);
        send[1] = 38;
        midiout->sendMessage( &send );
        SLEEP(200);
        midiout->sendMessage( &send );
        SLEEP(200);
        midiout->sendMessage( &send );
        SLEEP(400);
        send[1] = 36;
        iterations++;
    }
    //}
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
    
    low.push_back(144);
    low.push_back(45);
    low.push_back(80);
    med = low;
    high = low;
    low_off = low;
    low_off[2] = 0;
    med_off = low_off;
    high_off = low_off;
    
}
void sort(){
    for(unsigned int y = 0; y<100; y++){
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
    bool input_done = false;
    unsigned int input;
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
    // RtMidiOut constructor
    try {
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    // Call function to select port.
    try {
        if ( chooseMidiPort( midiout ) == false ) delete midiout;
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        delete midiout;
    }
    std::cout<<input<<"\nFactors:\n";
    bool factoring_done = false;
    unsigned int divisor = 1;
    unsigned int count_factors = 0;
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
        factors[i] = factors[i] % 100;
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
    bool percussion_started = false;


    std::vector<unsigned char> send;
    send.push_back(CH8+NOTEON);
    send.push_back(59);
    send.push_back(100);
    midiout->sendMessage( &send );
    SLEEP(600);
    send[2] = 0;
    midiout->sendMessage( &send );

    //boost::thread t_mandatory(mandatory);
    //std::thread t_mandatory(mandatory);
    //std::cout<<"thread initiated\n";
    
    for (unsigned int k = 0; k < dupes_out.size(); k++){
        std::cout<<dupes_out[k]<<", ";
        if(dupes_out[k]==1){
            //boost::thread t_one(one);
            std::thread t_one(one);
        }
        else if(dupes_out[k]==2){
            //SLEEP(2*4800);
            //boost::thread t_two(two);
            std::thread t_two(two);

        }
        else if(dupes_out[k]==3){
            //SLEEP(3*4800);
            //boost::thread t_three(three);
            std::thread t_three(three);
        }
        else if(dupes_out[k]==4){
            //SLEEP(4*4800);
            //boost::thread t_four(four);
            std::thread t_four(four);
        }
        else if(dupes_out[k]==5){
            //SLEEP(5*4800);
            //boost::thread t_five(five);
            std::thread t_five(five);
        }
        else if(dupes_out[k]==6){
            //SLEEP(6*4800);
            //boost::thread t_six(six);
            std::thread t_six(six);
        }
        else if(dupes_out[k]==7){
            //SLEEP(7*4800);
            //boost::thread t_seven(seven);
            std::thread t_seven(seven);
        }
        else{
            if(!percussion_started){
                //std::cout<<"percussion started\n";
                //boost::thread t_else(percussion, dupes_out[k]);
                std::thread t_else(percussion, dupes_out[k]);
                percussion_started = true;
            }
        }
    }
    SLEEP(2400);
    std::cout<<"\n";
    std::cout<<"Number of unique factors after mod 100: "<<dupes_out.size()<<"\n";
    
    return 0;
}
bool chooseMidiPort( RtMidiOut *rtmidi )
{
    std::cout << "\nWould you like to open a virtual output port? [y/N] ";
    
    std::string keyHit;
    std::getline( std::cin, keyHit );
    if ( keyHit == "y" ) {
        rtmidi->openVirtualPort();
        return true;
    }
    
    std::string portName;
    unsigned int i = 0, nPorts = rtmidi->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No output ports available!" << std::endl;
        return false;
    }
    
    if ( nPorts == 1 ) {
        std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
    }
    else {
        for ( i=0; i<nPorts; i++ ) {
            portName = rtmidi->getPortName(i);
            std::cout << "  Output port #" << i << ": " << portName << '\n';
        }
        
        do {
            std::cout << "\nChoose a port number: ";
            std::cin >> i;
        } while ( i >= nPorts );
    }
    
    std::cout << "\n";
    rtmidi->openPort( i );
    
    return true;
}
