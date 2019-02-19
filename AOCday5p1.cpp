#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int fullyReactPolymer( string& );
bool sameTypeDiffPolarity( const char&, const char& );
int alphaValue( const char& );

int main( void ) {
    string polymer_str;
    
    cin >> polymer_str;
    cout << fullyReactPolymer( polymer_str ) << endl;

    return EXIT_SUCCESS; 
}

int fullyReactPolymer( string&  polymer_str ) {
    int unit1, unit2;
    unit1 = 0;
    unit2 = 1;
    while( unit2 < polymer_str.size() ) {
        while( sameTypeDiffPolarity( polymer_str[unit1], polymer_str[unit2] ) ) {
            polymer_str.erase( unit1, 2 );
            if( unit1 > 0 ) {
                --unit1;
                --unit2;
            }
        }
        ++unit1;
        ++unit2;
    }
    return polymer_str.size();
}

bool sameTypeDiffPolarity( const char& unit1, const char& unit2 ) {
    if( alphaValue( unit1 ) != alphaValue( unit2 ) )
        return false;
    if( unit1 == unit2 )
        return false;
    return true;
}

int alphaValue( const char& unit ) {
    if( unit >= 'a' && unit <= 'z' )
        return (int)(unit - 'a');
    if( unit >= 'A' && unit <= 'Z' )
        return (int)(unit - 'A');
    return -1;
}