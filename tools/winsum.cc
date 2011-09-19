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

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

int
main( int argc, char* argv[] )
{
  char buffer[MAX_BUFFER];
  int windowSize;
  int *q;       // Episode duration queue
  int sum = 0;  // Window sum of episode durations
  int i;
  int iDummy;
  double alpha = 1;
  long coarse = 1;
  long ccount;
  long start = 0;
  char cDummy;
  double prev;

  if ( argc < 2 ) {
    cerr << "Usage: " << argv[ 0 ]
	 << " <window size> [<filter-coefficient>] [<coarseness>]\n";
    return 1;
  }

  if ( argc > 2 ) {
    alpha = atof( argv[ 2 ] );
  }

  if ( argc > 3 ) {
    coarse = atol( argv[ 3 ] );
  }

  windowSize = atoi( argv[ 1 ] );
  q = new int[ windowSize ];

  // Ignore Header
  do {
    cin.getline( buffer, MAX_BUFFER );
  } while ( buffer[ 0 ] == '#' );

  for ( i = 0; i < windowSize; i++ ) {
    if ( cin >> iDummy ) {
      cin >> iDummy;
      cin >> iDummy;
      cin >> q[ i ];
      cin >> cDummy;
      sum += q[ i ];
    }
    else {
      cerr << "Not enough data to fill window\n";
      return 1;
    }
  }
  
  i = 0;
  ccount = 0;

  start = 0;
  prev = sum;
  while ( !cin.eof() ) {
    if ( ccount % coarse == 0 )
      cout << start / 10.0 / 3600 << " "
	   << prev / 10.0 / windowSize << endl;
    
    sum -= q[ i ];
    cin >> iDummy;
    cin >> iDummy;
    cin >> iDummy;
    cin >> q[ i ];
    cin >> cDummy;
    sum += q[ i ];
    start += q[ i ];

    prev = ( 1 - alpha ) * prev + alpha * sum;
    i = ( i + 1 ) % windowSize;
    ccount++;
  }

  delete [] q;

  return 0;
}

