#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

struct Marble {
    int value;
    Marble* prev_marble;
    Marble* next_marble;
};

unsigned int getHighestScore( const unsigned int&, const unsigned int& );
Marble* insertAtOffset( Marble*, int, const int );
Marble* removeAtOffset( Marble*, int );
int valueAtOffset( Marble*, int );
void printMarbleCircle( Marble* );

int main( void ) {
    //cout << getHighestScore( 9, 25 ) << endl; //Debug 
    //cout << getHighestScore( 435, 71184 ) << endl; //Part 1
    cout << getHighestScore( 435, 7118400 ) << endl; //Part 2

    return EXIT_SUCCESS; 
}

unsigned int getHighestScore( const unsigned int& players, const unsigned int& marbles ) {
    unsigned int highest_score, curr_player;
    vector<unsigned int> scores( players, 0 );
    curr_player = highest_score = 0;
    Marble* curr_marble = NULL;
    curr_marble = insertAtOffset( curr_marble, 0, 0 );
    for( unsigned int m = 1; m <= marbles; ++m ) {
        //printMarbleCircle( curr_marble );
        if( m % 23 == 0 ) {
            scores[curr_player] += m + valueAtOffset( curr_marble, -7 );
            curr_marble = removeAtOffset( curr_marble, -7 );
        }
        else {
            curr_marble = insertAtOffset( curr_marble, 1, m );
        }
        ++curr_player;
        if( curr_player >= scores.size() )
            curr_player = 0;
    }
    for( unsigned int s = 0; s < scores.size(); ++s ) {
        if( scores[s] > highest_score )
            highest_score = scores[s];
    }
    return highest_score;
}

Marble* insertAtOffset( Marble* curr_marble, int offset, const int val ) {
    Marble* new_marble = new Marble;
    new_marble->value = val;
    if( curr_marble == NULL ) {
        new_marble->prev_marble = new_marble;
        new_marble->next_marble = new_marble;
    }
    else{
        if( offset >= 0) {
            while( offset-- > 0 ) {
                curr_marble = curr_marble->next_marble;
            }
        }
        else {
            while( offset++ < 0 ) {
                curr_marble = curr_marble->prev_marble;
            }
        }
        new_marble->prev_marble = curr_marble;
        new_marble->next_marble = curr_marble->next_marble;
        curr_marble->next_marble->prev_marble = new_marble;
        curr_marble->next_marble = new_marble;
    }
    return new_marble;
}

Marble* removeAtOffset( Marble* curr_marble, int offset ) {
    Marble* tmp_marble;
    if( offset > 0) {
        while( offset-- > 0 ) {
            curr_marble = curr_marble->next_marble;
        }
    }
    if( offset < 0 ) {
        while( offset++ < 0 ) {
            curr_marble = curr_marble->prev_marble;
        }
    }
    tmp_marble = curr_marble->next_marble;
    curr_marble->next_marble->prev_marble = curr_marble->prev_marble;
    curr_marble->prev_marble->next_marble = curr_marble->next_marble;
    delete curr_marble;
    return tmp_marble;
}

int valueAtOffset( Marble* curr_marble, int offset ) {
    if( offset > 0) {
        while( offset-- > 0 ) {
            curr_marble = curr_marble->next_marble;
        }
    }
    if( offset < 0 ) {
        while( offset++ < 0 ) {
            curr_marble = curr_marble->prev_marble;
        }
    }
    return curr_marble->value;
}

void printMarbleCircle( Marble* curr_marble ) {
    Marble* tmp_marble = curr_marble;
    cout << "(" << curr_marble->value << ") ";
    while( curr_marble->next_marble != tmp_marble ) {
        curr_marble = curr_marble->next_marble;
        cout << curr_marble->value << " ";
    }
    cout << endl;
}