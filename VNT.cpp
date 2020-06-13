#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


/*Safe array within safe array*/
using namespace std;
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
} ;
class safe_matrix
{
public:
    int **p, m, n;

        
    safe_matrix(){
        p=NULL;
    }
    safe_matrix(int row, int col)
    {
        m = row;
        n = col;
        p = new int*[m];
        for (int i = 0; i < m; i++)
            p[i] = new int[n];
    }
    // ~safe_matrix()
    //{
    // for (int i = 0; i < m; i++)
    //  delete p[i];
    //delete p;
    //}
    void accept()
    {
        cout<<"Enter matrix elements:";
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cin >> p[i][j];
            }
        }
    }
    void display()
    {
        cout <<"The matrix is:";
        for(int i = 0; i < m; i++)
        {
            cout <<endl;
            for(int j = 0; j < n; j++)
            {
                cout << p[i][j] <<" ";
            }
        }
    }
    
    safe_matrix operator +(safe_matrix m2)
    {
        safe_matrix T(m, n);
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                T.p[i][j] = p[i][j] + m2.p[i][j];
            }
        }
        return T;
    }
    
    safe_matrix operator= (safe_matrix eq)
    {
        m = eq.m;
        n = eq.n;
        p = eq.p;
        
        return *this;
    }
    
    friend safe_matrix operator * (safe_matrix, safe_matrix);
};

safe_matrix operator* (safe_matrix a , safe_matrix b)
{
    safe_matrix B(1,1);
    if(a.n == b.m)
    {
        safe_matrix T(a.m, b.n);
        for(int i = 0; i < a.m; i++)
        {
            for(int k = 0; k < b.n; k++)
            {
                T.p[i][k] = 0;
                for(int j = 0; j < a.n; j++)
                {
                    T.p[i][k]+= a.p[i][j] * b.p[j][k];
                }
            }
        }
        B = T;
    }
    return B;
}



class VNT{
public:
    int** p ;
    //int MAX_INT;
    int x;
    int y;
    int temp_x,temp_y;
    
    class CRow {
        friend class VNT;
    public:
        int& operator[](int col)
        {
            return parent.p[row][col];
        }
    private:
        CRow(VNT &parent_, int row_) :
        parent(parent_),
        row(row_)
        {}
        
        VNT& parent;
        int row;
    };
    
    CRow operator[](int row)
    {
        return CRow(*this, row);
    }
    
public:
    VNT(){
        x=0;
        y=0;
        temp_y=0;
        temp_x=0;
        p=NULL;

    }
    VNT(int a,int b){
    
    
        x = a - 1;
        y = b - 1;
        temp_y=0;
        temp_x=0;
        
        p = new int*[a];
        for (int i = 0; i < a; i++)
            p[i] = new int[b];
        for( int i=0; i<=x ;i++){
            for( int j=0; j<=y ;j++){
                p[i][j]=0;
            }
        }
        //p[0][0]=INT_MAX;
        
      
        
    }
    int right_Parent(int& i){
        return ++i;
        
    }
    int left_Parent(int& j){
        return ++j;
    }
    
    void add(int d){
        p[temp_x][temp_y]=d;
        calibre(temp_x, temp_y);
        
        if(temp_y==y){
            if(temp_x==x)
                return;
                
                else {++temp_x;
                    temp_y=0;}
        }
         else ++temp_y;
    }
    int right (int& i){
        
        
            return --i;
            
    }
    int left (int& j){
    
    
        return --j;
    }
    int& smallest_paren(int i,int j){
        if(i==x)
            return p[x][left_Parent(j)];
        if(j==y)
            return p[right_Parent(i)][j];
        else
            if(p[i+1][j]<=p[i][j+1])
                return p[right_Parent(i)][j];
            else return p[i][left_Parent(j)];
        
    }
    int& smallest_parent(int& i,int& j){
        if(i==x)
            return p[x][left_Parent(j)];
        if(j==y)
            return p[right_Parent(i)][j];
        
        else
            if(p[i+1][j]<=p[i][j+1]){
                
                    return p[right_Parent(i)][j];}
        else return p[i][left_Parent(j)];
            
    }
    int  bigest_chil(int i,int j){
        if (i==0&&j==0)
            return p[0][0];
        if(i==0)
            return p[0][left(j)];
        if(j==0)
            return p[right(i)][0];
        else
            if(p[i-1][j]>=p[i][j-1]){
            
                return p[right(i)][j];
                
            }
            else return p[i][left(j)];
    }
   int&  bigest_child(int& i,int& j){
       if (i==0&&j==0)
           return p[0][0];
        if(i==0)
            return p[0][left(j)];
        if(j==0)
            return p[right(i)][0];
        else
            if(p[i-1][j]>=p[i][j-1])
            return p[right(i)][j];
            else return p[i][left(j)];
    }
    
    void calibre (int i,int j){

        int parent = p[i][j];
            if (i==0&&j==0)
                return;
            if (parent<=bigest_chil(i, j)){
                
            swap(&p[i][j],&bigest_child(i,j));
            
            calibre(i, j);
            }
    }
    //bool his_parents(int i;int j){
        
    
    void bubble (int i,int j){
        int& parent= smallest_paren(i, j);
        if (i>=temp_x&&j>=temp_y)
            return;
        if(parent==0)
            return;
        //cout<<"this p{]"<<parent<<endl;
            //return;
        if(parent<=p[i][j]){
          swap(&p[i][j],&smallest_parent(i, j));
    
        //cout<<"i J"<<i<<j<<endl;
            bubble(i, j);}
        
    }
    void decrease(){
    if(temp_y==0){
        if(temp_x==0)
            return;
        
        else {--temp_x;
            temp_y=y;}
    }
    else --temp_y;
}

    int getMin(){
        int temp=p[0][0];
        p[0][0]=p[temp_x][temp_y];
        //p[temp_x][temp_y]=INT_MAX;
        
        
        bubble(0, 0);
       for (int i=temp_x; i<=x;i++){
            for(int j=temp_y;j<=y;j++)
            p[i][j]=0;
        }
        //cout<<temp_x<<temp_y<<endl;
        decrease();
        //cout<<temp_x<<temp_y<<endl;
        return temp;
        
        
    }
    int* sort(int k[],int size){
        if (size>((x+1)*(y+1)))
            cout<< "array size is not right"<<endl;
        else
            for(int i=0; i<size;i++){
            //cout<<k[i]<<endl;
                this->add(k[i]);
                //this->display();
            }
        
        for(int i=0; i<=size;i++){
             k[i] = this->getMin();
        
            //cout<<this->getMin();
        }
        return k;
    
        
    
    }
        void display()
    {
        cout <<"The matrix is:";
        for(int i = 0; i <= x; i++)
        {
            cout <<endl;
            for(int j = 0; j <= y; j++)
            {
                cout << p[i][j] <<" ";
            }
        }
    }
    bool find(int q){
        if(q<p[0][0]||q>p[temp_x][temp_y])
            return false;
        while (getMin()!=0) {
            if(q==getMin())
            return true;
    }
        return false;
    }
};



int main(){
    
    
     
    VNT rf(3,3);
    VNT s(3,3);
    cout << "\nrf\n";
    rf.add(50);
    rf.display();
    rf.add(10);
    rf.display();
    rf.add(5);
    rf.display();
    rf.add(2);
    rf.display();
    rf.add(6);
    rf.display();
    rf.add(7);
    rf.display();
    rf.add(1);
    rf.display();
    rf.add(3);
    rf.display();
    rf.add(6);
    rf.display();
    cout<<endl;
     cout<<"smallest element in the vnt is "<<" "<<rf.getMin()<<endl;
    int arr[9]={4,7,2,5,8,0,1,3,6};
    cout<<"original array"<<endl;
    for (int i=0;i<9;i++)
        cout<<arr[i]<<" ";
    
    cout<<endl;
    int* ptr=s.sort(arr, 9);
    cout<<"the sorted Array is the following"<<endl;
    for(int i=0; i<9;i++)
       cout<<ptr[i]<<" ";
    cout<<endl;
    
    cout<<"query result for 4: "<<rf.find(4)<<endl;

    //s.display();
    //rf[0][0]=9;
   // rf.bubble(0, 0);
    //rf.display();
    //rf.add(13);
    //rf.add(6);
    //cout<<"here "<<" "<< rf.temp_x<<" "<< rf.temp_y<<endl;
   /* rf.getMin();
    rf.display();
   rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();
    rf.getMin();
    rf.display();//*/
    
    
    
    //rf.calibre(2,2);
    //rf.display();
    //cout<<rf.bigest_child(1, 1)<<endl;
    //swap(&rf.bigest_child(1, 1),&rf[1][1]);
    //rf.display();
    
}
