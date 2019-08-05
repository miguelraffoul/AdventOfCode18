#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getRecipesBefore( const string&, vector<int>& );
void printRecipes( const vector<int>& );

int main( void ) {
    string input;
    vector<int> recipes;
    recipes.push_back( 3 );
    recipes.push_back( 7 );

    cin >> input;
    cout << getRecipesBefore( input, recipes ) << endl;

    return EXIT_SUCCESS; 
}

int getRecipesBefore( const string& target, vector<int>& recipes ) {
    int elf1_idx = 0;
    int elf2_idx = 1;
    int target_size = target.size();
    string tmp;
    while( true ) {
        int recipe_sum = recipes[elf1_idx] + recipes[elf2_idx];
        if( recipe_sum >= 10 ) {
            recipes.push_back( 1 );
            tmp.push_back( '1' );
            if( tmp.size() > target_size )
                tmp.erase( tmp.begin() );
            if( tmp == target )
                return (recipes.size() - target_size);
        }
        recipes.push_back( recipe_sum % 10 );
        tmp.push_back( (char)('0' + (recipe_sum % 10)) );
        if( tmp.size() > target_size )
            tmp.erase( tmp.begin() );
        if( tmp == target )
            return (recipes.size() - target_size);
        
        if( elf1_idx + recipes[elf1_idx] + 1 >= recipes.size() )
            elf1_idx = ((recipes[elf1_idx] + 1) - (recipes.size() - elf1_idx)) % recipes.size();
        else
            elf1_idx += recipes[elf1_idx] + 1;
        
        if( elf2_idx + recipes[elf2_idx] + 1 >= recipes.size() )
            elf2_idx = ((recipes[elf2_idx] + 1) - (recipes.size() - elf2_idx)) % recipes.size();
        else
            elf2_idx += recipes[elf2_idx] + 1;
    }
    return -1;
}