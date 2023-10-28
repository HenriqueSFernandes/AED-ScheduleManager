// request.h

#ifndef PROJAED_REQUEST_H
#define PROJAED_REQUEST_H

#include "student.h"
#include "studentGroup.h"

class Request {
private:
    static int count;  // Declare a static member variable for request ID.
    int requestId; //The ID that identifies each Request
    bool processed;
    std::string type;



public:
    Request(string type) {
        requestId = count++;
        processed=0;
        this->type=type;
    }
    void setProcessed(bool processed){
        this->processed=processed;
    }
    string getType(){ return type;}
};

#endif // PROJAED_REQUEST_H