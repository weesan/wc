/*
 * Some stats:
 *
 * On a file with 1457794071 (~1.4B) lines (or names), it takes about
 * 15 mins to do the word count on a 8-cpu machine (Intel(R) Xeon(R)
 * CPU E5-2680 v2 @ 2.80GHz) with 16G of memory.
 *
 * real    15m14.777s
 * user    14m52.724s
 * sys     0m21.464s
 *
 * C++
 * Processing z.log ...
 * Processed 1457794071 lines.
 *  19000949: [james]
 *  18883180: [john]
 *  16928312: [robert]
 *  16376832: [michael]
 *  14083130: [david]
 *  13098420: [mary]
 *  12836484: [william]
 *  12123425: [smith]
 *  11814266: [thomas]
 *  10989334: [j]
 *  10018107: [johnson]
 *
 *
 * To compile on Mac:
 * $ g++ -std=c++11 -O3 wc.cc -o wc
 */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <unordered_map>

// Pick either CPP or C
//#define CPP
#define C

// When choosing CPP above, pick one of the following:
//#define STL_COPY
//#define BOOST
#define STRTOK

#ifdef BOOST
#include <boost/algorithm/string.hpp>
#endif

using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return -1;
    }

    //  Don't sync C++ and C I/O
    //std::ios::sync_with_stdio(false);

    cout << "C++" << endl;
    cout << "Processing " << argv[1] << " ..." << endl;

    //map<string, int> wc;
    unordered_map<string, int> wc;
    int count = 0;

#ifdef CPP
    fstream ifs(argv[1]);
    string line;

    while (getline(ifs, line)) {
        count++;
        //cout << line << endl;

#ifdef STL_COPY
        istringstream iss(line);
        vector<string> words;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(words));
        if (words.size() == 0) {
            continue;
        }
        //cout << words.size() << endl;

        for (int i = 0; i < words.size(); i++) {
            wc[words[i]]++;
        }
#endif

#ifdef BOOST
        vector<string> words;
        boost::split(words, line, boost::is_any_of(" "));
        for (int i = 0; i < words.size(); i++) {
            wc[words[i]]++;
        }
#endif

#ifdef STRTOK
        for (char *word = strtok((char *)line.c_str(), " ");
             word; word = strtok(NULL, " ")) {
            wc[word]++;
        }
#endif
    }
#endif

#ifdef C
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        return -1;
    }
    char line[8192];
    while (fgets(line, sizeof(line), fp)) {
        count++;
        line[strlen(line) - 1] = 0;
        if (line[0] == 0) {
            continue;
        }
        for (char *word = strtok(line, " "); word; word = strtok(NULL, " ")) {
            wc[word]++;
        }
    }
    fclose(fp);
#endif

    cout << "Processed " << count << " lines." << endl;

    vector<std::pair<string, int> > sorted_wc;
    copy(wc.begin(), wc.end(), back_inserter(sorted_wc));
    sort(sorted_wc.begin(), sorted_wc.end(),
         [](const std::pair<string, int> &a, const std::pair<string, int> &b) {
             return a.second > b.second;
         });
    for (int i = 0; i < sorted_wc.size(); i++) {
        //cout << sorted_wc[i].second << " " << sorted_wc[i].first << endl;
        printf("%10d: [%s]\n", sorted_wc[i].second, sorted_wc[i].first.c_str());
    }

    return 0;
}
