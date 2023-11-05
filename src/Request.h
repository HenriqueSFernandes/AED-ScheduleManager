/// @file Request.h
#ifndef PROJAED_REQUEST_H
#define PROJAED_REQUEST_H

#include "student.h"
#include "studentGroup.h"

/**
 * @brief Class used to represent a generic request.
 */
class Request {
private:
    static int count;  // Static variable for request counter.
    int requestId; // ID for each request.

    std::string type;

public:
    /**
     * @brief Resets the request counter.
     */
    void static resetCount() {
        count = 0;
    }

    /**
     * @brief Parameterized constructor.
     * @param type String representing the request type (add/remove/switch).
     */
    Request(std::string type) {
        count++;
        requestId = count;
        this->type = type;
    }

    /**
     * @brief Gets the type of the request.
     * @return A string representing the type of the request.
     */
    std::string getType() const { return type; }

    // Virtual function for allowing downcasting.
    virtual void dummy() {}

    virtual ~Request() {};
};

#endif // PROJAED_REQUEST_H
