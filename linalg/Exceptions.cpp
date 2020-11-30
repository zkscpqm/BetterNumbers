#include <exception>
#include <vector>
#include <tuple>
#include <format>


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
        return std::format("Parameters don't match:\n{} data len, {} rows, {} cols\nRows * Cols should equal the data length";
    }


    virtual ~matrixInitializationException() throw () {}
};