#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int getNodeValue( void );

int main( void ) {
    cout << getNodeValue() << endl;

    return EXIT_SUCCESS; 
}

int getNodeValue( void ) {
    int children, metadata, tmp, value;
    vector<int> children_values;
    cin >> children >> metadata;
    for( int c = 0; c < children; ++c ) {
        children_values.push_back( getNodeValue() );
    }
    value = 0;
    while( metadata-- ) {
        cin >> tmp;
        if( children ) {
            if ( tmp <= children_values.size() )
                value += children_values[tmp - 1];
        }
        else 
            value += tmp;
    }
    return value;
}