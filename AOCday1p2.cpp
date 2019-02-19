#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int getRepFrequency( const vector<string>& );

int main( void ) {
    vector<string> change_list;
    string input;

    while( cin >> input ){
        change_list.push_back( input );
    }
    cout << getRepFrequency( change_list ) << endl;
    
    return EXIT_SUCCESS; 
}

int getRepFrequency( const vector<string>& change_list ) {
    unordered_set<int> unique_freqs;
    string freq_change;
    int freq = 0;
    char op;
    while( true ) {
        for( unsigned int x = 0; x < change_list.size(); ++x ) {
            freq_change = change_list[x];
            op = freq_change[0];
            freq_change[0] = ' ';
            if( op == '+' )
                freq += stoi( freq_change );
            if( op == '-' )
                freq -= stoi( freq_change );
            if( unique_freqs.insert( freq ).second == false )
                return freq;
        }
    }
    return 0;
}