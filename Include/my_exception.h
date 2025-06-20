#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H


namespace my {

//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   Base class for the handling different kinds of exceptions
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
class Exception {
private:
protected:

    const char* mb_description;

public:
    explicit Exception(const char* description);

    virtual const char* what() const;
};





} // End of "my" namespace

#endif // MY_EXCEPTION_H
