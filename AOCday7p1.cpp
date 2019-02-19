#include <cstdlib>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Instruction {
    bool is_completed;
    vector<string> dependencies;
    vector<string> dependents;
};

vector<string> buildInstructionSet( unordered_map<string, struct Instruction>& );
string processInstructionSet( unordered_map<string, struct Instruction>&, const vector<string>& );
bool readyToProcess( unordered_map<string, struct Instruction>&, const string& );

int main( void ) {
    unordered_map<string, struct Instruction> inst_set;
    vector<string> start_inst;
        
    start_inst = buildInstructionSet( inst_set );
    cout << processInstructionSet( inst_set, start_inst ) << endl;

    return EXIT_SUCCESS; 
}


//0    1 2    3  4        5      6    7 8   9
//Step I must be finished before step G can begin.

vector<string> buildInstructionSet( unordered_map<string, struct Instruction>& inst_set ) {
    vector<string> start_inst;
    string input;
    while( getline( cin, input ) ) {
        istringstream iss( input );
        vector<string> inst_pieces;
        string tmp;
        while( iss >> tmp ) {
            inst_pieces.push_back( tmp );
        }
        //add dependents I -> G
        if( inst_set.find( inst_pieces[1] ) == inst_set.end() ) {
            struct Instruction new_inst;
            new_inst.is_completed = false;
            new_inst.dependents.push_back( inst_pieces[7] );
            inst_set[inst_pieces[1]] = new_inst;
        }
        else {
            inst_set[inst_pieces[1]].dependents.push_back( inst_pieces[7] );     
        }
        //add dependencies G -> I
        if( inst_set.find( inst_pieces[7] ) == inst_set.end() ) {
            struct Instruction new_inst;
            new_inst.is_completed = false;
            new_inst.dependencies.push_back( inst_pieces[1] );
            inst_set[inst_pieces[7]] = new_inst;
        }
        else {
            inst_set[inst_pieces[7]].dependencies.push_back( inst_pieces[1] );     
        }
    }
    unordered_map<string, struct Instruction>::iterator it;
    for( it = inst_set.begin(); it != inst_set.end(); ++it ) {
        if( it->second.dependencies.size() == 0 )
            start_inst.push_back( it->first );
    }
    return start_inst;
}

string processInstructionSet( unordered_map<string, struct Instruction>& inst_set, const vector<string>& start ) {
    priority_queue<string, vector<string>, greater<string> > inst_queue( start.begin(), start.end() );
    string inst_order, curr_inst, tmp_inst;
    while( inst_queue.size() > 0 ) {
        curr_inst = inst_queue.top();
        inst_queue.pop();
        inst_set[curr_inst].is_completed = true;
        for( unsigned int i = 0; i < inst_set[curr_inst].dependents.size(); ++i ) {
            tmp_inst = inst_set[curr_inst].dependents[i];
            if( readyToProcess( inst_set, tmp_inst ) ){
                inst_queue.push( tmp_inst );
            }
        }
        inst_order += curr_inst;
    }
    return inst_order;
}

bool readyToProcess( unordered_map<string, struct Instruction>& inst_set, const string& inst ) {
    string tmp_inst;
    for( unsigned int i = 0; i < inst_set[inst].dependencies.size(); ++i ) {
        tmp_inst = inst_set[inst].dependencies[i];
        if( !inst_set[tmp_inst].is_completed )
            return false;
    }
    return true;
}