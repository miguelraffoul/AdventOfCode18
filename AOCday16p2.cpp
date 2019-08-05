#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void generateMappings( unordered_map< int, unordered_set<string> >& );
vector< vector<unsigned int> > getInputSample( ifstream& );
vector<unsigned int> toIntArray( string& );
bool isValidSample( const vector< vector<unsigned int> >&, unordered_map< int, unordered_set<string> >& );
bool equalResults( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> addr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> addi( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> mulr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> muli( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> banr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> bani( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> borr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> bori( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> setr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> seti( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> gtir( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> gtri( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> gtrr( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> eqir( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> eqri( const vector<unsigned int>&, const vector<unsigned int>& );
vector<unsigned int> eqrr( const vector<unsigned int>&, const vector<unsigned int>& );
void printMappings( unordered_map< int, unordered_set<string> >& );
void refineMappings( unordered_map< int, unordered_set<string> >& );
void executeOperations( unordered_map< int, unordered_set<string> >& );

int main( void ) {
    unordered_map< int, unordered_set<string> > mappings;

    generateMappings( mappings );
    executeOperations( mappings );

    return EXIT_SUCCESS;
}

void generateMappings( unordered_map< int, unordered_set<string> >& mappings ) {
    vector< vector<unsigned int> > sample;
    int validated_samples = 0;
    ifstream sample_file;

    sample_file.open( "inputAOC16_p1", ifstream::in );
    sample = getInputSample( sample_file );
    while( sample.size() > 0 ) {
        if( isValidSample( sample, mappings ) )
            ++validated_samples;

        sample = getInputSample( sample_file );
    }
    sample_file.close();
    //cout << validated_samples << endl;
    //printMappings( mappings );
    refineMappings( mappings );
    //printMappings( mappings );
}

vector< vector<unsigned int> > getInputSample( ifstream& sample_file ) {
    vector< vector<unsigned int> > sample;
    string input;

    getline( sample_file, input );
    if( input.size() == 0 )
        return sample;
    sample.push_back( toIntArray( input ) );
    getline( sample_file, input );
    sample.push_back( toIntArray( input ) );
    getline( sample_file, input );
    sample.push_back( toIntArray( input ) );
    sample_file >> input;

    return sample;
}

vector<unsigned int> toIntArray( string& input ) {
    vector<unsigned int> array;
    istringstream iss;
    unsigned int tmp;

    for( unsigned int c = 0; c < input.size(); ++c ) {
        if( input[c] < '0' || input[c] > '9' )
            input[c] = ' ';
    }
    iss.str( input );
    while( iss >> tmp ) {
        array.push_back( tmp );   
    }

    return array;
}

bool isValidSample( const vector< vector<unsigned int> >& sample, unordered_map< int, unordered_set<string> >& mappings ) {
    int successful_ops = 0;

    if( equalResults( addr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "addr" );
    }
    if( equalResults( addi( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "addi" );
    }
    if( equalResults( mulr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "mulr" );
    }
    if( equalResults( muli( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "muli" );
    }
    if( equalResults( banr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "banr" );
    }
    if( equalResults( bani( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "bani" );
    }
    if( equalResults( borr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "borr" );
    }
    if( equalResults( bori( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "bori" );
    }
    if( equalResults( setr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "setr" );
    }
    if( equalResults( seti( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "seti" );
    }
    if( equalResults( gtir( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "gtir" );
    }
    if( equalResults( gtri( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "gtri" );
    }
    if( equalResults( gtrr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "gtrr" );
    }
    if( equalResults( eqir( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "eqir" );
    }
    if( equalResults( eqri( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "eqri" );
    }
    if( equalResults( eqrr( sample[0], sample[1] ), sample[2] ) ) {
        ++successful_ops;
        mappings[sample[1][0]].insert( "eqrr" );
    }

    return successful_ops >= 3;
}

bool equalResults( const vector<unsigned int>& result, const vector<unsigned int>& expected ) {
    for( unsigned int i = 0; i < result.size(); ++i ) {
        if( result[i] != expected[i] )
            return false;
    }
    return true;
}

vector<unsigned int> addr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] + regs[op_code[2]];
    return result;
}

vector<unsigned int> addi( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] + op_code[2];
    return result;
}

vector<unsigned int> mulr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] * regs[op_code[2]];
    return result;
}

vector<unsigned int> muli( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] * op_code[2];
    return result;
}

vector<unsigned int> banr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] & regs[op_code[2]];
    return result;
}

vector<unsigned int> bani( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] & op_code[2];
    return result;
}

vector<unsigned int> borr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] | regs[op_code[2]];
    return result;
}

vector<unsigned int> bori( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] | op_code[2];
    return result;
}

vector<unsigned int> setr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]];
    return result;
}

vector<unsigned int> seti( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = op_code[1];
    return result;
}

vector<unsigned int> gtir( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = op_code[1] > regs[op_code[2]] ? 1 : 0;
    return result;
}

vector<unsigned int> gtri( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] > op_code[2] ? 1 : 0;
    return result;
}

vector<unsigned int> gtrr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] > regs[op_code[2]] ? 1 : 0;
    return result;
}

vector<unsigned int> eqir( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = op_code[1] == regs[op_code[2]] ? 1 : 0;
    return result;
}

vector<unsigned int> eqri( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] == op_code[2] ? 1 : 0;
    return result;
}

vector<unsigned int> eqrr( const vector<unsigned int>& regs, const vector<unsigned int>& op_code ) {
    vector<unsigned int> result = regs;
    result[op_code[3]] = regs[op_code[1]] == regs[op_code[2]] ? 1 : 0;
    return result;
}

void printMappings( unordered_map< int, unordered_set<string> >& mappings ) {
    unordered_map< int, unordered_set<string> >::iterator op_code;
    unordered_set< string >::iterator op_string;
    for( op_code = mappings.begin(); op_code != mappings.end(); ++op_code ) {
        cout << op_code->first << ": ";
        for( op_string = op_code->second.begin(); op_string != op_code->second.end(); ++op_string ) {
            cout << *op_string << ", ";
        }
        cout << endl;
    }
}

void refineMappings( unordered_map< int, unordered_set<string> >& mappings ) {
    unordered_map< int, unordered_set<string> >::iterator it, current, next;
    bool continue_flag = true;
    int erased;
    //bootstrap
    for( it = mappings.begin(); it != mappings.end(); ++it ) {
        if( it->second.size() == 1 ) {
            current = next = it;       
            break;
        }
    }
    while( continue_flag ) {
        continue_flag = false;
        for( it = mappings.begin(); it != mappings.end(); ++it ) {
            if( it != current ) {
                erased = it->second.erase( *(current->second.begin()) );
                if( erased > 0 && it->second.size() == 1 ) {
                    next = it;
                    continue_flag = true;
                }
            }
        }
        current = next;
    }
}

void executeOperations( unordered_map< int, unordered_set<string> >& mappings ) {
    vector<unsigned int> registers( 4, 0 );
    vector<unsigned int> op_code;
    string input;

    ifstream operations;

    operations.open( "inputAOC16_p2", ifstream::in );
    while( getline( operations, input ) ) {
        op_code = toIntArray( input );
        if( *(mappings[op_code[0]].begin()) == "addr" ) 
            registers = addr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "addi" ) 
            registers = addi( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "mulr" ) 
            registers = mulr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "muli" ) 
            registers = muli( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "banr" ) 
            registers = banr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "bani" ) 
            registers = bani( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "borr" ) 
            registers = borr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "bori" ) 
            registers = bori( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "setr" ) 
            registers = setr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "seti" ) 
            registers = seti( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "gtir" ) 
            registers = gtir( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "gtri" ) 
            registers = gtri( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "gtrr" ) 
            registers = gtrr( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "eqir" ) 
            registers = eqir( registers, op_code );
        else if( *(mappings[op_code[0]].begin()) == "eqri" ) 
            registers = eqri( registers, op_code );
        else //( *(mappings[op_code[0]].begin()) == "eqrr" ) 
            registers = eqrr( registers, op_code );
    }
    operations.close();
    cout << registers[0] << " " << registers[3] << " " << registers[2] << " " << registers[3] << endl;
}