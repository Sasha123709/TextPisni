#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Song {
    string name;
    string author;
    int year;
    string text;
};
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void add(vector<Song>& catalog) {
    Song song;
    cout << "Enter the name of song: ";
    getline(cin, song.name);
    cout << "Enter the author of song: ";
    getline(cin, song.author);
    cout << "Enter the year of song: ";
    cin >> song.year;
    cin.ignore();
    cout << "Enter the text of song(empty line for end): "<<endl;
    string line;
    while (getline(cin, line) && !line.empty()) {
        song.text += line + "\n";
    }
    catalog.push_back(song);
    Sleep(1000);
    cout << "Please wait";
    for (int i = 0; i < 3; i++) {
        cout << '.';
        Sleep(1000);
    }
    setColor(10);
    cout << "\nReady!"<<endl;
    setColor(7);
    
}

void save(vector<Song>& catalog) {
    ofstream file("text.txt");
    if (!file) {
        setColor(12);
        cout << "ERROR!";
        setColor(7);
    }

    for (auto& song : catalog) {
        file << song.name << endl;
        file << song.author << endl;
        file << song.year << endl;
        file << song.text << endl;
    }

    Sleep(1000);
    cout << "Please wait";
    for (int i = 0; i < 3; i++) {
        cout << '.';
        Sleep(1000);
    }
    setColor(10);
    cout << "\nReady!" << endl;
    setColor(7);
    file.close();
}
void load(vector<Song>& catalog) {
    ifstream file("text.txt");
    if (!file) {
        setColor(12);
        cout << "ERROR!";
        setColor(7);
    }

    Song song;
    string line;
    while (getline(file, song.name)) {
        getline(file, song.author);
        file >> song.year;
        file.ignore();
        song.text.clear();
        while (getline(file, line) && !line.empty()) {
            song.text += line + "\n";
        }
        catalog.push_back(song);
    }
    Sleep(1000);
    cout << "Please wait";
    for (int i = 0; i < 3; i++) {
        cout << '.';
        Sleep(1000);
    }
    setColor(10);
    cout << "\nReady!" << endl;
    setColor(7);
    file.close();
}

void del(vector<Song>& catalog, string& title) {
    auto it = remove_if(catalog.begin(), catalog.end(), [&](const Song& song) { // capture list
        return song.name == title;
        });
    if (it != catalog.end()) {
        catalog.erase(it, catalog.end());
        Sleep(1000);
        cout << "Please wait";
        for (int i = 0; i < 3; i++) {
            cout << '.';
            Sleep(1000);
        }
        setColor(10);
        cout << "\nThe song is removed!" << endl;
        setColor(7);
    }
    else {
        cout << "ERROR!" <<endl;
    }

}

void dysplay(vector<Song>& catalog, string& title) {
    for (auto song : catalog) {
        if (song.name == title) {
            cout << "Text \"" << song.name << "\":\n" << song.text << "\n";
            return;
        }
        cout << "ERROR!";
    }
}
void dysplaybyautor(vector<Song>& catalog, string& author) {
    bool found = false;
    Sleep(1000);
    cout << "Finding";
    for (int i = 0; i < 3; i++) {
        cout << '.';
        Sleep(1000);
    }
    for (auto& song : catalog) {
        if (song.author == author) {

            cout << "\nName: " << song.name << "\nAuthor: " << song.author << "\nYear: " << song.year;
            found = true;
        }
        if (!found) {
            cout << "ERROR!" << endl;
        }
    }
}
void change(vector<Song>& catalog, string& title) {
    for (auto& song : catalog) {
        if (song.name == title) {
            cout << "Enter the new text of song(empty line for end):";
            song.text.clear();
            string line;
            while (getline(cin, line) && !line.empty()) {
                song.text += line + "\n";
            }
            Sleep(1000);
            cout << "Please wait";
            for (int i = 0; i < 3; i++) {
                cout << '.';
                Sleep(1000);
            }
            setColor(10);
            cout << "\nReady!" << endl;
            setColor(7);
            return;
        }
    }
    cout << "ERROR!";
}
void find(vector<Song>& catalog, string& word) {
    bool found = false;
    Sleep(1000);
    cout << "Finding";
    for (int i = 0; i < 3; i++) {
        cout << '.';
        Sleep(1000);
    }

    for (auto& song : catalog) {
        if (song.text.find(word) != string::npos) {
            cout << "\nName: " << song.name << "\nAuthor: " << song.author << "\nYear: " << song.year;
            found = true;
        }
    }

    if (!found) {
        cout << "ERROR!" << endl;
    }
}


int main() {
    vector<Song> catalog;
    int choice=1;
    while (choice != 0) {

        cout << "\t\tMenu\n1) Add song\n2) Save songs to file\n3) Load songs from file\n4) Delete song\n5) Display song\n6) Display songs by author\n7) Change text of song\n8) Find song with a word\n0) Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            add(catalog);
            break;
        case 2:
            save(catalog);
            break;
        case 3:
            load(catalog);
            break;
        case 4: {
            string name;
            cout << "Enter the name of song, wich do you want to delete: ";
            getline(cin, name);
            del(catalog, name);
            break;
        }
        case 5: {
            string title;
            cout << "Enter the name of song, wich do you want to display: ";
            getline(cin, title);
            dysplay(catalog, title);
            break;
        }
        case 6: {
            string author;
            cout << "Enter the autor of song, wich do you want to display: ";
            getline(cin, author);
            dysplaybyautor(catalog, author);
            break;
        }
        case 7: {
            string title;
            cout << "Enter the name of song, wich do you want to change: ";
            getline(cin, title);
            change(catalog, title);
            break;
        }
        case 8: {
            string word;
            cout << "Enter the word in song, wich do you want to display: ";
            getline(cin, word);
            find(catalog, word);
            break;
        }
        default:
            break;
        }
    }
}