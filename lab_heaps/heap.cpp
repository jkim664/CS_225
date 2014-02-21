/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {					//Done

	return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {		//Done

	return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {	//Done
    
	return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {		//Done
    
	return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {		//Done

	return ( leftChild(currentIdx) < _elems.size() );
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {	//Done

	if ( rightChild(currentIdx) < _elems.size() && higherPriority( _elems[rightChild(currentIdx)], _elems[leftChild(currentIdx)] ) ) {
		
    		return rightChild(currentIdx);												
    				
    	}
    	
    	else return leftChild(currentIdx);
    	
	
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {		//Done
	
	if ( hasAChild(currentIdx) ) {
	
		size_t minChildIdx = maxPriorityChild(currentIdx);
	
	
		if (higherPriority(_elems[minChildIdx], _elems[currentIdx]) ) {
		
			std::swap(_elems[currentIdx], _elems[minChildIdx]);
			heapifyDown(minChildIdx);
		}
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {

	_elems.push_back( T() );
	
	
    	
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {

	_elems.push_back( T() );
	
	for (int i = 0; i < elems.size(); i++) {
	
		_elems.push_back(elems[i]);
		
	}
	
	for (int i = parent(_elems.size()-1); i > 0; i--) {
	
		heapifyDown(i);
	
	}
	
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    	
    	T temp = peek();
    	
	std::swap(_elems[1], _elems[_elems.size() - 1] );
	_elems.pop_back();
	heapifyDown(1);
	
	return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    	
	return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    	
    	_elems.push_back(elem);
    	heapifyUp(_elems.size()-1);
    	
    	
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    	
    	return (_elems.size() <= 1);
}
