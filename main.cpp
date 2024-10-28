#include <cstdlib>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <vector>

using namespace std;

void setSettings(int& width, int& height, float& refreshTime) {
    string input;
    while (true) {
        try {
            cout << "width: ";
            cin >> input;
            width = stoi(input);
            break;
        } catch(...) {
            cout << "incorrect number" << endl;
        }
    }

    while (true) {
        try {
            cout << "height: ";
            cin >> input;
            height = stoi(input);
            break;
        } catch(...) {
            cout << "incorrect number" << endl;
        }
    }

    while (true) {
        try {
            cout << "refresh time (s): ";
            cin >> input;
            refreshTime = stof(input);
            break;
        } catch(...) {
            cout << "incorrect number" << endl;
        }
    }   
}

void generate(vector<vector<bool>>& cells, int& width, int& height) {
    for (int i = 0; i != height; i++) {
        cells.push_back(vector<bool>()); 
        for (int j = 0; j != width; j++) {
            cells[i].push_back(rand() % 2);
        }            
    }
}

void update(vector<vector<bool>>& cells, int& width, int& height, float& refreshTime) {
    system("cls");
    cout << "width = " << width << " | height = " << height << " | refresh time = " << refreshTime << "s" << endl << endl;
    for (size_t i = 0; i < cells.size(); i++) {
        vector<bool>& row = cells[i];
        for (size_t j = 0; j < row.size(); j++) {

            short neighbors = 0;
            if (j > 0 && cells[i][j - 1])
                neighbors++;
            if (j < row.size() - 1 && row[j + 1]) {
                neighbors++;
            }
            if (i > 0) {
                if (j > 0 && cells[i - 1][j - 1]) {
                    neighbors++;
                }
                if (cells[i - 1][j]) {
                    neighbors++;
                }
                if (j < row.size() - 1 && cells[i - 1][j + 1]) {
                    neighbors++;
                }                                
            }
            if (i < cells.size() - 1) {
                if (j > 0 && cells[i + 1][j - 1]) {
                    neighbors++;
                }
                if (cells[i + 1][j]) {
                    neighbors++;
                }               
                if (j < row.size() - 1 && cells[i + 1][j + 1]) {
                    neighbors++;
                }              
            }            

            if (row[j] == true) { 
                if (neighbors < 2 || neighbors > 3) {
                    row[j] = false; 
                } 
            } else {
                if (neighbors == 3) {
                    row[j] = true; 
                }
            }

            cout << (row[j] ? "\033[42m " : "\033[40m ");
        }
        cout << "\033[40m " << endl;
    }
}

void loop(vector<vector<bool>>& cells, int& width, int& height, float& refreshTime) {
    while (true) {
        update(cells, width, height, refreshTime);
        usleep(refreshTime * 1000000);
    }    
}

int main() {
    srand(time(0));
    vector<vector<bool>> cells;
    int width, height;
    float refreshTime;

    setSettings(width, height, refreshTime);

    generate(cells, width, height);

    loop(cells, width, height, refreshTime);
    
    return 0;
}