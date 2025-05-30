#include <iostream>
#include "lab1.h"

//
//

Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef) {
	_data = new ValueType[size];
	for (size_t i = 0; i < size; i++) {
		_data[i] = rawArray[i];
	}
}

Vector::Vector(const Vector& other) : _data(nullptr), _size(other._size), _multiplicativeCoef(other._multiplicativeCoef), _capacity(other._size) {}

Vector& Vector::operator=(const Vector& other) {
	
	if (&other == this) {
		return *this;
	}

	this->_size = other._size; 
	this->_multiplicativeCoef = other._multiplicativeCoef;
	this->_capacity = other._capacity;
	
	_data = new ValueType[_size];
        for (size_t i = 0; i < _size; i++) {
                _data[i] = other._data[i];
        }

	return *this;

}

Vector::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef) { 
	
	if (&other != this) {
		other._data = nullptr;
		other._capacity = 0;
		other._size = 0;
	}
}

Vector& Vector::operator=(Vector&& other) noexcept {

	if (_data == other._data) {
		return *this;
	}
	this->_size = other._size;
	this->_capacity = other._capacity;
	delete[] _data;
	this->_data = other._data;

	other._data == nullptr;
	other._size = 0;
	other._capacity = 0;
	
	return *this;

}

Vector::~Vector() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

void Vector::pushBack(const ValueType& value) {
	if (_capacity > _size) {
		_data[_size] = value;
	}
	else {
		if (_capacity == 0) {_capacity = _multiplicativeCoef;}
		else {
			_capacity = _capacity * _multiplicativeCoef;
		}
		ValueType *temp = new ValueType[_capacity];
		for (size_t i = 0; i < _size; i++) {
			temp[i] = _data[i];
		}
		temp[_size] = value;
		delete[] _data;
		_data = temp;
	}

	_size++;
}

void Vector::pushFront(const ValueType& value) {
        if (_capacity > _size) {
                for (size_t i = 0; i < _size; i++) {
                        _data[i + 1] = _data[i];
                }
		_data[0] = value;
        }
        else {
		if (_capacity == 0) {_capacity = _multiplicativeCoef;}
                else {
                        _capacity = _capacity * _multiplicativeCoef;
                }
		ValueType *temp = new ValueType[_capacity];
        	for (size_t i = 0; i < _size; i++) {
                	temp[i + 1] = _data[i];
        	}
		temp[0] = value;
        	delete[] _data;
        	_data = temp;
	}
        _size++;
}

void Vector::insert(const ValueType& value, size_t pos) {
	if (pos > _size || _size == 0) {return;}
	if (_capacity <= _size) {
                _capacity = _capacity*_multiplicativeCoef;
	}
	ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < pos; i++) {
                temp[i] = _data[i];
        }
	temp[pos] = value;
	for (size_t i = pos; i < _size; i++) {
		temp[i + 1] = _data[i];
	}
	delete[] _data; 
	_data = temp;
	_size++;

}

void Vector::insert(const ValueType* values, size_t size, size_t pos) {
	if (pos > _size || _size == 0) { return; }
	while (_capacity < _size + size) {
                _capacity = _capacity * _multiplicativeCoef;
        }
	ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < pos; i++) {
                temp[i] = _data[i];
        }
        for (size_t i = 0; i < size; i++) {
		temp[i + pos] = values[i];
	}
        for (size_t i = pos; i < _size; i++) {
                temp[i + size + pos] = _data[i];
        }
        delete[] _data;
        _data = temp;
	_size += size;

}

void Vector::insert(const Vector& vector, size_t pos) {
        if (pos > _size || _size == 0) {return;}
	while (_capacity < _size + vector._size) {
                _capacity = _capacity * _multiplicativeCoef;
        }
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < pos; i++) {
                temp[i] = _data[i];
        }
        for (size_t i = 0; i < vector._size; i++) {
                temp[i + pos] = vector._data[i];
        }
        for (size_t i = pos; i < _size; i++) {
                temp[i + vector._size + pos] = _data[i];
        }
        delete[] _data;
        _data = temp;
        _size += vector._size;
}


void Vector::popBack(){ 
    if (_size == 0) {return;}
    _size--;
}

void Vector::popFront(){
    if (_size == 0) {return;}
    for (size_t i = 0; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

void Vector::erase(size_t pos, size_t count) {
    if (pos + count > _size) {
	if (pos > _size) {return;}
    }
    else {
        ValueType *temp = new ValueType[_capacity];
        for (size_t i = 0; i < pos; i++) {
            temp[i] = _data[i];
    	}
	for (size_t i = pos + count; i < _size; i++) {
	    temp[i - count] = _data[i];
	}
        delete[] _data;
        _data = temp;
        _size-=count;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (endPos > _size) {
        _size = beginPos;
        }
    else {
        for (size_t i = beginPos; i < _size - (endPos - beginPos); i++) {
            _data[i] = _data[i + endPos];
        }
        _size -= (endPos - beginPos);
    }
}


size_t Vector::size() const{ 
	return _size; 
}
size_t Vector::capacity() const{ 
	return _capacity; 
}
double Vector::loadFactor() const{ 
	return static_cast<double>(_size)/static_cast<double>(_capacity); 
}

ValueType& Vector::operator[](size_t idx) {
	return _data[idx];
}
const ValueType& Vector::operator[](size_t idx) const {
	return _data[idx];
}

long long Vector::find(const ValueType& value) const {
	for (size_t i = 0; i < _size; i++) {
		if (_data[i] == value) {
			return i;
		}
	}
	return -1;
}

void Vector::reserve(size_t capacity) {
	if (capacity > _capacity) {
		ValueType *temp = new ValueType[capacity];
		for (size_t i = 0; i < _size; i++) {
			temp[i] = _data[i];
		}
		delete[] _data;
		_data = temp;
	}
	else {return;}
}

void Vector::shrinkToFit() {
	if (_capacity == _size) {return;}
	ValueType *temp = new ValueType[_size];
        for (size_t i = 0; i < _size; i++) {
        	temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
	_capacity = _size;
}

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*() {
	return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const {
	return *_ptr;
}

ValueType* Vector::Iterator::operator->() {
	return _ptr;
}

const ValueType* Vector::Iterator::operator->() const {
	return _ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
	_ptr++;
	return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
	Iterator temp = *this;
	_ptr++;
	return temp;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
	return (_ptr == other._ptr);
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
        return (_ptr != other._ptr);
}

Vector::Iterator Vector::begin() {
	Iterator itr(&_data[0]);
	return itr;
}

Vector::Iterator Vector::end() {
	Iterator itr(&_data[_size]);
	return itr;
}


