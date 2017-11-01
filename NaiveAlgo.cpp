//
// Created by Quoc Minh Vu on 2017-10-31.
//

#include "NaiveAlgo.h"

int NaiveAlgo::CheckPatternOccur(const string &TEXT, const string &PATTERN) {
    int i = 0;
    for (auto it = TEXT.begin(); it != TEXT.end(); it++) {
        i++;
        if (*it == *PATTERN.begin()) {
            auto textIter = it;
            bool isSubString = true;
            for (auto patternIter = PATTERN.begin(); patternIter != PATTERN.end(); patternIter++, textIter++) {
                if (*textIter != *patternIter) {
                    isSubString = false;
                    break;
                }
            }
            if (isSubString)
                return i - 1;
        }
    }

    return -1;
}
