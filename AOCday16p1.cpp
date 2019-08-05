#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector< vector<unsigned int> > getInputSample( void );
vector<unsigned int> toIntArray( string& );
bool isValidSample( const vector< vector<unsigned int> >& );
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

int main( void ) {
    vector< vector<unsigned int> > sample;
    int validated_samples = 0;

    sample = getInputSample();
    while( sample.size() > 0 ) {
        if( isValidSample( sample ) )
            ++validated_samples;

        sample = getInputSample();
    }
    cout << validated_samples << endl;

    return EXIT_SUCCESS;
}

vector< vector<unsigned int> > getInputSample( void ) {
    vector< vector<unsigned int> > sample;
    string input;

    getline( cin, input );
    if( input.size() == 0 )
        return sample;
    sample.push_back( toIntArray( input ) );
    getline( cin, input );
    sample.push_back( toIntArray( input ) );
    getline( cin, input );
    sample.push_back( toIntArray( input ) );
    cin >> input;

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

bool isValidSample( const vector< vector<unsigned int> >& sample ) {
    int successful_ops = 0;

    if( equalResults( addr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( addi( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( mulr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( muli( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( banr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( bani( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( borr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( bori( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( setr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( seti( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( gtir( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( gtri( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( gtrr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( eqir( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( eqri( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;
    if( equalResults( eqrr( sample[0], sample[1] ), sample[2] ) )
        ++successful_ops;

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