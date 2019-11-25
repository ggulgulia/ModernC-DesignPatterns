#include <iostream>
#include <utility>
#include <memory>

class LightSwitch;
class SwitchState{
 
    public:
        virtual void on(LightSwitch&){
            std::cout << "Light is already in on state\n";
        }
        
        virtual void off(LightSwitch&){
            std::cout << "Light is already in off state\n";
        }

        virtual ~SwitchState(){} 
};


class OnState : public SwitchState{
        
    public:
        OnState(){
            std::cout << "the light is switched on\n";
        }

        void off(LightSwitch& ls) override;
};

class OffState : public SwitchState{
    public:
    OffState() {
        std::cout << "the light is switched on\n";
    }

    void on(LightSwitch& ls) override;
};

class LightSwitch{
    private:

        std::unique_ptr<SwitchState> state_;      
    public:
        //the light is swtiched off when created
        LightSwitch(): state_{std::make_unique<OffState>()}{
           std::cout << "new light switch created in off state\n";
        }

        //LightSwitch(const LightSwitch&) = delete;

        void on(){
            state_->on(*this);
        }

        void off(){
            state_->off(*this);
        }


        //perfect forwarding function
        template <typename T>
        void setState(T&& state){
                state_.release();
                state_ = std::forward<T>(state);
        }
         
        void resetState(){
                state_.release();
        }
};


void OffState::on(LightSwitch& ls){
        
    std::cout << "switching the light from OFF to ON!!\n";
    ls.resetState();
    ls.setState(std::make_unique<OnState>());
}

void OnState::off(LightSwitch& ls){
        
    std::cout << "switching the light from ON to OFF!!\n";
    ls.resetState();
    ls.setState(std::make_unique<OffState>());
}
int main(){
        
    LightSwitch ls;
    ls.off();
    ls.on();
    ls.on();
    ls.off();

    return 0;
}
