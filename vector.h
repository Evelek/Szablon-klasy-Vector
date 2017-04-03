#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
#include <new>
#include <iterator>
#include <algorithm>
#include <functional>

template <class Type>
class Vector {
	Type *tab;
	size_t rozmiar;
public:
	Vector();
	void dodaj_element(const Type &wartosc);
	void usun_element();
	void wyswietl_vector() const;
	size_t zwroc_rozmiar() const;
	void wyczysc_vector();
	void sortowanie_rosnaco();
	void sortowanie_malejaco();
};

template<class Type>
Vector<Type>::Vector()
{
	tab = new Type[1];
	rozmiar = 0;
}

template<class Type>
void Vector<Type>::dodaj_element(const Type &wartosc) {
	Type *tablica_tymczasowa = new Type[rozmiar]; //utworzenie tymczasowej tablicy dynamicznej
	for (size_t i = 0; i < rozmiar; i++)
		tablica_tymczasowa[i] = tab[i];  //skopiowanie wartosci z glownej tablicy do tymczasowej
	delete[] tab; //dealokacja pamieci tablicy glownej
	tab = new Type[rozmiar + 1]; //alokacja pamieci nowej powiekszonej glownej tablicy
	for (size_t i = 0; i < rozmiar; i++)
		tab[i] = tablica_tymczasowa[i];  //skopiowanie wartosci z tablicy tymczasowej do glownej
	tab[rozmiar] = wartosc; //dodanie elementu do glownej tablicy
	rozmiar++;
	delete[] tablica_tymczasowa; //dealokacja pamieci tablicy tymczasowej
}

template<class Type>
void Vector<Type>::usun_element() {
	rozmiar--;
	Type *tablica_tymczasowa = new Type[rozmiar]; //utworzenie tymczasowej tablicy dynamicznej
	for (size_t i = 0; i < rozmiar; i++)
		tablica_tymczasowa[i] = tab[i];  //skopiowanie wartosci z glownej tablicy do tymczasowej bez ostatniego elementu
	tab = new (tab) Type[rozmiar]; //miejscowa wersja new
	for (size_t i = 0; i < rozmiar; i++)
		tab[i] = tablica_tymczasowa[i];  //skopiowanie wartosci z tablicy tymczasowej do glownej
	delete[] tablica_tymczasowa; //dealokacja pamieci tablicy tymczasowej
}

template<class Type>
void Vector<Type>::wyswietl_vector() const {
	for (size_t i = 0; i < rozmiar; ++i)
		std::cout << tab[i] << " ";
}

template<class Type>
size_t Vector<Type>::zwroc_rozmiar() const {
	return rozmiar;
}

template<class Type>
void Vector<Type>::wyczysc_vector() {
	delete[] tab;
	rozmiar = 0;
}

template<class Type>
void Vector<Type>::sortowanie_rosnaco()
{
	std::sort(tab, tab + rozmiar, std::less<Type>());
}

template<class Type>
void Vector<Type>::sortowanie_malejaco()
{
	std::sort(tab, tab + rozmiar, std::greater<Type>());
}

#endif // !VECTOR_H_
