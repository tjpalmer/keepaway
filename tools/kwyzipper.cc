/**********************************
 * kwyzipper                      *
 *                                *
 * Tool to significantly compress *
 * keepaway log files.            *
 * Greg Kuhlmann 2004             *
 *                                *
 **********************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

#define MAX_EPISODES 524288
#define MAX_BUFFER 1024

using namespace std;

struct header_t 
{
  short keepers;
  short takers;
  short width;
  short length;
  int   num_episodes;
} header;

short episode[ MAX_EPISODES ];
char  buffer [ MAX_BUFFER   ];
char  outfile[ MAX_BUFFER   ];

void compress  ( char infile[] );
void decompress( char infile[] );

int main( int argc, char* argv[] )
{
  if ( argc < 3 ) {
    cerr << "Usage: " << argv[ 0 ]
	 << " [-c <kwy file>] [-x <kz file>]\n";
    return 1;
  }

  if ( !strcmp( argv[ 1 ], "-c" ) ) {
    compress( argv[ 2 ] );
  }
  else if ( !strcmp( argv[ 1 ], "-x" ) ) {
    decompress( argv[ 2 ] );
  }
  else {
    cerr << "Usage: " << argv[ 0 ]
	 << " [-c <kwy file>] [-x <kz file>]\n";
    return 1;
  }

  return 0;
}

void compress( char infile[] )
{
  char *suffix = strstr( infile, ".kwy" );
  if ( suffix == NULL ||
       strlen( suffix ) != 4 ) {
    cerr << "Expected suffix: .kwy not found in: " << infile << endl;
    exit( 1 );
  }

  ifstream fin( infile );
  if ( !fin ) {
    cerr << "Error opening input file: " << infile << endl;
    exit( 1 );
  }

  strcpy( outfile, infile );
  strcat( outfile, ".kz" );
  int fout = open( outfile, O_CREAT | O_WRONLY, 0644 );
  if ( fout == -1 ) {
    cerr << "Error opening output file: " << outfile << endl;
    exit( 1 );
  }

  header.num_episodes = 0;
  fin.getline( buffer, MAX_BUFFER );
  sscanf( buffer, "# Keepers: %d", &(header.keepers) );
  fin.getline( buffer, MAX_BUFFER );
  sscanf( buffer, "# Takers:  %d", &(header.takers) );
  fin.getline( buffer, MAX_BUFFER );
  sscanf( buffer, "# Region:  %d x %d", &(header.width), &(header.length) );
  for ( int i = 0; i < 8; i++ )
    fin.getline( buffer, MAX_BUFFER );

  int  iVal;
  char cVal;
  while ( fin >> iVal ) {
    fin >> iVal >> iVal >> iVal >> cVal;
    episode[ header.num_episodes++ ] = ( cVal == 't' ) ? -iVal : iVal;
  }

  write( fout, (char *) &header, sizeof(header_t) );
  write( fout, (char *) episode, header.num_episodes * sizeof(short) );

  fin.close();
  close( fout );
}

void decompress( char infile[] )
{
  char *suffix = strstr( infile, ".kwy.kz" );
  if ( suffix == NULL ||
       strlen( suffix ) != 7 ) {
    cerr << "Expected suffix: .kwy.kz not found in: " << infile << endl;
    exit( 1 );
  }

  int fin = open( infile, O_RDONLY );
  if ( fin == -1 ) {
    cerr << "Error opening input file: " << infile << endl;
    exit( 1 );
  }

  *suffix = '\0';
  strcpy( outfile, infile );
  strcat( outfile, ".kwy" );
  ofstream fout( outfile );
  if ( !fout ) {
    cerr << "Error opening output file: " << outfile << endl;
    exit( 1 );
  }

  read( fin, (char *) &header, sizeof(header_t) );
  read( fin, (char *) episode, header.num_episodes * sizeof(short) );

  fout << "# Keepers: " << header.keepers << endl;
  fout << "# Takers:  " << header.takers << endl;
  fout << "# Region:  " << header.width << " x " << header.length << endl;
  fout << "#\n"
       << "# Description of Fields:\n"
       << "# 1) Episode number\n"
       << "# 2) Start time in simulator steps (100ms)\n"
       << "# 3) End time in simulator steps (100ms)\n"
       << "# 4) Duration in simulator steps (100ms)\n"
       << "# 5) (o)ut of bounds / (t)aken away\n"
       << "#\n";

  int start = 0;
  for ( int i = 0; i < header.num_episodes; i++ ) {
    int ep; char c;
    if ( episode[ i ] < 0 ) {
      ep = -episode[ i ];
      c = 't';
    }
    else {
      ep = episode[ i ];
      c = 'o';
    }
    fout << i + 1 << "\t" << start << "\t"
	 << start + ep << "\t" << ep << "\t" << c << endl;
    start += ep;
  }

  close( fin );
  fout.close();
}
