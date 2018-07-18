
#pragma once

#include "database/Database.h"

namespace stellar
{

struct TxHistoryRow {
    std::string txid;
    uint32_t ledgerseq;
    int txindex;
    std::string txbody;
    std::string txresult;
    std::string txmeta;
};

struct TxHistoryWriter {
    TxHistoryWriter();
    std::vector<TxHistoryRow> rows;
    void write(Database &db);
};

class BulkWriterManager {
    public:
    TxHistoryWriter txHistory;
    void commit(Database &db){
        txHistory.write(db);
    }
};

}