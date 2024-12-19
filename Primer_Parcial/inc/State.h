
class Context; 

#ifndef STATE_H
#define STATE_H
class State{
    protected:
       Context* contexto;
    public:
        void setContext(Context* ctx) {
            contexto = ctx;
        }   
        virtual void validarExpresion(char c) = 0;

};
#endif 
