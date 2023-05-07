
// ------------------------------------------------------------------------------------------------ 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
    T rand(T a, T b) {
        return uniform_int_distribution<T>(a, b)(rng);
    }

template<class T>
    T rand() {
        return uniform_int_distribution<T>()(rng);
    }
// ------------------------------------------------------------------------------------------------ 

void printTimeElapsedMins(clock_t tStart,string s){
  cout<<s<<endl;
  cout<<"Time elapsed since start : "<<((double)(clock()-tStart)/CLOCKS_PER_SEC)/60.0<<" mins\n\n";
}

void printTimeElapsedSeconds(clock_t tStart,string s){
  cout<<s<<endl;
  cout<<"Time elapsed since start : "<<((double)(clock()-tStart)/CLOCKS_PER_SEC)<<" seconds\n\n";
}
// ------------------------------------------------------------------------------------------------ 

bool IsEqualCell(Cell a, Cell b){
    return (a.x==b.x && a.y==b.y);
}

Cell GetNextCell(Cell cell,int n,int m){
    cell.y++;

    if( cell.y == m){
        cell.x++;
        cell.y = 0;
    }

    if(cell.x==n){
        cell.x = 0;
    }

    return cell;
}

Cell GetPrevCell(Cell cell,int n,int m){
    cell.y--;

    if( cell.y < 0){
        cell.x--;
        cell.y = m-1;
    }

    if(cell.x < 0){
        cell.x = n-1;
    }
    
    return cell;
}

Cell GetRandomCell(int n,int m){
    Cell i = Cell( rand(0,n-1) , rand(0,m-1) );

    return i;
}

pii GetRandomPair(int n,int m){
    pair<int,int>p = {rand(0,n-1) , rand(0,m-1)};

    return p;
}

int distance(Cell& a, Cell& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

Genotype GetRandomMember(int n,int m){
    // clock_t start = clock();
    Genotype randomGene ;
    vector<int>ar(n*m);
    for(int i = 0 ; i < n*m ; ++i){
        ar[i] = i;
    }
    shuffle(ar.begin(),ar.end(),rng);

    randomGene.Warehouse = vector<vi>(n,vi(m));
    for(int i = 0 ; i < n*m ; ++i){
        int x = i/m;
        int y = i%m;

        randomGene.Warehouse[x][y] = ar[i];
        randomGene.AllItems[i] = {Cell(x,y)};
    }

    return randomGene;
}

// ------------------------------------------------------------------------------------------------ 

int i4_uniform_ab ( int a, int b )

//****************************************************************************80
//
//  Purpose:
//
//    I4_UNIFORM_AB returns a scaled pseudorandom I4 between A and B.
//
//  Discussion:
//
//    The pseudorandom number should be uniformly distributed
//    between A and B.
//

//  Parameters:
//
//    Input, int A, B, the limits of the interval.
//
//    Input/output, int &SEED, the "seed" value, which should NOT be 0.
//    On output, SEED has been updated.
//
//    Output, int I4_UNIFORM, a number between A and B.
//
{
  int c;
  const int i4_huge = 2147483647;
  int k;
  float r;
  int value;

  if ( seed == 0 )
  {
    cerr << "\n";
    cerr << "I4_UNIFORM_AB - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }
//
//  Guarantee A <= B.
//
  if ( b < a )
  {
    c = a;
    a = b;
    b = c;
  }

  k = seed / 127773;

  seed = 16807 * ( seed - k * 127773 ) - k * 2836;

  if ( seed < 0 )
  {
    seed = seed + i4_huge;
  }

  r = ( float ) ( seed ) * 4.656612875E-10;
//
//  Scale R to lie between A-0.5 and B+0.5.
//
  r = ( 1.0 - r ) * ( ( float ) a - 0.5 ) 
    +         r   * ( ( float ) b + 0.5 );
//
//  Use rounding to convert R to an integer between A and B.
//
  value = round ( r );
//
//  Guarantee A <= VALUE <= B.
//
  if ( value < a )
  {
    value = a;
  }
  if ( b < value )
  {
    value = b;
  }

  return value;
}

double r8_uniform_ab ( double a, double b )
//****************************************************************************80
//  Purpose:
//
//    R8_UNIFORM_AB returns a scaled pseudorandom R8.
//
//  Discussion:
//
//    The pseudorandom number should be uniformly distributed
//    between A and B.
//
{
  int i4_huge = 2147483647;
  int k;
  double value;

  if ( seed == 0 )
  {
    cerr << "\n";
    cerr << "R8_UNIFORM_AB - Fatal error!\n";
    cerr << "  Input value of SEED = 0.\n";
    exit ( 1 );
  }

  k = seed / 127773;

  seed = 16807 * ( seed - k * 127773 ) - k * 2836;

  if ( seed < 0 )
  {
    seed = seed + i4_huge;
  }

  value = ( double ) ( seed ) * 4.656612875E-10;

  value = a + ( b - a ) * value;

  return value;
}

void timestamp ( )
//  Purpose:
//    TIMESTAMP prints the current YMDHMS date as a time stamp.
//  Example:
//    May 31 2001 09:45:54 AM
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}


Genotype initial_pop(int n,int m){
    //currently assuming n % 10, m % 10. 
    int str = 0;
    int gap = 5;
    Genotype gene;
    gene.Warehouse = vector(n,vector<int>(m));
    for(int i = 0; i < n; i += gap){
        for(int j = 0; j < m; j += gap){
            for(int l = i; l < min(i + gap,n); l++){
                for(int k = j; k < min(j + gap,m); k++){
                    gene.Warehouse[l][k] = str;
                    gene.AllItems[str] = {Cell(l,k)};
                    str++;
                }
            }
        }
    }

    return gene;
}

// currenlty for 1 item warehouse placement
unordered_map<int,vector<Cell>> GetItemsMappingForWarehouse(vector<vi>&warehouse){
  unordered_map<int,vector<Cell>> allItems;

  int n = warehouse.size();
  int m = warehouse[0].size();

  fi(0,n-1){
    fj(0,m-1){
      allItems[warehouse[i][j]] = {Cell(i,j)};
    }
  }

  return allItems;
}