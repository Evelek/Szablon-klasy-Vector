#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include <new>
#include <iterator>
#include <algorithm>
#include <functional>

namespace vec {
	template <class Type>
	class Vector {
	private:
		Type *main_vector;
		size_t vector_size;
		size_t capacity;
	public:
		Vector();							// Vector <Type> object;
		explicit Vector(const size_t vector_size);			// Vector <Type> object(size_t);
		Vector(const Vector<Type> &copy_ctor);				// Vector <Type> new_object(const Vector &);
		Vector(Vector<Type> &&move_ctor);				// Vector <Type> new_object(Vector &&);
		Vector<Type> &operator=(const Vector<Type> &copy);		// Vector <Type> new_object = object;
		Vector<Type> &operator=(Vector<Type> &&move_copy);		// object_two = std::move(object_one);
		~Vector();

		Type & operator[](size_t element_number);
		const Type & operator[](size_t element_number) const;

		void add_new_element(const Type &value);
		void remove_element();
		void show_vector() const;
		size_t size() const;
		void reset_vector();
		void sort_ascending();
		void sort_descending();
	};
	template<class Type>
	Vector<Type>::Vector() {
		capacity = 10;
		main_vector = new Type[capacity];
		vector_size = 0;
		for (size_t i = 0; i < capacity; ++i)
			main_vector[i] = 0;
	}

	template<class Type>
	Vector<Type>::Vector(const size_t vector_size) {
		capacity = (((vector_size + 9) / 10) * 10); //round to multiple of 10
		main_vector = new Type[capacity];
		this->vector_size = vector_size;
		for (size_t i = 0; i < vector_size; ++i)
			main_vector[i] = 0;
	}

	template<class Type>
	Vector<Type>::Vector(const Vector<Type> &copy_ctor) {
		capacity = copy_ctor.capacity;
		vector_size = copy_ctor.vector_size;
		main_vector = new Type[capacity];
		for (size_t i = 0; i < vector_size; ++i)
			main_vector[i] = std::move(copy_ctor.main_vector[i]);
	}

	template<class Type>
	Vector<Type>::Vector(Vector<Type> &&move_ctor) {
		vector_size = move_ctor.vector_size;
		capacity = move_ctor.capacity;
		main_vector = move_ctor.main_vector;
		move_ctor.vector_size = 0;
		move_ctor.capacity = 0;
		move_ctor.main_vector = nullptr;
	}

	template<class Type>
	Vector<Type> & Vector<Type>::operator=(const Vector<Type> &copy) {
		if (this == &copy)
			return *this;

		delete[] main_vector;
		capacity = copy.capacity;
		vector_size = copy.vector_size;
		main_vector = new Type[capacity];
		for (size_t i = 0; i < vector_size; ++i)
			main_vector[i] = std::move(copy.main_vector[i]);
		return *this;
	}

	template<class Type>
	Vector<Type>& Vector<Type>::operator=(Vector<Type>&& move_copy) {
		if (this == &move_copy)
			return *this;
		delete[] main_vector;

		vector_size = move_copy.vector_size;
		capacity = move_copy.capacity;
		main_vector = move_copy.main_vector;
		move_copy.vector_size = 0;
		move_copy.capacity = 0;
		move_copy.main_vector = nullptr;
		return *this;
	}

	template<class Type>
	Vector<Type>::~Vector() {
		delete[] main_vector;
	}

	template<class Type>
	Type & Vector<Type>::operator[](size_t element_number) {
		return main_vector[element_number];
	}

	template<class Type>
	const Type & Vector<Type>::operator[](size_t element_number) const {
		return main_vector[element_number];
	}

	template<class Type>
	void Vector<Type>::add_new_element(const Type &value) {
		if (vector_size < capacity) {
			main_vector[vector_size] = value;
			vector_size++;
		}
		else {
			/* Description:
			1) Alocate memory for temp_copy_vector
			2) Copy elements from main_vector to temp_copy_vector
			3) Dealocate main_vector's memory
			4) Alocate new memory for main_vector
			5) Increase capacity by 10
			6) Copy elements from temp_copy_vector to main_vector
			7) Dealocate temp_copy_vector's memory
			*/

			capacity += 10; //increase capacity by 10

			Type *temp_copy_vector = new Type[vector_size]; //alocate memory for temp_copy_vector which is destination for copying elements from main_vector
			Type *pointer = &main_vector[vector_size]; //point one-past-the-end element of main_vector
			size_t pointer_moves = 0; //variable counts temp_copy_vector's and main_vector's moves during copying elements

									  //copy elements from main_vector to temp_copy_vector
			while (main_vector != pointer) {
				*temp_copy_vector++ = std::move(*main_vector++);
				pointer_moves++;
			};
			pointer = &temp_copy_vector[0]; //point the last element of temp_copy_vector

											//move back main_vector and temp_copy_vector on initial position
			for (size_t i = 0; i < pointer_moves; ++i) {
				main_vector--;
				temp_copy_vector--;
			}

			delete[] main_vector; //dealocate main_vector's memory

			vector_size++;
			main_vector = new Type[capacity]; //alocate memory for main_vector

											  //copy elements from temp_copy_vector to main_vector
			while (temp_copy_vector != pointer) {
				*main_vector++ = std::move(*temp_copy_vector++);
			}

			main_vector[0] = value; //add element to the main_vector

									//move back main_vector and temp_copy_vector on initial position
			for (size_t i = 0; i < pointer_moves; ++i) {
				main_vector--;
				temp_copy_vector--;
			}

			delete[] temp_copy_vector; //dealocate temp_copy_vector's memory
		}
	}

	template<class Type>
	void Vector<Type>::remove_element() {
		if (vector_size < capacity) { //if vector_size is smaller than capacity
			vector_size--;
			main_vector[vector_size] = 0;
			if (vector_size % 10 == 0 && capacity != 10)
				capacity -= 10;
		}
		else {
			/* Description:
			1) Alocate memory for temp_copy_vector
			2) Copy elements from main_vector to temp_copy_vector
			3) Dealocate main_vector's memory
			4) Alocate new memory for main_vector
			5) Increase capacity by 10
			6) Copy elements from temp_copy_vector to main_vector
			7) Dealocate temp_copy_vector's memory
			*/

			vector_size--;  //reduction vector_size by one

			Type *temp_copy_vector = new Type[vector_size]; //alocate memory for temp_copy_vector which is destination for copying elements from main_vector
			Type *pointer = &main_vector[vector_size]; //point one-past-the-end element of main_vector
			size_t pointer_moves = 0; //variable counts temp_copy_vector's and main_vector's moves during copying elements

									  //copy elements from main_vector to temp_copy_vector
			while (main_vector != pointer) {
				*temp_copy_vector++ = std::move(*main_vector++);
				pointer_moves++;
			}
			pointer = &temp_copy_vector[0]; //point the last element of temp_copy_vector

											//move back main_vector and temp_copy_vector on initial position
			for (size_t i = 0; i < pointer_moves; ++i) {
				main_vector--;
				temp_copy_vector--;
			}

			main_vector = new (main_vector)Type[vector_size]; //placement new

															  //copy elements from temp_copy_vector to main_vector
			while (temp_copy_vector != pointer) {
				*main_vector++ = std::move(*temp_copy_vector++);
			}

			//move back main_vector and temp_copy_vector on initial position
			for (size_t i = 0; i < pointer_moves; ++i) {
				main_vector--;
				temp_copy_vector--;
			}

			delete[] temp_copy_vector; //dealocate temp_copy_vector's memory
		}
	}

	template<class Type>
	void Vector<Type>::show_vector() const {
		for (size_t i = 0; i < vector_size; ++i)
			std::cout << main_vector[i] << " ";
	}

	template<class Type>
	size_t Vector<Type>::size() const {
		return vector_size;
	}

	template<class Type>
	void Vector<Type>::reset_vector() {
		delete[] main_vector;
		capacity = 10;
		vector_size = 0;
		main_vector = new Type[capacity];
	}

	template<class Type>
	void Vector<Type>::sort_ascending() {
		std::sort(main_vector, main_vector + vector_size, std::less<Type>());
	}

	template<class Type>
	void Vector<Type>::sort_descending() {
		std::sort(main_vector, main_vector + vector_size, std::greater<Type>());
	}
}
#endif // !VECTOR_H_
