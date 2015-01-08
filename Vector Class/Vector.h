template <class T>
class Vector
{
public:
	Vector() : data(NULL) {} //Constructor
	~Vector() {} //Destructor
	Vector(const Vector<T> & lhs); //Copy constructor
	bool empty();
	int size();
	int capacity();
	void clear();
	void push_back();
	void begin(); //TODO: not void
	void end(); //TODO: not void
private:
	T * data;
	int array_size;
};