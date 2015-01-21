#ifndef NULL_DELETER_HPP
#define	NULL_DELETER_HPP

struct NullDeleter
{
	void operator()(const void*){}
};

#endif	
