#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int t = 0;
    while (++ t) {
        cout << endl;
        cout << "###########################" << endl;
        cout << "Test #" << t << ":" << endl;

        system("gen.exe");
        system("brute.exe");
        cout << "Done generating." << endl;

        system("prog.exe");
        if (system("check")) {
            cout << "FAIL!!!" << endl;
            system("PAUSE");
            return 0;
        }
    }

    return 0;
}
