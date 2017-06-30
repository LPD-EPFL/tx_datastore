
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "VersionManager.h"
#include "DataService.h"
#include <chrono>
#include <thread>

#include <libcuckoo/cuckoohash_map.hh>
#include <libcuckoo/city_hasher.hh>

#define DEFAULT_TIMEOUT 10 //in milliseconds
#define MIN_NUM_RETRIES 5

class Scheduler : virtual public DataServiceIf {
  public:
    
    Scheduler() {
      // Your initialization goes here
      wait_time = DEFAULT_TIMEOUT;
    }
    Scheduler(int timeout){
      wait_time = timeout;
    }
    ~Scheduler(){}
    
    void HandleAbort(AbortReply& _return, const TransactionId tid);
    void HandleCommit(CommitReply& _return, const TransactionId tid, const Timestamp ts);
    void HandleReadRequest(ReadReply& _return, const TransactionId tid, const TimestampInterval& interval, const Key& k);
    void HandleWriteRequest(WriteReply& _return, const TransactionId tid, const TimestampInterval& interval, const Key& k, const Value& v);
    void HandleFreezeReadRequest(ReadReply& _return, const TransactionId tid, const TimestampInterval& interval, const Key& k);

  private:
    int wait_time;
    VersionManager version_manager;

    //For the concurrent hash table implementation, see https://github.com/efficient/libcuckoo
    //Map
    //cuckoohash_map<TransactionId, cuckoohash_map<Key, std::pair<Value,TimestampInterval>, CityHasher<Key>>, CityHasher<TransactionId>> pendingWriteSets;
    cuckoohash_map<TransactionId, unordered_map<Key, std::pair<Value,TimestampInterval>>, CityHasher<TransactionId>> pendingWriteSets;

    inline bool timeout(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> end) {
       auto diff = end - start;
       auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
       if (ms.count() > wait_time) {
        return true;
       }
       return false;
    }

};

#endif
