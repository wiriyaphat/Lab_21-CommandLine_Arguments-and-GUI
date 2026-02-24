#include <iostream>
#include <cstdlib>
using namespace std;
int main(int argc, char *argv[]){
    float sum = 0;
    for (int i = 1; i < argc; i++){
        sum += atof(argv[i]);
    }
    float aveg = sum/(argc-1);
    if (argc < 2)
    {cout << "Please input numbers to find average.";}
    else{
        cout << "---------------------------------\n";
        cout << "Average of " << argc-1 << " numbers = " << aveg << "\n";
        cout << "---------------------------------\n";
    }
}
