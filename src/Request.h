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
    void static setCount() {
        count = 0;
    }

    Request(std::string type) {
        count++;
        requestId = count;
        cout << "request id is " << requestId << " and count is " << count << endl;
        processed = false;
        this->type = type;
    }

    void setProcessed(bool processed) {
        this->processed = processed;
    }

    std::string getType() const { return type; }

    // Add a virtual function (it can be a pure virtual function).
    virtual void dummy() {
        //ALLOWS DOWNCASTING
    }

    virtual ~Request() {};
};

#endif // PROJAED_REQUEST_H
