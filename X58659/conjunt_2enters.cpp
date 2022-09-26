#include "conjunt_2enters.hpp"

//--- Constructor => crea conjunt buit
cj_2enters::cj_2enters(){
    _size = 0; 
}

//--- Constructor => crea un conjunt a partir d'altre
cj_2enters::cj_2enters(const cj_2enters &cj){
    _size = cj._size;
    for(int i = 0; i < cj._size; i++){
        _cnj[i] = cj._cnj[i];
    }
}

//--- Operador de asignació
cj_2enters& cj_2enters::operator=(const cj_2enters &cj){
    _size = cj._size;
    for(int i = 0; i < cj._size; i++){
        _cnj[i] = cj._cnj[i];
    }
    return *this;
}

cj_2enters::~cj_2enters(){}

// Retorna cert si i només si pe pertany al conjunt.
bool cj_2enters::conte(pair<int, int> pe) const{
    for(int i = 0; i < _size; i++){
        if(pe == _cnj[i]) return true; 
    }
    return false; 
    /* int mid, inf = 0, sup = _size-1; 
    while(inf <= sup){
        mid = (sup+inf) / 2; 
        if(_cnj[mid] == pe) return true; 
        else if(pe < _cnj[mid]) sup = mid - 1; 
        else inf = mid + 1; 
    }
    return false;  */
}

// Retorna el nombre d'elements (la cardinalitat) del conjunt.
int cj_2enters::card() const{
    return _size;
}

// Operadors relacionals. == retorna cert si i només si els dos conjunts
// (el paràmetre implícit i B) contenen els mateixos elements;
bool cj_2enters::operator==(const cj_2enters& B) const{
    if(_size == B._size){
        for(int i = 0; i < _size; i++){
            if(_cnj[i] != B._cnj[i]) return false; 
        }
    }else return false;
    
    return true; 
}

// != retorna cert si i només si els conjunts són diferents.
bool cj_2enters::operator!=(const cj_2enters& B) const{
    if(_size == B._size){
        for(int i = 0; i < _size; i++){
            if(_cnj[i] != B._cnj[i]) return true; 
        }
    }else return true;
    
    return false; 
}



// Insereix la parella d'enters pe en el conjunt. No fa res si pe ja pertanyia al conjunt.
void cj_2enters::insereix(pair<int, int> pe){
    if(!this->conte(pe)){
        if(_size == 0) _cnj[0] = pe; 
        for(int i = _size; i > 0; i--){
            if(pe > _cnj[i-1]){
                _cnj[i] = pe;
                break;
            }else{
                _cnj[i] = _cnj[i-1];
                _cnj[i-1] = pe;
            }
        }
        _size++;
    } 
}

// Unió, intersecció i diferència de conjunts. Operen creant un nou conjunt sense 
void cj_2enters::unir(const cj_2enters& B){
    int i = 0, j = 0;
    cj_2enters aux;
    while(i < _size or j < B._size){
        if(i >= _size){
            aux._cnj[aux._size] = B._cnj[j];
            aux._size++;
            j++;
        }else if(j >= B._size){
            aux._cnj[aux._size] = _cnj[i];
            aux._size++;
            i++;
        }
        else if(_cnj[i] == B._cnj[j]){
            aux._cnj[aux._size] = _cnj[i];
            aux._size++;
            i++;
            j++;
        }else if(_cnj[i] > B._cnj[j]){
            aux._cnj[aux._size] = B._cnj[j];
            j++;
            aux._size++;
        }else if(_cnj[i] < B._cnj[j]){
            aux._cnj[aux._size] = _cnj[i];
            i++;
            aux._size++;
        }
    }
    *this = aux; 
}

void cj_2enters::intersectar(const cj_2enters& B){
    cj_2enters cj_aux;
    int i = 0, j = 0;
    while(i < _size and j < B._size){
        if(_cnj[i] == B._cnj[j]){
            cj_aux._cnj[cj_aux._size] = _cnj[i];
            i++; j++; cj_aux._size++;
        }else if(_cnj[i] > B._cnj[j]) j++;
        else i++;
    }
    *this = cj_aux;
}

void cj_2enters::restar(const cj_2enters& B){
    cj_2enters cj_aux; 
    int i = 0, j = 0;
    while(i < _size){
        if(j >= B._size){
            cj_aux._cnj[cj_aux._size] = _cnj[i];
            i++;
            cj_aux._size++;
        }
        else if(_cnj[i] < B._cnj[j]){
            cj_aux._cnj[cj_aux._size] = _cnj[i];
            i++; 
            cj_aux._size++;
        }else if(_cnj[i] > B._cnj[j]){
            j++;
        }else{
            j++;
            i++;
        }
    }
    *this = cj_aux;                 
}

cj_2enters cj_2enters::operator+(const cj_2enters& B) const{
    cj_2enters cj_aux(*this);
    
    cj_aux.unir(B);

    return cj_aux; 
}
cj_2enters cj_2enters::operator*(const cj_2enters& B) const{
    cj_2enters cj_aux(*this);
    
    cj_aux.intersectar(B);

    return cj_aux; 
}
cj_2enters cj_2enters::operator-(const cj_2enters& B) const{
    cj_2enters cj_aux(*this);
    
    cj_aux.restar(B);

    return cj_aux; 
}

void cj_2enters::print(ostream& os) const{
    os << "[";
    for(int i = 0; i < _size; i++){
        if(i != 0) os << " ";
        os << _cnj[i].first << "," << _cnj[i].second;
    }
    os << "]";
}

pair<int, int> cj_2enters::min() const{ 
    return _cnj[0];
}

pair<int, int> cj_2enters::max() const {
    return _cnj[_size - 1];
}