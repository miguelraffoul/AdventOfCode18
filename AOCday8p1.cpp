#include <cstdlib>
#include <iostream>

using namespace std;

int getMetadataSum( void );

int main( void ) {
    cout << getMetadataSum() << endl;

    return EXIT_SUCCESS; 
}

int getMetadataSum( void ) {
    int children, metadata, sum, tmp;
    cin >> children >> metadata;
    sum = 0;
    while( children-- ) {
        sum += getMetadataSum();
    }
    while( metadata-- ) {
        cin >> tmp;
        sum += tmp;
    }
    return sum;
}