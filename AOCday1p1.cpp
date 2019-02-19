#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int getFrequency( void );

int main( void ) {
    cout << getFrequency() << endl;
    return EXIT_SUCCESS; 
}

int getFrequency( void ) {
    string input;
    char op;
    int freq = 0;
    while( cin >> input ) {
        op = input[0];
        input[0] = ' ';
        if( op == '+' )
            freq += stoi( input );
        if( op == '-' )
            freq -= stoi( input );
    }
    return freq;
}