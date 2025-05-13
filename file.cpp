#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("data.csv");
    ofstream outputFile("smallfile.csv");

    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    string line;
    int rowCount = 0;
    const int MAX_ROWS = 300;

    while (getline(inputFile, line)) {
        outputFile << line << '\n';
        rowCount++;

        // Stop after 20,000 rows
        if (rowCount > MAX_ROWS)
            break;
    }

    inputFile.close();
    outputFile.close();

    cout << "? Wrote first " << MAX_ROWS << " rows to smallfile.csv" << endl;

    return 0;
}
