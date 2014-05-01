#pragma once

#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <stdint.h>
class Dataset
{
public:
    enum DataType {
        square,
        mv,
        symm,
        trmm,
        hemm
    };

    Dataset(DataType type);
    ~Dataset();
    void change();
    void set(uint32_t &n, uint32_t &m, uint32_t &k,
             double *&A, double *&B, double *&C );
private:
    std::ifstream ifs;
    static std::map< DataType, std::vector< std::string > > fileList;
    const static std::string fileListPath;
    const static std::string dataDir;
    static std::map< std::string, DataType > typeMap;
};
