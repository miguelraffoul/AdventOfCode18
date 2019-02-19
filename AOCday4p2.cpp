#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

pair<string, vector<string> > getEntryDetails( string& );
int getSeleepiestGuard( const map<string, vector<string> >& );
int addMinutes( const int&, const int&, vector<int>& );

int main( void ) {
    map<string, vector<string> > sorted_schedule;
    string input;

    while( getline( cin, input ) ) {
        sorted_schedule.insert( getEntryDetails( input ) );
    }
    cout << getSeleepiestGuard( sorted_schedule ) << endl;

    return EXIT_SUCCESS; 
}

pair<string, vector<string> > getEntryDetails( string& input ) {
    string entry_key, tmp;
    vector<string> details;
    int count = 0;
    istringstream iss;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] == '[' || input[i] == ']' || input[i] == '-' ||
            input[i] == ':' || input[i] == '#' ) {
            input[i] = ' ';
        } 
    }
    iss.str( input );
    while( count++ < 5 ) {
        iss >> tmp;
        entry_key += tmp;
        details.push_back( tmp );
    }
    while( iss >> tmp ) {
        details.push_back( tmp );
    }
    return make_pair( entry_key, details );
}

/* Input Format */
/*
0    1  2  3  4  5     6
-----------------------------------------
1518 11 18 00 00 Guard #2411 begins shift 
1518 11 18 00 31 falls asleep 
1518 11 18 00 45 wakes up 
*/

int getSeleepiestGuard( const map<string, vector<string> >& sorted_schedule ) {
    unordered_map<int, vector<int> > sleeping_minutes;
    map<string, vector<string> >::const_iterator it;
    int chosen_guard_id, chosen_guard_min;
    int curr_guard_id, sleep_time, wake_time;
    int tmp_sleep_min, max_sleep;
    tmp_sleep_min = max_sleep = -1;
    for( it = sorted_schedule.begin(); it != sorted_schedule.end(); ++it ) {
        if( it->second[5] == "Guard" )
            curr_guard_id = stoi( it->second[6] ); 
        else if( it->second[5] == "falls" )
            sleep_time = stoi( it->second[4] );
        else { //it->second[5] = "wakes"
            if( sleeping_minutes.find( curr_guard_id ) == sleeping_minutes.end() ) {
                sleeping_minutes[curr_guard_id] = vector<int>( 60, 0 );
            }
            wake_time =  stoi( it->second[4] );
            tmp_sleep_min = addMinutes( sleep_time, wake_time, sleeping_minutes[curr_guard_id] );
            if( sleeping_minutes[curr_guard_id][tmp_sleep_min] > max_sleep ) {
                chosen_guard_id = curr_guard_id;
                chosen_guard_min = tmp_sleep_min;
                max_sleep = sleeping_minutes[curr_guard_id][tmp_sleep_min];
            }
        }
    }
    return chosen_guard_min * chosen_guard_id;
}

int addMinutes( const int& start, const int& end, vector<int>& minutes ) {
    int minute, max;
    minute = max = -1;
    for( unsigned int x = start; x < end; ++x ) {
        minutes[x] += 1;
        if( minutes[x] > max ) {
            minute = x;
            max = minutes[x];
        }
    }
    return minute;
}