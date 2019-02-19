#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Kart {
    private:
    int row_pos;
    int col_pos;
    int abs_pos;
    int option;
    char direction;

    void turnLeft( void );
    void turnRight( void );
    void moveKart( const unsigned int& );

    public:
    Kart( const int&, const int&, const int&, const char& );
    void updatePosition( const vector<string>& );
    int getAbsPosition( void ) const;
    pair<int, int> getPosition( void );
    bool operator < ( const Kart& ) const;
};

vector<Kart> readTunnelGrid( vector<string>& );
pair<int, int> getFirstCrashPos( const vector<string>&, vector<Kart>& );

int main( void ) {
    vector<string> tunnel_grid;
    vector<Kart> karts;
    pair<int, int> crash_pos;

    karts = readTunnelGrid( tunnel_grid );
    crash_pos = getFirstCrashPos( tunnel_grid, karts );
    cout << crash_pos.second << "," << crash_pos.first << endl;

    return EXIT_SUCCESS; 
}

Kart::Kart( const int& row, const int& col, const int& pos, const char& dir ):
    row_pos( row ),
    col_pos( col ),
    abs_pos( pos ),
    option( 0 ),
    direction( dir )
{
}

void Kart::turnLeft( void ) {
    if( direction == '>' ) {
        direction = '^';
    }
    else if( direction == '<' ) {
        direction = 'v';
    }
    else if( direction == '^' ) {
        direction = '<';
    }
    else {
        direction = '>';
    }
}

void Kart::turnRight( void ) {
    if( direction == '>' ) {
        direction = 'v';
    }
    else if( direction == '<' ) {
        direction = '^';
    }
    else if( direction == '^' ) {
        direction = '>';
    }
    else {
        direction = '<';
    }
}

void Kart::moveKart( const unsigned int& row_size ) {
    if( direction == '>' ) {
        col_pos += 1;
    }
    else if( direction == '<' ) {
        col_pos -= 1;
    }
    else if( direction == '^' ) {
        row_pos -= 1;
    }
    else {
        row_pos += 1;
    }
    abs_pos = (row_size * row_pos) + col_pos;
}

void Kart::updatePosition( const vector<string>& tunnel_grid ) {
    if( tunnel_grid[row_pos][col_pos] == '+' ) {
        if( option == 0 ) {
            turnLeft();
        }
        if( option == 2 ) {
            turnRight();
        }
        ++option;
        if( option == 3 )
            option = 0;
    }
    if( tunnel_grid[row_pos][col_pos] == '\\' ) {
        if( direction == '>' ) {
            turnRight();
        }
        else if( direction == '<' ) {
            turnRight();
        }
        else if( direction == '^' ) {
            turnLeft();
        }
        else {
            turnLeft();
        }
    }
    if( tunnel_grid[row_pos][col_pos] == '/'  ) {
        if( direction == '>' ) {
            turnLeft();
        }
        else if( direction == '<' ) {
            turnLeft();
        }
        else if( direction == '^' ) {
            turnRight();
        }
        else {
            turnRight();   
        }
    }
    moveKart( tunnel_grid[0].size() );
}

pair<int, int> Kart::getPosition( void ) {
    return make_pair( row_pos, col_pos );
}

int Kart::getAbsPosition( void ) const {
    return abs_pos;
}

bool Kart::operator < ( const Kart& k ) const {
    return abs_pos < k.getAbsPosition();
}

vector<Kart> readTunnelGrid( vector<string>& tunnel_grid ) {
    vector<Kart> karts;
    string input;
    int r = 0;
    while( getline( cin, input ) ) {
        string line;
        for( unsigned int c = 0; c < input.size(); ++c ) {
            if( input[c] == '<' || input[c] == '>' ||
                input[c] == '^' || input[c] == 'v' ) {
                int p = (r * input.size()) + c;
                Kart new_kart( r, c, p, input[c] );
                karts.push_back( new_kart );
                if( input[c] == '<' || input[c] == '>' )
                    line += '-';
                else
                    line += '|';
            }
            else
                line += input[c];
        }
        tunnel_grid.push_back( line );
        ++r;
    }
    return karts;
}

pair<int, int> getFirstCrashPos( const vector<string>& tunnel_grid, vector<Kart>& karts ) {
    map<int, int> sorted_karts;
    for( unsigned int k = 0; k < karts.size(); ++k ) {
        sorted_karts.insert( make_pair( karts[k].getAbsPosition(), k ) );
    }
    while( sorted_karts.size() > 1 ) {
        map<int, int> tmp_sort;
        while( sorted_karts.size() > 0 ) {
            int k = sorted_karts.begin()->second;
            sorted_karts.erase( sorted_karts.begin() );
            karts[k].updatePosition( tunnel_grid );
            if( sorted_karts.find( karts[k].getAbsPosition() ) != sorted_karts.end() ) {
                sorted_karts.erase( karts[k].getAbsPosition() );
            }
            else if( tmp_sort.find( karts[k].getAbsPosition() ) != tmp_sort.end() ) {
                tmp_sort.erase( karts[k].getAbsPosition() );
            } 
            else {
                tmp_sort.insert( make_pair( karts[k].getAbsPosition(), k ) );
            }
        }
        sorted_karts.insert( tmp_sort.begin(), tmp_sort.end() );
    }
    return karts[sorted_karts.begin()->second].getPosition();
}