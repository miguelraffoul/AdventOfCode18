#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void parseInput( unordered_map<string, char>&, string& );
pair<int, int> getSumAfterGenerations( unordered_map<string, char>&, const string&, const int );
int expandString( string& );

int main( void ) {
    unordered_map<string, char> rules;
    string inital_config;
    pair<int, int> results;

    parseInput( rules, inital_config );
    results = getSumAfterGenerations( rules, inital_config, 100 );

    cout << "Sum: " << results.first << endl;
    cout << "Initial position starts at: " << results.second << endl;

    return EXIT_SUCCESS; 
}

void parseInput( unordered_map<string, char>& rules, string& inital_config ) {
    string input1, input2, input3;
    cin >> input1 >> input2 >> input3;
    inital_config = input3;
    while( cin >> input1 >> input2 >> input3 ) {
        rules[input1] = input3[0];
    }
}

pair<int, int> getSumAfterGenerations( unordered_map<string, char>& rules, const string& inital_config, const int generations ) {
    string prev_gen, new_gen( inital_config );
    int sum, initial_pos;
    sum = initial_pos = 0;
    cout << "0: " << new_gen << endl;
    for( int gen = 1; gen <= generations; ++gen ) {
        initial_pos += expandString( new_gen );
        prev_gen = new_gen;
        for( unsigned int i = 2; i < new_gen.size() - 2; ++i ) {
            string tmp( prev_gen.begin() + (i - 2), prev_gen.begin() + (i + 3) );
            if( rules.find( tmp ) != rules.end() ) {
                new_gen[i] = rules[tmp];
            }
            else {
                new_gen[i] = '.';   
            }
        }
        cout << gen << ": " << new_gen << endl;
    }
    sum = 0;
    for( unsigned int i = 0; i < new_gen.size(); ++i ) {
        if( new_gen[i] == '#' ) {
            sum += i - initial_pos;
        }
    }
    return make_pair( sum, initial_pos );
}

int expandString( string& new_gen ) {
    int first_idx = new_gen.find_first_of( '#' );
    int last_idx = new_gen.find_last_of( '#' );
    int head_chars = 4 - first_idx >= 0 ? 4 - first_idx : 0;
    int tail_chars = 4 - (new_gen.size() - 1 - last_idx) >= 0 ? 4 - (new_gen.size() - 1 - last_idx) : 0;
    if( head_chars > 0 )
        new_gen = string( head_chars, '.' ) + new_gen;
    if( tail_chars > 0 )
        new_gen += string( tail_chars, '.' );
    return head_chars;
}