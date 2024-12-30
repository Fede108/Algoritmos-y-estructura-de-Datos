
class Context; 

#ifndef STATE_H
#define STATE_H
class State{
    protected:
       Context* contexto;
       string expresion;
    public:
        void setContext(Context* ctx) {
            contexto = ctx;
        }   
        Context* getContext(){return contexto;}
        virtual bool validarExpresion(char c) = 0;
        virtual string print() = 0;
}; 
#endif 
