
#include "TransactionManager.h"

Transaction* TransactionManager::StartTransaction(){
	TransactionId tid = oracle.GetTransactionId();
	Timestamp ts = oracle.GetTimestamp();
	Transaction *t = new Transaction(tid,ts);
	return t;
}

bool TransactionManager::ReadData(Transaction* transaction, Key key, Value& value){
    const Value* contains = transaction->FindInWriteSet(key);
    if(contains == NULL){
        contains = transaction->FindInReadSet(key);
    }
    if(contains != NULL){
        value = *contains;
        return true;
    }
    
    TimestampInterval current_interval = transaction->committed_interval;
    ServerConnection server  = service.GetServer(key);

    ReadReply reply;
    server->client = 




    return false;
}

bool TransactionManager::CommitTransaction(Transaction* transaction){
    return true;
}
