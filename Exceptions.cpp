#include <exception>
#include <vector>
#include <tuple>
#include <sstream>


using std::vector;

class matrixInitializationException : virtual public std::exception {

protected:

    int __rows;
    int __cols;
    int __data;

public:

    explicit
        matrixInitializationException(const vector<double> data, int rows, int cols):
        __rows(rows),
        __cols(cols),
        __data(data.size())
    {}

    virtual const char* what() const throw() {
        std::stringstream exception_message;
        exception_message << "Parameters don't match:\n" << __data << " data len | " << __rows << " rows | " << __cols << " cols\nRows * Cols should equal the data length";
        return exception_message.str().c_str();
;
    }


    virtual ~matrixInitializationException() throw () {}
};