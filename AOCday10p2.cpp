#include <cstdlib>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

vector<int> getPointDetails( string& );
bool updatePositions( vector< pair<int, int> >&, const vector< pair<int, int> >& );
void printPoints( const vector< pair<int, int> >&, const int, const int, const int, const int);

int main( void ) {
    vector< pair<int, int> > positions;
    vector< pair<int, int> > speeds;
    int iterations = 20000;
    string input;
    
    
    while( getline( cin, input ) ) {
        vector<int> tmp = getPointDetails( input );
        positions.push_back( make_pair( tmp[0], tmp[1] ) );
        speeds.push_back( make_pair( tmp[2], tmp[3] ) );
    }
    for( int it = 1; it <= iterations; ++it ) {
        if( updatePositions( positions, speeds ) )
            cout << "Iteration/Second: " << it << endl;
    }

    return EXIT_SUCCESS; 
}

vector<int> getPointDetails( string& input ) {
    istringstream iss;
    vector<int> point;
    int tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] < '0' || input[i] > '9' ){
            if ( input[i] != '-' )
                input[i] = ' ';
        }
    }
    iss.str( input );
    while( iss >> tmp ) {
        point.push_back( tmp );
    }
    return point;
}

bool updatePositions( vector< pair<int, int> >& positions, const vector< pair<int, int> >& speeds ) {
    int low_y, high_y, low_x, high_x;
    low_y = low_x = 0x7fffffff;
    high_y = high_x = 0x80000000;

    for( unsigned int p = 0; p < positions.size(); ++p ) {
        positions[p].first += speeds[p].first;
        positions[p].second += speeds[p].second;
        low_x = positions[p].first < low_x ? positions[p].first : low_x;
        high_x = positions[p].first > high_x ? positions[p].first : high_x;
        low_y = positions[p].second < low_y ? positions[p].second : low_y;
        high_y = positions[p].second > high_y ? positions[p].second : high_y;
    }
    //cout << (high_y - low_y + 1) << endl;
    if( high_y - low_y <= 12 ) {
        printPoints( positions, (high_y - low_y + 1), (high_x - low_x + 1), low_y, low_x );
        return true;
    }
    return false;
}

void printPoints( const vector< pair<int, int> >& positions, 
                  const int rows, const int cols,
                  const int low_y, const int low_x ) {
    vector<string> grid( rows, string( cols, '.' ) );
    system( "clear" );
    for( unsigned int p = 0; p < positions.size(); ++p ) {
        grid[positions[p].second - low_y][positions[p].first - low_x] = '#';
    }
    for( unsigned int r = 0; r < grid.size(); ++r ) {
        for( unsigned int c = 0; c < grid[r].size(); ++c ) {
            cout << grid[r][c];
        }
        cout<< endl;
    }
    this_thread::sleep_for( chrono::milliseconds( 250 ) );
}


/*
......................
......................
......#...#..###......
......#...#...#.......
......#...#...#.......
......#####...#.......
......#...#...#.......
......#...#...#.......
......#...#...#.......
......#...#..###......
......................
......................
*/