//! g++ -std=c++11 dataset.cpp -fsyntax-only
#include "dataset.h"

using namespace std;

const string fileListPath = "./data/list.txt";
const string dataDir      = "./data";
map< Dataset::DataType, vector< string > > Dataset::fileList;
map< string, Dataset::DataType > typeMap;

Dataset::Dataset(DataType type)
{
    if (typeMap.empty()) {
        typeMap["<square>"] = DataType::square;
        typeMap["<mv>"]     = DataType::mv;
        typeMap["<symm>"]   = DataType::symm;
        typeMap["<hemm>"]   = DataType::hemm;
    }
    if (fileList.empty()) {
        ifstream listfs(fileListPath);
        string type;
        listfs >> type;
        if (typeMap.count(type) == 0) {
            throw string("Unknown DataType ") + type;
        }
        
    }
}

Dataset::~Dataset()
{
}

void Dataset::set(uint32_t &n, uint32_t &m, uint32_t &k,
                  double *&A, double *&B, double *&C )
{
    
}
