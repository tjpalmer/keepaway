/*
Copyright (c) 2002-2004 Gregory Kuhlmann
University of Texas at Austin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the University of Amsterdam nor the names of its
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define MAX_BUFFER 1024
#define START_SIZE 1000

#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int*
doubleIt( int* array, int &aSize )
{
  int* a = new int[ aSize * 2 ];
  memcpy( a, array, aSize * sizeof( int ) );
  delete [] array;
  aSize *= 2;
  return a;
}

int i_cmp( int* a, int* b ) { return *a - *b; }

int
main( int argc, char* argv[] )
{
  char buffer[MAX_BUFFER];
  int arraySize;
  int count;
  int numOut;
  double interval;
  double intStart;
  double intEnd;
  double current;
  int *q;       // Episode duration queue
  int i;
  int iDummy;
  char cDummy;
  long sum=0;

  if ( argc < 2 ) {
    cerr << "Usage: " << argv[ 0 ]
	 << " <interval in secs>\n";
    return 1;
  }

  interval = atof( argv[ 1 ] );
  arraySize = START_SIZE;
  q = new int[ arraySize ];

  // Ignore Header
  do {
    cin.getline( buffer, MAX_BUFFER );
  } while ( buffer[ 0 ] == '#' );

  
  i = 0;
  numOut = 0;
  while ( !cin.eof() ) {
    cin >> iDummy;
    cin >> iDummy;
    cin >> iDummy;
    cin >> q[ i ];
    cin >> cDummy;

    sum += q[ i++ ];

    if ( cDummy == 'o' )
      numOut++;

    if ( i >= arraySize )
      q = doubleIt( q, arraySize ); 
  }
  i--;

  qsort( q, i, sizeof( int ),
	 (int (*) (const void*, const void*)) i_cmp );

  cerr << "Mean:   " << sum / 10.0 / i << endl;
  cerr << "Median: " << q[i/2] / 10.0 << endl;
  cerr << "Ended:  " << numOut * 100.0 / i << "% out, "
       << ( i - numOut ) * 100.0 / i << "% taken" << endl;

  intStart = 0;
  intEnd = interval;
  count = 0;
  for ( int j = 0; j < i; j++ ) {
    if ( ( current = q[j] / 10.0 ) > intEnd ) {
      cout << intStart << "\t"
	   << count << endl;
      count = 0;
      intStart = intEnd;
      intEnd += interval;
      j--;
    }
    else
      count++;
  }
  cout << intStart << "\t"
       << count << endl;


  delete [] q;

  return 0;
}

