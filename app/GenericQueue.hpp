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
	// Declare the LinkedList struct within the GenericQueue object
	struct Node{
		Node(Object v)
		: value{v}, next{nullptr}
		{}
		Object value;
		Node * next;
		size_t ta_num;
	};

	Node * front1;


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

	size_t TA_num() const noexcept;
};






template<typename Object>
GenericQueue<Object>::GenericQueue() : front1{nullptr}
{
}



// Note:  copy constructors are required.
// Be sure to do a "deep copy" -- if I 
// make a copy and modify one, it should not affect the other. 
template<typename Object>
GenericQueue<Object>::GenericQueue(const GenericQueue & st)
{
	// If orginal is empty, nothing to copy
	if (st.front1 == nullptr)
	{
		return;
	}
	// Make sure the copy is not updated along with the original
	// Initialize original Node and the new copy Node. Also intialize the first string value
	Node * org = st.front1;	
	Node * copy = new Node(org -> value);
	// Set the copy as the front
	front1 = copy;
	// Loop through each node after the first string value and copy it
	while (org -> next != nullptr)
	{
		org = org -> next;
		enqueue(org -> value);
	}
}

template<typename Object>
GenericQueue<Object> & GenericQueue<Object>::operator=(const GenericQueue<Object> & st)
{
	// Check if the objects are equal. If not, remove all elements and deep copy
	if (this != & st)
	{
		// Loop through all Nodes and delete them
		while (!isEmpty())
		{
			dequeue();
		}

		// Copy from original
		Node * tmp = st.front1;
		while (tmp != nullptr)
		{
			enqueue(tmp -> value);
			tmp = tmp -> next;
		}
	}
	return *this;


}

template<typename Object>
GenericQueue<Object>::~GenericQueue() 
{
	// Goes through each Node in QueueofStrings object and deletes it
	while (front1 != nullptr)
	{
		Node * tmp = front1;
		front1 = front1->next;
		delete tmp;
	}
}


template<typename Object>
size_t GenericQueue<Object>::size() const noexcept
{
	// Initialize size counter and Node pointer holder
	size_t counter = 0;
	Node * tmp = front1;
	// Loop through every Node and count it
	while (tmp != nullptr)
	{
		counter ++;
		tmp = tmp -> next;
	}
	return counter;

}


template<typename Object>
bool GenericQueue<Object>::isEmpty() const noexcept
{
	// If there is no Nodes, return true. Else return false.
	if (front1 == nullptr)
	{
		return true;
	}
	return false;
}

template<typename Object>
void GenericQueue<Object>::enqueue(const Object & elem)
{
	// Check if Node pointer is null. If so, create a new Node with elem. Else, Add the new Node.
	if (nullptr == front1)
	{
		Node * tmp{front1};
		front1 = new Node(elem);
		front1 -> next = tmp;
		return;
	}
	Node * tmp{front1};
	while (tmp -> next != nullptr)
	{
		tmp = tmp -> next;
	}
	tmp -> next = new Node(elem);

}


template<typename Object>
Object & GenericQueue<Object>::front()
{
	// Check if QueueOfStrings is empty. If so, throw exception. If not, return front value
	if (isEmpty())
	{
		throw QueueEmptyException{"Queue is Empty"};
	}
	return front1 -> value;
}

template<typename Object>
const Object & GenericQueue<Object>::front() const
{
	// Check if QueueOfStrings is empty. If so, throw exception. If not, return front value
	if (isEmpty())
	{
		throw QueueEmptyException{"Queue is Empty"};
	}
	return front1 -> value;
}


// does not return anything.  Just removes. 
template<typename Object>
void GenericQueue<Object>::dequeue()
{
	// First check if the Queue is empty
	if (isEmpty())
	{
		throw QueueEmptyException("Queue is Empty.");
	}
	// Move the Node pointer to the next one and delete the current Node
	Node * tmp = front1;
	front1 = front1 -> next;
	delete tmp;
}


template<typename Object>
size_t GenericQueue<Object>::TA_num() const noexcept
{
	return front1->ta_num;
}


#endif 

