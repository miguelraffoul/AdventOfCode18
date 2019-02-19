#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

pair<pair<int, int>, int> largestTotalPowerCoord( const int& );
int getPowerLevel( const int&, const int&, const int& );

int main( void ) {
    const int grid_sn = 1718;
    pair<pair<int, int>, int> result;

    result = largestTotalPowerCoord( grid_sn );
    cout << result.first.first << "," << result.first.second << "," << result.second << endl;

    return EXIT_SUCCESS; 
}

pair<pair<int, int>, int> largestTotalPowerCoord( const int& grid_sn ) {
    int power_grid[300][300];
    int power_sum[300][300];
    int x, y, size, max, tmp;
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
    for( int row = 0; row < 300; ++row ) {
        for( int col = 0; col < 300; ++col ) {
            for( int s = 0; row + s < 300 && col + s < 300; ++s ) {
                tmp = power_sum[row + s][col + s];
                if( row > 0 )
                    tmp -= power_sum[row - 1][col + s];
                if( col > 0 )
                    tmp -= power_sum[row + s][col - 1];
                if( col > 0 && row > 0 )
                    tmp += power_sum[row - 1][col - 1];
                if( tmp >= max ) {
                    max = tmp;
                    y = row;
                    x = col;
                    size = s;
                }
            }
        }
    }
    return make_pair( make_pair( x + 1, y + 1 ), size + 1 );
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