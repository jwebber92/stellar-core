
#pragma once

#include <iostream>
#include "database/Database.h"

using namespace soci;

namespace stellar
{
// TODO use a vector of TxHistory struct
// TODO preallocate space
struct TxHistoryWriter {
    std::vector<std::string> txids;
    std::vector<uint32_t> ledgerseqs;
    std::vector<int> txindexs;
    std::vector<std::string> txbodys;
    std::vector<std::string> txresults;
    std::vector<std::string> txmetas;

    void add(
        const std::string& txid,
        uint32_t ledgerseq,
        int txindex,
         std::string& txbody,
        const std::string& txresult,
        const std::string& txmeta
        )
    {
        txids.push_back(txid);
        ledgerseqs.push_back(ledgerseq);
        txindexs.push_back(txindex);
        txbodys.push_back(txbody);
        txresults.push_back(txresult);
        txmetas.push_back(txmeta);
    }

    void clear(){
        txids.clear();
        ledgerseqs.clear();
        txindexs.clear();
        txbodys.clear();
        txresults.clear();
        txmetas.clear();
    }

    void write(Database &db){
        std::cout << "\n\nwrite " << txids.size() << std::endl;
        if(txids.empty()){
            return;
        }

        soci::session& session = db.getSession();
        std::ostringstream oss;
        oss << "insert into txhistory(txid, ledgerseq, txindex, txbody, txresult, txmeta) values ";
        for(int i = 0; i < txids.size(); i++){
            oss << "("
                << "'" << txids[i] << "'," 
                << ledgerseqs[i] << "," 
                << txindexs[i] << "," 
                << "'" << txbodys[i] << "'," 
                << "'" << txresults[i] << "'," 
                << "'" << txmetas[i] << "'" 
                << ")";
            if(i < txids.size() -1){
                oss << ",";
            }
        }
        oss << ";";
        session << oss.str();
        clear();

    }
};

class BulkWriterManager {
    public:
    TxHistoryWriter txHistory;
    void commit(Database &db){
        txHistory.write(db);
    }
};

}