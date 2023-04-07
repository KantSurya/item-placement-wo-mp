
// ------------------------------------------------------------------------------------------------ 
#define debug(x) cout<<#x<<": "<<x<<endl;
#define DEBUG(x) cout<<#x<<": \n"; for(int i = 0 ; i < x.size() ; ++i)cout<<x[i]<<" \n"[i==(int)x.size()-1];
#define debugCell(c) cout<<#c<<": "<<c.x<<" "<<c.y<<endl;

#define fi(a,b) for(int i = a ; i<=b ; ++i)
#define fj(a,b) for(int j = a ; j<=b ; ++j)

#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int,int>
// ------------------------------------------------------------------------------------------------ 


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

vector<vi>GetRandomMember(int n,int m){
    vector<int>ar(n*m);
    for(int i = 0 ; i < n*m ; ++i){
        ar[i] = i;
    }
    shuffle(ar.begin(),ar.end(),rng);

    vector<vi>randomMember(n,vi(m));
    for(int i = 0 ; i < n*m ; ++i){
        int x = i/m;
        int y = i%m;

        randomMember[x][y] = ar[i];
    }

    return randomMember;
}