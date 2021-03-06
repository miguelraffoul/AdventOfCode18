#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> getRectDetails( string& );
int getOverlapCount( const vector< vector<int> >& );
string coordsToString( const int&, const int& );

int main( void ) {
    vector< vector<int> > rectangles;
    string input;

    while( getline( cin, input ) ) {
        rectangles.push_back( getRectDetails( input ) );
    }
    cout << getOverlapCount( rectangles ) << endl;
    
    return EXIT_SUCCESS; 
}

vector<int> getRectDetails( string& input ) {
    vector<int> rectangle;
    istringstream iss;
    int tmp;
    for( unsigned int i = 0; i < input.size(); ++i ) {
        if( input[i] < '0' || input[i] > '9' )
            input[i] = ' ';
    }
    iss.str( input );
    while( iss >> tmp ) {
        rectangle.push_back( tmp );
    }
    return rectangle;
}

int getOverlapCount( const vector< vector<int> >& rectangles ) {
    unordered_set<string> claimed_coords;
    unordered_set<string> overlaped_coords;
    string tmp_coords;
    for( unsigned int r = 0; r < rectangles.size(); ++r ) {
        for( int row = rectangles[r][2]; row < (rectangles[r][2] + rectangles[r][4]); ++row ) {
            for( int col = rectangles[r][1]; col < (rectangles[r][1] + rectangles[r][3]); ++col ) {
                tmp_coords = coordsToString( row, col );
                if( claimed_coords.insert( tmp_coords ).second == false )
                    overlaped_coords.insert( tmp_coords );
            }
        }
    }
    return overlaped_coords.size();
}

string coordsToString( const int& row, const int& col ) {
    ostringstream oss;
    oss << row;
    oss << ',';
    oss << col;
    return oss.str();
}