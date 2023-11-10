#ifndef __QUEUE_OF_STRINGS_HPP
#define __QUEUE_OF_STRINGS_HPP

#include <string>
#include <stdexcept>

class QueueEmptyException : public std::runtime_error 
{
public:
	explicit QueueEmptyException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Object>
class GenericQueue
{
private:
	// fill in private member data here


public:
	GenericQueue();

	// Note:  copy constructors are required.
	// Be sure to do a "deep copy" -- if I 
	// make a copy and modify one, it should not affect the other. 
	GenericQueue(const GenericQueue & st);
	GenericQueue & operator=(const GenericQueue & st);
	~GenericQueue();

	size_t size() const noexcept;
	bool isEmpty() const noexcept;


	void enqueue(const Object & elem);


	// both versions of front(), as well as dequeue(), throw a QueueEmptyException if called when empty.
	Object & front();
	const Object & front() const;

	// does not return anything.  Just removes. 
	void dequeue();
};






template<typename Object>
GenericQueue<Object>::GenericQueue()
{
}



// Note:  copy constructors are required.
// Be sure to do a "deep copy" -- if I 
// make a copy and modify one, it should not affect the other. 
template<typename Object>
GenericQueue<Object>::GenericQueue(const GenericQueue & st)
{

}

template<typename Object>
GenericQueue<Object> & GenericQueue<Object>::operator=(const GenericQueue<Object> & st)
{
	if( this != &st )
	{
		// delete the current materials then finish the assignment operation.
	}

	return *this;

}

template<typename Object>
GenericQueue<Object>::~GenericQueue() 
{
}


template<typename Object>
size_t GenericQueue<Object>::size() const noexcept
{
	return 561; // stub, probably not the right answer.
}


template<typename Object>
bool GenericQueue<Object>::isEmpty() const noexcept
{
	return false;  // stub, probably not the right answer.
}

template<typename Object>
void GenericQueue<Object>::enqueue(const Object & elem)
{

}


template<typename Object>
Object & GenericQueue<Object>::front()
{
	throw QueueEmptyException{"Queue is Empty"};  // stub, probably not the right answer.
}

template<typename Object>
const Object & GenericQueue<Object>::front() const
{
	throw QueueEmptyException{"Queue is Empty"};  // stub, probably not the right answer.
}


// does not return anything.  Just removes. 
template<typename Object>
void GenericQueue<Object>::dequeue()
{
	throw QueueEmptyException{"Queue is Empty"};// stub, probably not the right answer.
}




#endif 

