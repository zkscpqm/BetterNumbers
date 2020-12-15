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
        matrixInitializationException(const vector<double>& data, int rows, int cols):
        __rows(rows),
        __cols(cols),
        __data(data.size())
    {}

    explicit
        matrixInitializationException(const vector<vector<double>>& data) :
        __rows(data.size()),
        __cols(data.at(0).size()),
        __data(__rows * __cols)
    {}

    virtual const char* what() const throw() {
        std::stringstream exception_message;
        exception_message << "Parameters don't match:\n" << __data << " data len | " << __rows << " rows | " << __cols << " cols\nRows * Cols should equal the data length";
        return exception_message.str().c_str();
;
    }


    virtual ~matrixInitializationException() throw () {}
};

class matrixSizeError : virtual public std::exception {

protected:

    unsigned short _mx1_rows;
    unsigned short _mx2_rows;
    unsigned short _mx1_cols;
    unsigned short _mx2_cols;

public:

    explicit
        matrixSizeError(Matrix2D& mx1, Matrix2D& mx2){
        auto [_mx1_rows, _mx1_cols] = mx1.shape();
        auto [_mx2_rows, _mx2_cols] = mx2.shape();
    }

    virtual const char* what() const throw() {
        std::stringstream exception_message;
        exception_message << "Matrix sizes don't match: (" << _mx1_rows << "x" << _mx1_cols << ") vs (" << _mx2_rows << "x" << _mx2_cols << ")";
        return exception_message.str().c_str();
    }


    virtual ~matrixSizeError() throw () {}
};

class matrixOutOfRange : virtual public std::exception {

protected:

    unsigned short _mx_rows;
    unsigned short _mx_cols;
    unsigned short _row;
    unsigned short _col;

public:

    explicit
        matrixOutOfRange(Matrix2D& mx, unsigned short row, unsigned short col) {
        auto [_mx_rows, _mx_cols] = mx.shape();
        _row = row;
        _col = col;
    }

    virtual const char* what() const throw() {
        std::stringstream exception_message;
        exception_message << "Out of range: Tried to get (" << _row << ", " << _col << ") for matrix sized (" << _mx_rows << "x" << _mx_cols << ")";
        return exception_message.str().c_str();
    }


    virtual ~matrixOutOfRange() throw () {}
};