#include <iostream>
#include <fstream>
#include <vector>
#include "NaiveAlgo.h"
#include "SuffixTreeAlgo.h"

using std::string;
using std::cout;
using std::endl;

const string readText(const string &filePath);

const std::vector<string> readPatterns(const string &filePath);

void removeR(string &line);

void generateInput(int textLength, int patternsLength, int patternsCount, const int TEST_CASE);

void modifyInput();

void runTest(const int TEST_CASE);

int main() {
//    generateInput(1000000, 50000, 10000, 17);
//    modifyInput();
    runTest(16);
}

void runTest(const int TEST_CASE) {
    // Read input
    clock_t clock_1 = clock();
    const string TEXT = readText(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/string.txt");
    const std::vector<string> PATTERNS = readPatterns(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/patterns.txt");
    clock_t clock_2 = clock();
    float dict_diff((float) clock_2 - (float) clock_1);
//    cout << "Finish reading input in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
    cout << dict_diff / (CLOCKS_PER_SEC / 1000) << endl;

    // Build the Suffix Tree
    clock_1 = clock();
    SuffixTreeAlgo tree;
    tree.buildSuffixTree(const_cast<char *>(TEXT.c_str()));
    clock_2 = clock();
    dict_diff = (float) clock_2 - (float) clock_1;
//    cout << "Finish building suffix tree in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
    cout << dict_diff / (CLOCKS_PER_SEC / 1000) << endl;

    // Run naive algorithm
    std::ofstream outputFile;
    outputFile.open(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/Output.txt");
    clock_1 = clock();
    for (auto it = PATTERNS.begin(); it != PATTERNS.end(); it++) {
        int i = NaiveAlgo::CheckPatternOccur(TEXT, *it);
        outputFile << i << endl;
//        cout << "i = " << i << endl;
    }
    clock_2 = clock();
    dict_diff = (float) clock_2 - (float) clock_1;
//    cout << "Finish naive algorithm in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
    cout << dict_diff / (CLOCKS_PER_SEC / 1000) << endl;
    outputFile.close();

    // Run Suffix tree algorithm
    outputFile.open(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/Output.txt");
    clock_1 = clock();
    for (auto it = PATTERNS.begin(); it != PATTERNS.end(); it++) {
        outputFile << tree.checkForSubString(*it) << endl;
    }
    clock_2 = clock();
    dict_diff = (float) clock_2 - (float) clock_1;
//    cout << "Finish Suffix Tree algorithm in " << dict_diff / (CLOCKS_PER_SEC / 1000) << "ms" << endl;
    cout << dict_diff / (CLOCKS_PER_SEC / 1000) << endl;
    tree.freeSuffixTreeByPostOrder(tree.getRoot());
    outputFile.close();
}

const string readText(const string &filePath) {
    std::ifstream file(filePath);
    string text;
    std::getline(file, text);
//    removeR(text);
    file.close();
    return text;
}

const std::vector<string> readPatterns(const string &filePath) {
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

void removeR(string &line) {
    if (!line.empty() && line.at(line.size() - 1) == '\r')
        line.erase(line.size() - 1);
}

void generateInput(int textLength, int patternsLength, int patternsCount, const int TEST_CASE) {
    std::ofstream stringFile;
    stringFile.open(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/string.txt");

    string text;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < textLength; i++) {
        int num = rand() % 26;
        text += (char) (97 + num);
    }
    cout << text << endl;
    stringFile << text << endl;
    stringFile.close();

    std::ofstream patternFile;
    patternFile.open(
            "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_" +
                    std::to_string(TEST_CASE) + "/patterns.txt");
    patternFile << patternsCount << endl;
    for (int i = 0; i < patternsCount; i++) {
        struct timespec ts{};
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand(static_cast<unsigned int>((time_t) ts.tv_nsec));

        int num = rand() % (textLength - patternsLength + 1);
        string pattern = text.substr(static_cast<unsigned long>(num), static_cast<unsigned long>(patternsLength));
        cout << pattern << endl;
        patternFile << pattern << endl;
    }
    patternFile.close();
}

void modifyInput() {
    for (int TEST_CASE = 15; TEST_CASE >= 10; TEST_CASE--) {
        std::ifstream inFile(
                "/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_"
                        + std::to_string(TEST_CASE + 1) + "/patterns.txt");
        std::ofstream outFile;
        outFile.open("/Users/midnightblur/Documents/workspace/CLionProjects/COMP6651_Assignment02/test_cases/test_case_"
                             + std::to_string(TEST_CASE) + "/patterns.txt");

        string line;
        std::getline(inFile, line);
        int lineCount = std::stoi(line);
        outFile << lineCount << endl;

        for (int i = 0; i < lineCount; i++) {
            std::getline(inFile, line);
            outFile << line.substr(0, line.size() - 25) << endl;
        }

        outFile.close();
        inFile.close();
    }
}