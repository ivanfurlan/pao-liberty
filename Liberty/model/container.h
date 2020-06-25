#ifndef CONTAINER_H
#define CONTAINER_H

#define INCREMENT_CAPACITY 2
// TO DO: ricontrollare tutto, siccome preso dall'anno scorso

template<class T>
class Container{
    public:
        class iterator;
        class const_iterator;

        Container(int =0); // TO DO: mettere almeno =3
        Container(const Container &) = default;
        ~Container();

        bool empty() const;
        unsigned int countElements() const;

        void insertAt(const T &, const iterator ); // TO DO: non credo serva
        void insertBack(const T &);
        void insertFront(const T &);

        iterator remove(const iterator);
        iterator remove(T &);
        iterator removeFront(); // TO DO: non credo serva
        iterator removeBack(); // TO DO: non credo serva

        T& at(const int &);
        T& front();
        T& back();
        T& operator[](const int &);
        const T& at(const int &) const;
        const T& front() const;
        const T& back() const;
        const T& operator[](const int &) const;

        iterator search(const T &); // TO DO: non credo serva //non è implementata, cioè credo serva solo per poterla chiamare su oggetti non costanti, ma poi utilizzi quella sotto. DA CONTROLLARE
        iterator begin();
        iterator end();

        const_iterator search(const T &) const; // TO DO: non credo serva
        const_iterator begin() const;
        const_iterator end() const;

        class iterator{

            public:
                iterator();
                iterator(Container &, const int =0);
                iterator(const iterator &) = default;

                iterator& operator++();
                iterator operator++(int);
                iterator& operator--();
                iterator operator--(int);

                iterator& operator=(const iterator &);
                iterator operator-(const int & i);
                iterator operator+(const int & i);

                T& operator*() const;

                bool operator==(const iterator &) const;
                bool operator!=(const iterator &) const;
                bool operator>(const iterator &) const;
                bool operator<(const iterator &) const;
                bool operator>=(const iterator &) const;
                bool operator<=(const iterator &) const;

                operator const_iterator() const;

            private:
                int index;
                Container * cPtr;

        };

        class const_iterator{

            public:
                const_iterator();
                const_iterator(const const_iterator &) = default;
                const_iterator(const Container &, const int =0);

                const_iterator& operator++();
                const_iterator operator++(int);
                const_iterator& operator--();
                const_iterator operator--(int);

                const_iterator& operator=(const const_iterator &);
                const_iterator operator-(const int & i);
                const_iterator operator+(const int & i);

                const T& operator*() const;

                bool operator==(const const_iterator &) const;
                bool operator!=(const const_iterator &) const;
                bool operator>(const const_iterator &) const;
                bool operator<(const const_iterator &) const;
                bool operator>=(const const_iterator &) const;
                bool operator<=(const const_iterator &) const;


            private:
                int index;
                const Container * cPtr;

        };

    private:
        T* array;
        unsigned int used;
        unsigned int capacity;

        void resize();
        void resize(unsigned int);
        void copyArray(const T*, T*) const;

        /*
            void rightShift(iterator, int =1);
            void leftShift(iterator, int =1);
         */
};

/*
 * IMPLEMENTAZIONE METODI DEL TEMPLATE
 * */

template <typename T>
Container<T>::Container(int size)
{
    used = 0;
    capacity = size;
    array = nullptr;
    resize(size);
}

template<class T>
Container<T>::~Container()
{
    delete[] this->array;
}

template <typename T>
void Container<T>::resize()
{
    resize((used>0) ? (used + INCREMENT_CAPACITY) : 1); // Se non utilizzato creo un arrai solo di 1, altrimenti l'array è lungo INCREMENT_CAPACITY più delle celle utilizzate
}

template <typename T>
void Container<T>::resize(unsigned int newSize)
{
    // TO DO: if(newSize < used) throw;
    T* newArray = new T[newSize]; // creo un nuovo array
    copyArray(array, newArray); // copio il vecchio array nel nuovo
    delete[] array; // cancello il vecchio array
    array = newArray; // aggiorno il puntatore
    capacity = newSize; // aggiorno la capacità
}

template <typename T>
void Container<T>::copyArray(const T* fromArray, T* toArray) const
{
    for(unsigned int x = 0; x<used; x++) toArray[x] = fromArray[x]; // copio solo la parte utilizzata del vecchio array nel nuovo
}

template <typename T>
void Container<T>::insertBack(const T & value)
{
    insertAt(value, end());
}

template <typename T>
void Container<T>::insertFront(const T & value)
{
    insertAt(value, begin());
}

template <typename T>
void Container<T>::insertAt(const T & value, const iterator it)
{
    if(used==capacity){
        resize();
    }

    for(auto x = end(); x>it; x--){ // sposto gli elementi a destra per liberare la cella dove devo fare l'inserimento
        *x = *(x-1);
    }
    used++;
    *it=value; // inserisco il valore
}

template <typename T>
typename Container<T>::iterator Container<T>::remove(T & value)
{
    return remove(search(value));
}

template <typename T>
typename Container<T>::iterator Container<T>::removeFront()
{
    return remove(begin());
}

template <typename T>
typename Container<T>::iterator Container<T>::removeBack()
{
    return remove(--end());
}

template <typename T>
typename Container<T>::iterator Container<T>::remove(const iterator it)
{
    // TO DO: if(it>=end()) throw;
    iterator temp = it;
    iterator deleted = it;
    while(temp<end()){
        *temp = *(temp++);
    }
    used--;
    if(used <= capacity-INCREMENT_CAPACITY*1.5) resize();
    return deleted;
}

template <typename T>
T& Container<T>::at(const int & index)
{
    return array[index];
}

template <typename T>
T& Container<T>::front(){
    // TO DO: if(used==0)throw;
    return array[0];
}

template <typename T>
T& Container<T>::back()
{
    // TO DO: if(used==0)throw;
    return array[used];
}

template <typename T>
T& Container<T>::operator[](const int & index)
{
    return array[index];
}

template <typename T>
const T& Container<T>::at(const int & index)const
{
    return array[index];
}

template <typename T>
const T& Container<T>::front()const
{
    // TO DO: if(used==0)throw;
    return array[0];
}

template <typename T>
const T& Container<T>::back()const
{
    // TO DO: if(used==0)throw;
    return array[used];
}

template <typename T>
const T& Container<T>::operator[](const int & index) const
{
    return array[index];
}

template <typename T>
typename Container<T>::const_iterator Container<T>::search(const T & value) const // TO DO: credo si possa ritornate iterator, poi nel caso c'è la conversione a const_iterator
{
    for(const_iterator it = begin(); it<end(); ++it){ // scorro e cerco l'elemento
        if(*it == value)
            return it;
    }
    return const_iterator();
}

template <typename T>
bool Container<T>::empty() const
{
    return !(used>0);
}

template<class T>
unsigned int Container<T>::countElements() const
{
    return used;
}

template <typename T>
typename Container<T>::iterator Container<T>::begin()
{
    return iterator(*this, 0);
}

template <typename T>
typename Container<T>::iterator Container<T>::end()
{
    return iterator(*this, used);
}

template <typename T>
typename Container<T>::const_iterator Container<T>::begin() const
{
    return const_iterator(*this, 0);
}

template <typename T>
typename Container<T>::const_iterator Container<T>::end() const
{
    return const_iterator(*this, used);
}

/*
 * IMPLEMENTAZIONE METODI DI ITERATOR
 * */
template<typename T>
Container<T>::iterator::operator const_iterator() const
{
    return const_iterator(*cPtr,index);
}

template <typename T>
Container<T>::iterator::iterator()
{
    cPtr = nullptr;
    index = 0;
}

template <typename T>
Container<T>::iterator::iterator(Container<T> & c, const int i) : cPtr(&c), index(i)
{

}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator++()
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    index++;
    return *this;
}

template <typename T>
typename Container<T>::iterator Container<T>::iterator::operator++(int)
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    iterator oldIterator = *this;
    index++;
    return oldIterator;
}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator--()
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    index--;
    return *this;
}

template <typename T>
typename Container<T>::iterator Container<T>::iterator::operator--(int)
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    iterator oldIterator = *this;
    index--;
    return oldIterator;
}

template <typename T>
typename Container<T>::iterator& Container<T>::iterator::operator=(const iterator & it)
{
    cPtr = it.cPtr;
    index = it.index;
    return *this;
}

template <typename T>
typename Container<T>::iterator Container<T>::iterator::operator-(const int & i)
{
    return iterator(*cPtr, index - i);
}

template <typename T>
typename Container<T>::iterator Container<T>::iterator::operator+(const int & i)
{
    return iterator(*cPtr, index + i);
}

template <typename T>
T& Container<T>::iterator::operator*() const
{
    return (*cPtr).at(index); // deferienzo il puntatore al container, ed uso il metodo at per accedere alla cella in posizione index (che è un campo dati dell'iteratore, cioè dell'oggetto *this)
}

template<typename T>
bool Container<T>::iterator::operator<(const iterator & it) const
{
    return index<it.index;
}

template<typename T>
bool Container<T>::iterator::operator>(const iterator & it) const
{
    return index>it.index;
}

template<typename T>
bool Container<T>::iterator::operator==(const iterator & it) const
{
    return index==it.index;
}

/*
 * IMPLEMENTAZIONE METODI DI CONST_ITERATOR
 * */
template <typename T>
Container<T>::const_iterator::const_iterator(const Container<T> & c, int i) : cPtr(&c), index(i)
{

}

template <typename T>
const T& Container<T>::const_iterator::operator*() const
{
    return (*cPtr).at(index); // deferienzo il puntatore al container, ed uso il metodo at per accedere alla cella in posizione index (che è un campo dati dell'iteratore, cioè dell'oggetto *this)
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++()
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    index++;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int)
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    const_iterator oldIterator = *this;
    index++;
    return oldIterator;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--()
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    index--;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int)
{
    // TO DO: controllare limiti inferiori e superiori dell'array
    const_iterator oldIterator = *this;
    index--;
    return oldIterator;
}

template <typename T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator=(const const_iterator & i)
{
    cPtr = i.cPtr;
    index = i.index;
    return *this;
}

template <typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator-(const int & i)
{
    return const_iterator(*cPtr, index-i);
}

template <typename T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator+(const int & i)
{
    return const_iterator(*cPtr, index+i);
}

template<typename T>
bool Container<T>::const_iterator::operator<(const const_iterator & it) const
{
    return index < it.index;
}

template<typename T>
bool Container<T>::const_iterator::operator>(const const_iterator & it) const
{
    return index > it.index;
}

template<typename T>
bool Container<T>::const_iterator::operator==(const const_iterator & it) const
{
    return index == it.index;
}

#endif // CONTAINER_H