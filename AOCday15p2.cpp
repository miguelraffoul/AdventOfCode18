#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

struct Player {
    int play_order;
    char player_type;
    short y_position, x_position;
    short hit_points;
};

vector<string> grid;
map<int, string> player_order;
map<int, string> tmp_player_order;
unordered_map<string, struct Player> elfs;
unordered_map<string, struct Player> goblins;

void readInput( void );
string generateId( const char&, const int& );
void printGrid( void );
void printGrid( const vector<string>& );
void printPlayers( void );
int getCombatOutcome( const int& );
pair<int, string> playTurn( pair<int, string>, const int& );
char isInAttackRange( const string& );
int getPlayerRemainingHitPoints( const int& player_order );
void identifyTargets( const string& player_id, vector<string>& );
char getMoveDirection( const string& player_id, vector<string>& );
int movePlayer( const string&, const char& );
void attackEnemy( const string&, const char&, const int& );
int getTotalRemainingHitPoints( void );

int main( void ) {
    int elf_attack = 3;

    readInput();
    vector<string> bkp_grid = grid;
    map<int, string> bkp_player_order = player_order;
    unordered_map<string, struct Player> bkp_elfs = elfs;
    unordered_map<string, struct Player> bkp_goblins = goblins;

    do {
        //restore battle settings
        grid = bkp_grid;
        player_order = bkp_player_order;
        tmp_player_order.clear();
        elfs = bkp_elfs;
        goblins = bkp_goblins;

        system( "clear" );
        cout << "Elfs attack power: " << elf_attack << endl;
        cout << getCombatOutcome( elf_attack ) << endl;
        printGrid();
        this_thread::sleep_for( chrono::milliseconds( 200 ) );
        ++elf_attack;
    } while( elfs.size() < bkp_elfs.size() );

    return EXIT_SUCCESS;
}

void readInput( void ) {
    int row = 0, player_num = 0;
    string input;
    while( cin >> input ) {
        for( unsigned int i = 0; i < input.size(); ++i ) {
            if( input[i] == 'G' || input[i] == 'E' ) {
                string id = generateId( input[i], player_num );
                int order = (input.size() * row) + i;

                struct Player new_player;
                new_player.play_order = order;
                new_player.player_type = input[i];
                new_player.y_position = row;
                new_player.x_position = i;
                new_player.hit_points = 200;

                if( input[i] == 'E' )
                    elfs.insert( make_pair( id, new_player ) );
                else
                    goblins.insert( make_pair( id, new_player ) );
                player_order.insert( make_pair( order, id ) );
                ++player_num ;
            }
        }
        grid.push_back( input );
        ++row;
    }
}

string generateId( const char& type, const int& value ) {
    ostringstream oss;
    oss << type;
    oss << '-';
    oss << value;
    return oss.str();
}

void printGrid( void ) {
    for( unsigned int r = 0; r < grid.size(); ++r ) {
        cout << grid[r] << endl;
    }
    cout << endl;
}

void printGrid( const vector<string>& tmp_grid ) {
    for( unsigned int r = 0; r < tmp_grid.size(); ++r ) {
        cout << tmp_grid[r] << endl;
    }
    cout << endl;
}

void printPlayers( void ) {
    map<int, string>::iterator it;
    for( it = player_order.begin(); it != player_order.end(); ++it ) {
        cout << it->first << " - " << it->second << endl;
        if( it->second[0] == 'E' ) {
            cout << "****Elf****" << endl;
            cout << "x = " << elfs[it->second].x_position << " ";
            cout << "y = " << elfs[it->second].y_position << endl;
        }
        else {
            cout << "***Goblin***" << endl;
            cout << "x = " << goblins[it->second].x_position << " ";
            cout << "y = " << goblins[it->second].y_position << endl;
        }
        cout << endl;
    }
}

int getCombatOutcome( const int& elf_attack ) {
    int round = 0;
    while( elfs.size() > 0 && goblins.size() > 0 ) {
        while( player_order.size() > 0 ) {
            tmp_player_order.insert( playTurn( *(player_order.begin()), elf_attack ) );
            player_order.erase( player_order.begin() );
            if( elfs.size() == 0 || goblins.size() == 0 )
                break;
        }
        if( player_order.size() == 0 ) {
            player_order = tmp_player_order;
            tmp_player_order.clear();
            ++round;
        } 
    }
    cout << round << " * " << getTotalRemainingHitPoints() << " = ";
    return (round * getTotalRemainingHitPoints());
}

pair<int, string> playTurn( pair<int, string> player_details, const int& elf_attack ) {
    vector<string> tmp_grid;
    char move_direction, attack_direction;
    attack_direction = isInAttackRange( player_details.second );
    if( attack_direction == '-' ) {
        tmp_grid = grid;
        identifyTargets( player_details.second, tmp_grid );
        move_direction = getMoveDirection( player_details.second, tmp_grid );
        if( move_direction != '-' )
            player_details.first = movePlayer( player_details.second, move_direction );
    }
    attack_direction = isInAttackRange( player_details.second );
    if( attack_direction != '-' ) {
        attackEnemy( player_details.second, attack_direction, elf_attack );
    }
    return player_details;
}

char isInAttackRange( const string& player_id ) {
    struct Player p;
    int enemy_order, tmp_remaining_hp, remaining_hp = 300;
    char attack_direction = '-';
    if( player_id[0] == 'E' ) {
        p = elfs[player_id];
        if( p.y_position - 1 > 0 && grid[p.y_position - 1][p.x_position] == 'G' ) {
            enemy_order = ((p.y_position - 1) * grid[0].size()) + p.x_position;
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'U';
            }
        }
        if( p.x_position - 1 > 0 && grid[p.y_position][p.x_position - 1] == 'G' ) {
            enemy_order = (p.y_position * grid[0].size()) + (p.x_position - 1);
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'L';
            }
        }
        if( p.x_position + 1 < grid[0].size() && grid[p.y_position][p.x_position + 1] == 'G' ) {
            enemy_order = (p.y_position * grid[0].size()) + (p.x_position + 1);
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'R';
            }
        }
        if( p.y_position + 1 < grid.size() && grid[p.y_position + 1][p.x_position] == 'G' ) {
            enemy_order = ((p.y_position + 1) * grid[0].size()) + p.x_position;
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'D';
            }
        }
    }
    else {
        p = goblins[player_id];
        if( p.y_position - 1 > 0 && grid[p.y_position - 1][p.x_position] == 'E' ) {
            enemy_order = ((p.y_position - 1) * grid[0].size()) + p.x_position;
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'U';
            }
        }
        if( p.x_position - 1 > 0 && grid[p.y_position][p.x_position - 1] == 'E' ) {
            enemy_order = (p.y_position * grid[0].size()) + (p.x_position - 1);
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'L';
            }
        }
        if( p.x_position + 1 < grid[0].size() && grid[p.y_position][p.x_position + 1] == 'E' ) {
            enemy_order = (p.y_position * grid[0].size()) + (p.x_position + 1);
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'R';
            }
        }
        if( p.y_position + 1 < grid.size() && grid[p.y_position + 1][p.x_position] == 'E' ) {
            enemy_order = ((p.y_position + 1) * grid[0].size()) + p.x_position;
            tmp_remaining_hp = getPlayerRemainingHitPoints( enemy_order );
            if( tmp_remaining_hp < remaining_hp ) {
                remaining_hp = tmp_remaining_hp;
                attack_direction = 'D';
            }
        }
    }
    return attack_direction;
}

int getPlayerRemainingHitPoints( const int& p_order ) {
    string p_id;
    if( player_order.find( p_order ) != player_order.end() ) {
        p_id = player_order[p_order];
    }
    else if( tmp_player_order.find( p_order ) != tmp_player_order.end() ) {
        p_id = tmp_player_order[p_order];
    }
    if( p_id[0] == 'E' )
        return elfs[p_id].hit_points;
    else if( p_id[0] == 'G' )
        return goblins[p_id].hit_points;

    return 500;
}

void identifyTargets( const string& player_id, vector<string>& tmp_grid ) {
    unordered_map<string, struct Player>::iterator it, from_it, to_it;
    if( player_id[0] == 'E' ) {
        from_it = goblins.begin();
        to_it = goblins.end();
    }
    else {
        from_it = elfs.begin();
        to_it = elfs.end();
    }
    for( it = from_it; it != to_it; ++it ) {
        if( it->second.y_position > 0 && 
            grid[it->second.y_position - 1][it->second.x_position] == '.' )
            tmp_grid[it->second.y_position - 1][it->second.x_position] = '!';
        if( it->second.y_position < (grid.size() - 1) &&
            grid[it->second.y_position + 1][it->second.x_position] == '.' )
            tmp_grid[it->second.y_position + 1][it->second.x_position] = '!';
        if( it->second.x_position > 0 &&
            grid[it->second.y_position][it->second.x_position - 1] == '.' )
            tmp_grid[it->second.y_position][it->second.x_position - 1] = '!';
        if( it->second.x_position < (grid[0].size() - 1) &&
            grid[it->second.y_position][it->second.x_position + 1] == '.' )
            tmp_grid[it->second.y_position][it->second.x_position + 1] = '!';
    }
}

char getMoveDirection( const string& player_id, vector<string>& tmp_grid ) {
    deque< pair<int, int> > available_positions;
    deque< pair<int, int> > tmp_available_positions;
    char move_direction = '-';
    int target_order = 0x7fffffff;
    bool target_reached = false;
    int y_pos, x_pos;
    if( player_id[0] == 'E' ) {
        y_pos = elfs[player_id].y_position;
        x_pos = elfs[player_id].x_position;
    }
    else {
        y_pos = goblins[player_id].y_position;
        x_pos = goblins[player_id].x_position;
    }
    //bootstrap
    if( y_pos > 0 ) {
        if( tmp_grid[y_pos - 1][x_pos] == '!' ) 
            return 'U';
        else if( tmp_grid[y_pos - 1][x_pos] == '.' ) {
            tmp_grid[y_pos - 1][x_pos] = 'U';
            available_positions.push_back( make_pair( y_pos - 1, x_pos ) );
        }
    }
    if( x_pos > 0 ) {
        if( tmp_grid[y_pos][x_pos - 1] == '!' )
            return 'L';
        else if( tmp_grid[y_pos][x_pos - 1] == '.' ) {
            tmp_grid[y_pos][x_pos - 1] = 'L';
            available_positions.push_back( make_pair( y_pos, x_pos - 1 ) );
        }
    }
    if( x_pos < (tmp_grid[0].size() - 1) ) {
        if( tmp_grid[y_pos][x_pos + 1] == '!' )
            return 'R';
        else if( tmp_grid[y_pos][x_pos + 1] == '.' ) {
            tmp_grid[y_pos][x_pos + 1] = 'R';
            available_positions.push_back( make_pair( y_pos, x_pos + 1 ) );
        }
    }
    if( y_pos < (tmp_grid.size() - 1) ) {
        if( tmp_grid[y_pos + 1][x_pos] == '!' )
            return 'D';
        else if( tmp_grid[y_pos + 1][x_pos] == '.' ) {
            tmp_grid[y_pos + 1][x_pos] = 'D';
            available_positions.push_back( make_pair( y_pos + 1, x_pos ) );
        }
    }
    while( available_positions.size() > 0 ) {
        while( available_positions.size() > 0 ) {
            y_pos = available_positions[0].first;
            x_pos = available_positions[0].second;
            available_positions.pop_front();

            if( y_pos > 0 ) {
                if( tmp_grid[y_pos - 1][x_pos] == '!' ) {
                    if( ((y_pos - 1) * grid[0].size()) + x_pos < target_order )  {
                        move_direction = tmp_grid[y_pos][x_pos];
                        target_order = ((y_pos - 1) * grid[0].size()) + x_pos;
                        target_reached = true;
                    }
                }
                else if( tmp_grid[y_pos - 1][x_pos] == '.' ) {
                    tmp_grid[y_pos - 1][x_pos] = tmp_grid[y_pos][x_pos];
                    tmp_available_positions.push_back( make_pair( y_pos - 1, x_pos ) );
                }
            }
            if( x_pos > 0 ) {
                if( tmp_grid[y_pos][x_pos - 1] == '!' ) {
                    if( (y_pos * grid[0].size()) + (x_pos - 1) < target_order )  {
                        move_direction = tmp_grid[y_pos][x_pos];
                        target_order = (y_pos * grid[0].size()) + (x_pos - 1);
                        target_reached = true;
                    }
                }
                else if( tmp_grid[y_pos][x_pos - 1] == '.' ) {
                    tmp_grid[y_pos][x_pos - 1] = tmp_grid[y_pos][x_pos];
                    tmp_available_positions.push_back( make_pair( y_pos, x_pos - 1 ) );
                }
            }
            if( x_pos < (tmp_grid[0].size() - 1) ) {
                if( tmp_grid[y_pos][x_pos + 1] == '!' ) {
                    if( (y_pos * grid[0].size()) + (x_pos + 1) < target_order )  {
                        move_direction = tmp_grid[y_pos][x_pos];
                        target_order = (y_pos * grid[0].size()) + (x_pos + 1);
                        target_reached = true;
                    }
                }
                else if( tmp_grid[y_pos][x_pos + 1] == '.' ) {
                    tmp_grid[y_pos][x_pos + 1] = tmp_grid[y_pos][x_pos];
                    tmp_available_positions.push_back( make_pair( y_pos, x_pos + 1 ) );
                }
            }
            if( y_pos < (tmp_grid.size() - 1) ) {
                if( tmp_grid[y_pos + 1][x_pos] == '!' ) {
                    if( ((y_pos + 1) * grid[0].size()) + x_pos < target_order )  {
                        move_direction = tmp_grid[y_pos][x_pos];
                        target_order = ((y_pos + 1) * grid[0].size()) + x_pos;
                        target_reached = true;
                    }
                }
                else if( tmp_grid[y_pos + 1][x_pos] == '.' ) {
                    tmp_grid[y_pos + 1][x_pos] = tmp_grid[y_pos][x_pos];
                    tmp_available_positions.push_back( make_pair( y_pos + 1, x_pos ) );
                }
            }
        }
        if( target_reached )
            return move_direction;
        else {
            available_positions = tmp_available_positions;
            tmp_available_positions.clear();
        }
    }
    return move_direction;
}

int movePlayer( const string& player_id, const char& move_dir ) {
    int y_change, x_change, new_order;
    y_change = x_change = 0;
    switch( move_dir ) {
        case 'U':
            y_change = -1;
            break;
        case 'L':
            x_change = -1;
            break;
        case 'R':
            x_change = 1;
            break;
        case 'D':
            y_change = 1;
            break;
    }
    if( player_id[0] == 'E' ) {
        grid[elfs[player_id].y_position][elfs[player_id].x_position] = '.';
        elfs[player_id].y_position += y_change;
        elfs[player_id].x_position += x_change;
        grid[elfs[player_id].y_position][elfs[player_id].x_position] = 'E';

        new_order = (elfs[player_id].y_position * grid[0].size()) + elfs[player_id].x_position;
        elfs[player_id].play_order = new_order;
    }
    else {
        grid[goblins[player_id].y_position][goblins[player_id].x_position] = '.';
        goblins[player_id].y_position += y_change;
        goblins[player_id].x_position += x_change;
        grid[goblins[player_id].y_position][goblins[player_id].x_position] = 'G';

        new_order = (goblins[player_id].y_position * grid[0].size()) + goblins[player_id].x_position;
        goblins[player_id].play_order = new_order;
    }
    return new_order;
}

void attackEnemy( const string& player_id, const char& attack_direction, const int& elf_attack ) {
    int y_pos, x_pos, enemy_order;
    string enemy_id;
    if( player_id[0] == 'E' ) {
        y_pos = elfs[player_id].y_position;
        x_pos = elfs[player_id].x_position;
    }
    else {
        y_pos = goblins[player_id].y_position;
        x_pos = goblins[player_id].x_position;
    }
    
    switch( attack_direction ) {
        case 'U':
            enemy_order = ((y_pos - 1) * grid[0].size()) + x_pos;
            break;
        case 'L':
            enemy_order = (y_pos * grid[0].size()) + (x_pos - 1);
            break;
        case 'R':
            enemy_order = (y_pos * grid[0].size()) + (x_pos + 1);
            break;
        case 'D':
            enemy_order = ((y_pos + 1) * grid[0].size()) + x_pos;
            break;
    }
    if( player_order.find( enemy_order ) != player_order.end() )
        enemy_id = player_order[enemy_order];
    else if( tmp_player_order.find( enemy_order ) != tmp_player_order.end() )
        enemy_id = tmp_player_order[enemy_order];
    
    if( enemy_id[0] == 'E' ) {
        elfs[enemy_id].hit_points -= 3;
        if( elfs[enemy_id].hit_points <= 0 ) {
            grid[elfs[enemy_id].y_position][elfs[enemy_id].x_position] = '.';
            elfs.erase( enemy_id );
            player_order.erase( enemy_order );
            tmp_player_order.erase( enemy_order );
        }
    }
    else {
        goblins[enemy_id].hit_points -= elf_attack;
        if( goblins[enemy_id].hit_points <= 0 ) {
            grid[goblins[enemy_id].y_position][goblins[enemy_id].x_position] = '.';
            goblins.erase( enemy_id );
            player_order.erase( enemy_order );
            tmp_player_order.erase( enemy_order );
        }
    }
}

int getTotalRemainingHitPoints( void ) {
    int hit_points_sum = 0;
    unordered_map<string, struct Player>::iterator it;
    for( it = elfs.begin(); it != elfs.end(); ++it )
        hit_points_sum += it->second.hit_points;
    for( it = goblins.begin(); it != goblins.end(); ++it )
        hit_points_sum += it->second.hit_points;
    return hit_points_sum;
}