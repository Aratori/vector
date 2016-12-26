#include <iostream>
#include "MyVector.cpp"

using namespace std;


int main()
{
    MyVector<int> nVector(30, 2);
    MyVector<int> nnVector(30, 4);


    for(int i = 0 ; i < 20 ; i++)
        cout<<nnVector[i]<<endl;

    cin;

    return 0;
}
