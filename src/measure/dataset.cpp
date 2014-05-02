//! g++ -std=c++11 dataset.cpp -fsyntax-only
#include "dataset.h"
#include <iostream>
#include <random>
using namespace std;

const string Dataset::dataDir      = "./data/";
const string Dataset::fileListPath = "./data/list.txt";
typedef map< Dataset::DataType, vector< string > > fileListMap_t;
fileListMap_t Dataset::fileListMap;
typedef map< string, Dataset::DataType > typeMap_t;
typeMap_t Dataset::typeMap;

Dataset::Dataset()
{
    if (typeMap.empty()) createTypeMap();
    if (fileListMap.empty()) createFileListMap();

    // // print all
    // fileListMap_t::iterator it = fileListMap.begin();
    // for (; it != fileListMap.end(); it++ ) {
    //     cout << "==== " << it->first << " ====" << endl;
    //     vector<string> fnames = it->second;
    //     vector<string>::iterator fit = fnames.begin();
    //     cout << "Count: " << fnames.size() << endl;
    //     for (; fit != fnames.end(); fit++ ) {
    //         cout << (*fit) << endl;
    //     }
    // }
}

Dataset::~Dataset()
{
}

void Dataset::createFileListMap()
{
    ifstream listfs(fileListPath);
    string type_str;
    // Decode first line
    listfs >> type_str;
    if (typeMap.count(type_str) == 0) {
        throw string("Unknown DataType ") + type_str;
    }
    DataType type = typeMap[type_str];
    while (!listfs.eof()) {
        string line;
        listfs >> line;
        if ( line == "" ) break;
        // Check whether the line matches the header lines
        if (typeMap.count(line) != 0) {
            // Set new type
            type_str = line;
            type = typeMap[type_str];
        } else {
            fileListMap[type].push_back(line);
        }
    }
    
}

void Dataset::createTypeMap()
{
    typeMap["<free>"]   = DataType::free;
    typeMap["<square>"] = DataType::square;
    typeMap["<mv>"]     = DataType::mv;
    typeMap["<symm>"]   = DataType::symm;
    typeMap["<trmm>"]   = DataType::trmm;
    typeMap["<hemm>"]   = DataType::hemm;
}

void Dataset::prepare(DataType type,
                      uint32_t &n, uint32_t &m, uint32_t &k)
{
    // prepare
    random_device seed_gen;
    mt19937 random(seed_gen());
    vector<string> files = fileListMap[type];
    if (files.size() == 0) {
        throw "There is no file in this type";
    }
    string file = files[random()%files.size()];
    ifs.open(dataDir + file);
    cout << "# " << file << " is selected!" << endl;
    
    // read n, m, k
    ifs.read((char*)(&n), sizeof(uint32_t));
    ifs.read((char*)(&m), sizeof(uint32_t));
    ifs.read((char*)(&k), sizeof(uint32_t));
    cout << "# n=" << n << " m=" << m << " k=" << k << endl;
    this->n = n; this->m = m; this->k = k;
}

void Dataset::set(int la, int lb, int lc,
                  double *A, double *B, double *C )
{
    // Fill in A, B, C
    for ( uint32_t i = 0; i < n; i++ ) {
        ifs.read((char*)(A+i*la), sizeof(double)*k);
    }
    for ( uint32_t i = 0; i < k; i++ ) {
        ifs.read((char*)(B+i*lb), sizeof(double)*m);
    }
    for (uint32_t i = 0; i < n; i++) {
        for (uint32_t j = 0; j < m; j++) {
            C[i*m+j] = 0;
        }
    }
    this->la = la; this->lb = lb; this->lc = lc;
}

int Dataset::check(double *C)
{
    // Check Answer
    double *ans = new double[n*m]();
    ifs.read((char*)ans, sizeof(double)*n*m);
    int wcount = 0;             // # of wrong answer
    for ( uint32_t i = 0; i < n; i++ ) {
        for ( uint32_t j = 0; j < m; j++ ) {
            if ( fabs(C[i*lc+j] - ans[i*m+j]) > 1E-9 ) {
                cerr << "### WRONG: "
                     << "C(" << i << ", " << j << ") != "
                     << "Ans(" << i << ", " << j << ") :: "
                     << "C = " << C[i*lc+j] << ", "
                     << "Ans = " << ans[i*m+j] << endl;
                wcount++;
            }
        }
    }
    return wcount;
}
