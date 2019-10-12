#pragma once


template <typename T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* prev;
};


template <typename T>
class DoublyLinkedList
{
private:
	Node<T>*head;
	Node<T>*tail;


public:
	DoublyLinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	void reverse()
	{
		Node<T>*curr = this->head;
		Node<T>*prev = nullptr;

		while (curr != nullptr)
		{
			swap(curr->next, curr->prev);
			curr = curr->prev;
		}

		swap(this->head, this->tail);
	}

	DoublyLinkedList(DoublyLinkedList<T>  const & list) :DoublyLinkedList()
	{
		Node<T> *curr = list.head;
		if (curr == nullptr)
			return;


		Node<T>* prevNewNode = nullptr;
		Node<T>* newNode = new Node<T>;
		newNode->data = curr->data;
		newNode->prev = prevNewNode;
		prevNewNode = newNode;
		curr = curr->next;
		this->head = newNode;

		while (curr != nullptr)
		{
			newNode = new Node<T>;
			newNode->data = curr->data;
			newNode->prev = prevNewNode;
			prevNewNode->next = newNode;
			prevNewNode = newNode;
			curr = curr->next;
		}
		this->tail = prevNewNode;
		this->tail->next = nullptr;
	}


	void deleteAtTail()
	{
		if (this->tail == nullptr)
			return;

		else if (this->head->next == nullptr)
		{
			delete this->tail;
			this->head = this->tail = nullptr;
		}

		else
		{
			Node<T>*deleteNode = this->tail;
			this->tail = this->tail->prev;
			this->tail->next = nullptr;
			delete deleteNode;
		}

	}

	void deleteAtStart()
	{
		if (this->head == nullptr)
			return;

		Node<T> *deleteNode = this->head;

		if (this->head->next == nullptr)
		{
			delete deleteNode;
			this->tail = this->head = nullptr;
			return;
		}

		this->head = this->head->next;
		this->head->prev = nullptr;
		delete deleteNode;

	}

	void insertAtTail(T const data)
	{
		if (this->tail == nullptr)
		{
			this->tail = new Node<T>();
			this->tail->data = data;
			this->tail->next = this->tail->prev = nullptr;
			this->head = this->tail;
		}
		else
		{
			Node<T> *newTail = new Node<T>();
			newTail->data = data;
			newTail->prev = tail;
			newTail->next = nullptr;
			this->tail->next = newTail;
			this->tail = newTail;
		}
	}

	void insertAtHead(T const data)
	{
		if (this->head == nullptr)
		{
			this->head = new Node<T>();
			this->head->data = data;
			this->head->next = nullptr;
			this->head->prev = nullptr;
			this->tail = this->head;
		}

		else
		{
			Node<T> *newHead = new Node<T>();
			newHead->data = data;
			newHead->next = this->head;
			newHead->prev = nullptr;
			this->head->prev = newHead;
			this->head = newHead;
		}
	}

	void print() const
	{
		Node<T> *curr = this->head;
		while (curr != nullptr)
		{
			cout << curr->data << ", ";
			curr = curr->next;
		}
	}
	
	void removeDuplicates()
	{
		if (this->head == nullptr)
			return;

		if (this->head->next == nullptr)
			return;

		Node<T>*outerPtr = this->head;

		while (outerPtr != nullptr)
		{
			Node<T>* innerPtr = outerPtr->next;

			//innerPtr moves from the next node of outerPtr
			while (innerPtr != nullptr)
			{
				if (innerPtr->data == outerPtr->data)
				{
					Node<T>*deleteNode = innerPtr;
					innerPtr->prev->next = innerPtr->next;
					
					//if the node to be deleted is not the last node, then change the prev of the next node.
					if (innerPtr->next!=nullptr)
					innerPtr->next->prev = innerPtr->prev;

					innerPtr = innerPtr->next;
					delete deleteNode;
				}
				else innerPtr = innerPtr->next;
			}

			
			outerPtr = outerPtr->next;
		}
	}

	void deleteAll()
	{
		Node<T> *curr = this->head;

		while (curr != nullptr)
		{
			Node<T> *deleteNode = curr;
			curr = curr->next;
			delete deleteNode;

			this->head = this->tail = nullptr;
		}
	}
	~DoublyLinkedList()
	{

		deleteAll();
	}
};