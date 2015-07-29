
#ifndef _VERSION_SKIPLIST_H_
#define _VERSION_SKIPLIST_H_

#include "common.h"
#include "random.h"
#include "Version.h"

#define MAXLEVEL 4
class OrderedSetNode {
    friend class VersionSkiplist;
    public:
        OrderedSetNode(Timestamp ts, Version* v, int level);
        ~OrderedSetNode();

        inline Timestamp getTimestamp() {
            return timestamp;
        }

        inline Version* getVersion() {
            return version;
        }

        inline OrderedSetNode* getNext() {
            return next[0];
        }
    private:
        Timestamp timestamp;
        Version* version;
        uint32_t toplevel;
        OrderedSetNode** next;
};

//typedef struct Node_t {
    //Timestamp timestamp;
    //Version* version;
    //uint32_t toplevel;
    //struct Node_t** next;

    //Node(Timestamp ts, Version* v, int level);
    //~Node();

//} Node;

class VersionSkiplist {
    public:
        VersionSkiplist();
        ~VersionSkiplist();
        inline Timestamp getFirstTimestamp() {
            return head->next[0]->timestamp;
        }

        OrderedSetNode* find(Timestamp ts, OrderedSetNode* prev);
        int insert(Timestamp ts, Version* v);
        int remove(Timestamp ts);
        int reposition(Timestamp old_ts);
        size_t size();


    private:
        OrderedSetNode* head;
        inline int getRandomLevel();
        int levelmax;
        size_t sz;
};


#endif
