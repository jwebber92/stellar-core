#include <iostream>
#include "BulkWriterManager.h"
#include "database/Database.h"

using namespace soci;

namespace stellar
{

TxHistoryWriter::TxHistoryWriter(){
    rows.reserve(10000);
}

void TxHistoryWriter::write(Database &db){
    std::cout << "\n\nwrite " << rows.size() << std::endl;
    if(rows.empty()){
        return;
    }

    soci::session& session = db.getSession();
    std::ostringstream oss;
    oss << "insert into txhistory(txid, ledgerseq, txindex, txbody, txresult, txmeta) values ";
    for(int i = 0; i < rows.size(); i++){
        const TxHistoryRow &row = rows[i];
        oss << "("
            << "'" << row.txid << "'," 
            << row.ledgerseq << "," 
            << row.txindex << "," 
            << "'" << row.txbody << "'," 
            << "'" << row.txresult << "'," 
            << "'" << row.txmeta << "'" 
            << ")";
        if(i < (rows.size() - 1)){
            oss << ",";
        }
    }
    oss << ";";
    session << oss.str();
    rows.clear();
}

}