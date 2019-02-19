#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> largestTotalPowerCoord( const int& );
int getPowerLevel( const int&, const int&, const int& );

int main( void ) {
    const int grid_sn = 1718;
    pair<int, int> result;

    result = largestTotalPowerCoord( grid_sn );
    cout << result.first << "," << result.second << endl;

    return EXIT_SUCCESS; 
}

pair<int, int> largestTotalPowerCoord( const int& grid_sn ) {
    int power_grid[300][300];
    int power_sum[300][300];
    int x, y, max, tmp;
    for( int row = 0; row < 300; ++row ) {
        for( int col = 0; col < 300; ++col ) {
            tmp = getPowerLevel( grid_sn, row, col );
            power_grid[row][col] = tmp;
            power_sum[row][col] = tmp;
            if( row > 0 )
                power_sum[row][col] += power_sum[row - 1][col];
            if( col > 0 )
                power_sum[row][col] += power_sum[row][col - 1];
            if( col > 0 && row > 0 )
                power_sum[row][col] -= power_sum[row - 1][col - 1];
        }
    }
    max = 0x80000000;
    for( int row = 2; row < 300; ++row ) {
        for( int col = 2; col < 300; ++col ) {
            tmp = power_sum[row][col];
            if( row > 2 )
                tmp -= power_sum[row - 3][col];
            if( col > 2 )
                tmp -= power_sum[row][col - 3];
            if( col > 2 && row > 2 )
                tmp += power_sum[row - 3][col - 3];
            if( tmp >= max ) {
                max = tmp;
                y = row - 2;
                x = col - 2;
            }
        }
    }
    return make_pair( x + 1, y + 1 );
}

int getPowerLevel( const int& grid_sn, const int& row, const int& col ) {
    int power_lvl;
    power_lvl = (col + 1 + 10);
    power_lvl *= (row + 1);
    power_lvl += grid_sn;
    power_lvl *= (col + 1 + 10);
    power_lvl = ((power_lvl % 1000) / 100);
    power_lvl -= 5;
    return power_lvl;
}