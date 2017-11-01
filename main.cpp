#include <iostream>
#include <fstream>
#include <vector>
#include "NaiveAlgo.h"
#include "SuffixTree.h"

using std::string;
using std::cout;
using std::endl;

const string readText(const string& filePath);
const std::vector<string> readPatterns(const string& filePath);
void removeR(string& line);
void generateString();

int main() {
    //    generateString();

    // EDIT THE TEST CASE FOLDER HERE
    const string TEST_CASE = "test_case_1";

    // Read input
    clock_t clock_1 = clock();
    const string TEXT = readText("/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/" + TEST_CASE + "/string.txt");
    const std::vector<string> PATTERNS = readPatterns("/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/" + TEST_CASE + "/patterns.txt");

    // Build the Suffix Tree
    SuffixTree tree;
    tree.construct(TEXT);
    clock_t clock_2 = clock();
    float dict_diff((float) clock_2 - (float) clock_1);
    cout << "Finish reading input and building suffix tree in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;

    // Run naive algorithm
    clock_1 = clock();
    for (auto it = PATTERNS.begin(); it != PATTERNS.end(); it++) {
        int i = NaiveAlgo::CheckPatternOccur(TEXT, *it);
        cout << i << endl;
    }
    clock_2 = clock();
    dict_diff = (float) clock_2 - (float) clock_1;
    cout << "Finish naive algorithm in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;

    // Run Suffix tree algorithm
    clock_1 = clock();

    clock_2 = clock();
    dict_diff = (float) clock_2 - (float) clock_1;
    cout << "Finish Suffix Tree algorithm in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
}

const string readText(const string& filePath) {
    std::ifstream file(filePath);
    string text;
    std::getline(file, text);
//    removeR(text);
    file.close();
    return text;
}

const std::vector<string> readPatterns(const string& filePath) {
    std::ifstream file(filePath);
    std::vector<string> patterns;
    string line;
    std::getline(file, line);
    int lineCount = std::stoi(line);

    for (int i = 0; i < lineCount; i++) {
        std::getline(file, line);
        removeR(line);
        patterns.insert(patterns.end(), line);
    }

    file.close();
    return patterns;
}

void removeR(string& line) {
    if (!line.empty() && line.at(line.size() - 1) == '\r')
        line.erase(line.size() - 1);
}

void generateString() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 400000; i++) {
        int num = rand() % 26;
        cout << (char) (97 + num);
    }
    cout << "$";
}