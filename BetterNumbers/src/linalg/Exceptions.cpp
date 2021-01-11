#include <exception>
#include <vector>
#include <tuple>
#include <sstream>
#include "Matrix2D.h"


class matrixInitializationException : virtual public std::exception {

protected:

    int __rows;
    int __cols;
    int __data;

public:

    explicit
        matrixInitializationException(const std::vector<double>& data, int rows, int cols):
        __rows(rows),
        __cols(cols),
        __data(data.size())
    {}

    explicit
        matrixInitializationException(const std::vector<std::vector<double>>& data) :
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

    unsigned short _mx1_rows = -1;
    unsigned short _mx2_rows = -1;
    unsigned short _mx1_cols = -1;
    unsigned short _mx2_cols = -1;

public:

    explicit
        matrixSizeError(Matrix2D& mx1, Matrix2D& mx2){
        _mx1_rows = mx1.numRows();
        _mx1_cols = mx1.numCols();
        _mx2_rows = mx2.numRows();
        _mx2_cols = mx2.numCols();
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

    unsigned short _mx_rows = -1;
    unsigned short _mx_cols = -1;
    unsigned short _row = -1;
    unsigned short _col = -1;

public:

    explicit
        matrixOutOfRange(Matrix2D& mx, unsigned short row, unsigned short col) {
        _mx_rows = mx.numRows();
        _mx_cols = mx.numCols();
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