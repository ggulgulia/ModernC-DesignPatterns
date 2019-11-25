#include <iostream>

class LightSwitch;
struct State{
    virtual void on(LightSwitch* ls){
        std::cout << "Light is already on\n";
    }

    virtual void off(LightSwitch* ls){
        std::cout << "Light is already off\n";
    }

    virtual ~State() = default;
        
};

struct OnState : public State{

    virtual ~OnState() = default;
  OnState(){
    std::cout << "Light is turned on\n";
  }

  void off(LightSwitch* ls) override;
};

struct OffState : public State{
    virtual ~OffState() = default;
    OffState(){
        std::cout << "Light is turned off\n";
    }

    void on(LightSwitch* ls) override;
        
};

class LightSwitch{
    private:
        State* state_;
    public:
        LightSwitch(){
           state_ = new OffState();     
        }

        void setState(State* state){
            this->state_ = state;
        }

        void on(){
           state_->on(this);
        }

        void off(){
            state_->off(this);
        }
};

void OnState::off(LightSwitch* ls){
    std::cout << "Switching light from on to off\n";
    ls->setState(new OffState());
    delete this;
}

void OffState::on(LightSwitch* ls){
    std::cout << "switching the light from off to on\n";
    ls->setState(new OnState());
    delete this;
}
int main(){

    LightSwitch ls;
    ls.on();
    ls.on();
    ls.off();
    ls.off();
        
    return 0;
}
