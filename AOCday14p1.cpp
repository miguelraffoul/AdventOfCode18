#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string getScoresAfter( const int, vector<int>& );

int main( void ) {
    vector<int> recipes;
    recipes.push_back( 3 );
    recipes.push_back( 7 );

    cout << getScoresAfter( 890691, recipes ) << endl;

    return EXIT_SUCCESS; 
}

string getScoresAfter( const int target, vector<int>& recipes ) {
    string result;
    int elf1_idx = 0;
    int elf2_idx = 1;
    while( recipes.size() < (target + 10) ) {
        int recipe_sum = recipes[elf1_idx] + recipes[elf2_idx];
        if( recipe_sum >= 10 )
            recipes.push_back( 1 );
        recipes.push_back( recipe_sum % 10 );
        
        if( elf1_idx + recipes[elf1_idx] + 1 >= recipes.size() )
            elf1_idx = ((recipes[elf1_idx] + 1) - (recipes.size() - elf1_idx)) % recipes.size();
        else
            elf1_idx += recipes[elf1_idx] + 1;
        
        if( elf2_idx + recipes[elf2_idx] + 1 >= recipes.size() )
            elf2_idx = ((recipes[elf2_idx] + 1) - (recipes.size() - elf2_idx)) % recipes.size();
        else
            elf2_idx += recipes[elf2_idx] + 1;
    }
    for( int i = target; i < (target + 10); ++i ) {
        result += ('0' + recipes[i]);
    }
    return result;
}