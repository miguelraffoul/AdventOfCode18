#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string getCorrectCommonLetters( const vector<string>& );

int main( void ) {
    vector<string> box_ids;
    string input;

    while( cin >> input ) {
        box_ids.push_back( input );
    }
    cout << getCorrectCommonLetters( box_ids ) << endl;
    
    return EXIT_SUCCESS; 
}

string getCorrectCommonLetters( const vector<string>& box_ids ) {
    string common_letters;
    for( unsigned int box1 = 0; box1 < box_ids.size(); ++box1 ) {
        for( unsigned int box2 = box1 + 1; box2 < box_ids.size(); ++box2 ) {
            common_letters = "";
            for( unsigned int l = 0; l < box_ids[box1].size(); ++l ) {
                if( box_ids[box1][l] == box_ids[box2][l] )
                    common_letters += box_ids[box1][l];
            }
            if( common_letters.size() == box_ids[box1].size() - 1 )
                return common_letters;
        }
    }
    return common_letters;
}