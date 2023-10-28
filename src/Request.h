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


public:
    Request() {
        requestId = count++;
        processed=0;
    }
    void setProcessed(bool processed){
        this->processed=processed;
    }
};

#endif // PROJAED_REQUEST_H