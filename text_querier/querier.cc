#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;

class TextQuery
{
public:
//......
void readFile(const string & filename);
void query(const string & word);//

private:
//......
vector<string> _lines;//O(1)
map<string, set<int> > _wordNumbers;//the the
map<string, int> _dict;//
};

void TextQuery::readFile(const string & filename) {
    std::ifstream ifs(filename);
    string line;
    string word;
    int line_counter = 0;

    while (getline(ifs, line)) {
        std::istringstream iss(line);
        _lines.emplace_back(line);
        while (iss >> word) {
            ++_dict[word];
            _wordNumbers[word].insert(line_counter);
        }
        ++line_counter;
    }
    
    ifs.close();
}

void TextQuery::query(const string & word) {
    cout << "------------------------------------------------------" << endl;

    cout << word << " occurs " << _dict[word] << " times" << endl;

    auto set_line = _wordNumbers[word];
    for (const auto& e : set_line) {
    // 因为是从零行开始记录，最终结果+1进行修正
        cout << "(line " << e + 1 << ") " << _lines[e] << endl; 
    }

    cout << "------------------------------------------------------" << endl;
}

void inputString(string& word) {
    cout << "please input a word which you want to query" << endl;
    cin >> word;
    while (!cin.eof()) {
        if (cin.bad()) {
            std::cerr << "cin has broken." << endl;
            return;
        } else if (cin.fail()) {
            std::cerr << "please input a string." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
            cin >> word;
        } else {
            break;
        }
    }
}

//程序测试用例
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "usage: fine_name" << endl;
        return EXIT_FAILURE;
    }
    string queryWord;
    TextQuery tq;

    while (1) {
        inputString(queryWord);
        tq.readFile(argv[1]);
        tq.query(queryWord);
    }
    return 0;
}
