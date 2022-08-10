#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"

class NotFound : public std::exception
{
public:
	virtual const char* what() const throw(){return NOT_FOUND;}
};

class BadRequest : public std::exception
{
public:
	virtual const char* what() const throw(){return BAD_REQUEST;}
};

class PermissionDenied : public std::exception
{
public:
	virtual const char* what() const throw(){return PERMISSION_DENIED;}
};

#endif