#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int getCheckSum( void );
pair<int, int> getCounts( const string& );

int main( void ) {
    cout << getCheckSum() << endl;
    return EXIT_SUCCESS; 
}

int getCheckSum( void ) {
    int rep_twice, rep_thrice;
    string input;
    rep_twice = rep_thrice = 0;
    while( cin >> input ) {
        pair<int, int> counts = getCounts( input );
        rep_twice += counts.first;
        rep_thrice += counts.second;
    }
    return rep_thrice * rep_twice;
}

pair<int, int> getCounts( const string& input ) {
    int letter_count[26] = { 0 };
    int count1, count2, tmp;
    count1 = count2 = 0;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        tmp = input[i] - 'a';
        ++letter_count[tmp];
    }
    for( unsigned int i = 0; i < 26; ++i ) {
        if( letter_count[i] == 2 )
            count1 = 1;
        if( letter_count[i] == 3 )
            count2 = 1;
    }
    return make_pair( count1, count2 );
}