/*
    CSCI 373 - Project
    By Dennis Leung
    December 2, 2015
    Priority Queuing Player's Career Stats
*/

#include <iostream>     // For I/O
#include <string>       // For string
#include <fstream>      // For inputing csv files
#include <sstream>      // For converting string to double or int
#include <vector>       // For containing arrays in sequence
#include <queue>        // For priority queue
#include <iomanip>      // For formatting output for table

using namespace std;

// Declaration of constant variables
const char separator = ' ';
const int nameWidth  = 25;
const int numWidth   = 10;

// Player class/structure
class Player
{
    public:
        string  playerName;
        double  statPoints;
        double  statAssists;
        double  statRebounds;
};

// Comparison of Points to display
// from highest to lowest
struct topPoints
{
    bool operator( )( const Player& a, const Player& b )
    {
        return a.statPoints < b.statPoints;
    }
};

// Comparison of Assists to display
// from highest to lowest
struct topAssists
{
    bool operator( )( const Player&a, const Player& b )
    {
        return a.statAssists < b.statAssists;
    }
};

// Comparison of Rebounds to display
// from highest to lowest
struct topRebounds
{
    bool operator( )( const Player& a, const Player& b )
    {
        return a.statRebounds < b.statRebounds;
    }
};

// Function to format line inside the table
template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw( width ) << setfill( separator ) << t;
}

int main( int argc, char *argv[])
{
    // Opening command line input Team File and
    // checking to see if the file is opened or not
    ifstream team ( argv[1] );
    if ( team.is_open( ) )
        ;
    else
    {
        cout << "Error loading file." << endl;
        cout << "Format: ./Top <team.csv>" << endl;
        // Stops program from continuing if file is not
        // loaded correctly
        return 0;
    }

    // Various variables
    string  line;
    int     numline;
    int     counter = 0;

    // Initialize vectors for each column
    vector< string >    name;
    vector< double >    points;
    vector< double >    assists;
    vector< double >    rebounds;

    // Run through every row of the file
    // to gather information
    while( getline( team, line ) )
    {
        stringstream info( line );

        getline( info, line, ',' );
        name.push_back( line );

        getline( info, line, ',' );
        istringstream( line ) >> numline;
        points.push_back( numline );

        getline( info, line, ',' );
        istringstream( line ) >> numline;
        assists.push_back( numline );

        getline( info, line, ',' );
        istringstream( line ) >> numline;
        rebounds.push_back( numline );

        // Counts the rows in the file
        counter++;
    }

    // Closes the file
    team.close();

    // Establish how many 'Player' structs
    // to be made
    Player P[ counter ];

    // Passing through the vector information
    // into the Player structs
    for( int i = 0; i < counter; i++ )
    {
        P[ i ].playerName   = name[ i ];
        P[ i ].statPoints   = points[ i ];
        P[ i ].statAssists  = assists[ i ];
        P[ i ].statRebounds = rebounds[ i ];
    }

    // Asking user for which stat to list from highest
    // to lowest
    char input;
    int  choice;
    cout << "Please choose between the three stats:" << endl;
    cout << "P for Points | A for Assists | R for Rebounds" << endl;
    cin >> input;

    // Header for table
    printElement( "Player", nameWidth );
    printElement( "Points", numWidth );
    printElement( "Assists", numWidth );
    printElement( "Rebounds", numWidth );
    cout << endl;
    cout << "======================================================" << endl;

    // If-Else Statements to display highest career points, assists,
    // and/or rebounds within their respective teams
    if ( input == 'P' || input == 'p' )
    {
        priority_queue< Player, vector< Player >, topPoints > pq;

        for( int i = 0; i < counter; i++ )
            pq.push( P[ i ] );

        for( int x = 0; x < counter; x++ )
        {
            Player PP = pq.top();
            printElement( PP.playerName, nameWidth );
            printElement( PP.statPoints, numWidth );
            printElement( PP.statAssists, numWidth );
            printElement( PP.statRebounds, numWidth );
            cout << endl;
            pq.pop();
        }
    }
    else if ( input == 'A' || input == 'a' )
    {
        priority_queue< Player, vector< Player >, topAssists > pq;

        for( int i = 0; i < counter; i++ )
            pq.push( P[ i ] );

        for( int x = 0; x < counter; x++ )
        {
            Player PP = pq.top();
            printElement( PP.playerName, nameWidth );
            printElement( PP.statPoints, numWidth );
            printElement( PP.statAssists, numWidth );
            printElement( PP.statRebounds, numWidth );
            cout << endl;
            pq.pop();
        }
    }
    else if ( input == 'R' || input == 'r' )
    {
        priority_queue< Player, vector< Player >, topRebounds > pq;

        for( int i = 0; i < counter; i++ )
            pq.push( P[ i ] );

        for( int x = 0; x < counter; x++ )
        {
            Player PP = pq.top();
            printElement( PP.playerName, nameWidth );
            printElement( PP.statPoints, numWidth );
            printElement( PP.statAssists, numWidth );
            printElement( PP.statRebounds, numWidth );
            cout << endl;
            pq.pop();
        }
    }
    /////////////////////////////////////////////////////////////////////

    return 0;
}
