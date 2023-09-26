#pragma once

class Nodo {
  public:
    Nodo(const int kNumeroNodo, const double kDistancia, Nodo* kPadre) : numero_nodo_{kNumeroNodo}, distancia_{kDistancia}, padre_{kPadre} {};
    Nodo* GetPadre() const {return padre_;}
    Nodo*& GetPadre() {return padre_;}
    int GetNumero() const {return numero_nodo_;};
    int& GetNumero() {return numero_nodo_;}
    double GetDistancia() const {return distancia_;}
    double& GetDistancia() {return distancia_;}
    bool NodoEnRama(const int) const;
    ~Nodo() {}
  private:
    int numero_nodo_;
    double distancia_;
    Nodo* padre_{nullptr};
    
};