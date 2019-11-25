#include <iostream>
#include <map>
#include <vector>
#include <string>
//HandMade state machine implementation

enum class State{
    off_hook,
    connecting,
    connected,
    on_hold,
    on_hook
};

inline std::ostream& operator<<(std::ostream& os, const State& s){
    switch(s){
        case State::off_hook:
            os << "phone off the hook\n";
            break;
        case State::connecting:
            os << "phone waiting to connect\n";
            break;
        case State::connected:
            os << "phone connected\n";
            break;
        case State::on_hold:
            os << "phone on hold\n";
            break;
        case State::on_hook:
            os << "phone on hook\n";
            break;
        default:
            os << "unknown state of phone\n";
            break;
    }

    return os;
}

enum class Trigger{
        call_dialed,
        hung_up,
        call_connected,
        placed_on_hold,
        placed_off_hold,
        left_message,
        stop_using_phone
};

inline std::ostream& operator<<(std::ostream& os, const Trigger& t){

    switch(t){
        case Trigger::call_dialed:
            os << "call dialled by user\n";
            break;
        case Trigger::hung_up:
            os << "phone hung up by user\n";
            break;
        case Trigger::call_connected:
            os << "hey user, call has connected\n";
            break;
        case Trigger::placed_on_hold:
            os << "phone placed on hold by user\n";
            break;
        case Trigger::placed_off_hold:
            os << "phone placed off hold by user\n";
            break;
        case Trigger::left_message:
            os << "user left message\n";
            break;
        case Trigger::stop_using_phone:
            os << "user put the phone back on hook\n";
            break;
        default:
            os << "unknown action initiated by user\n";
            os << "user is hacking the phone !!!\n";
            break;
    }

    return os;
}
int main(){
       
    //state machines is a set of rules
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;
    rules[State::off_hook] = {{Trigger::call_dialed, State::connecting},
                             {Trigger::stop_using_phone, State::on_hook}
                             };

    rules[State::connecting] = {
                                {Trigger::hung_up, State::off_hook},
                                {Trigger::call_connected, State::connected}
                               };

    rules[State::connected] = {
                              {Trigger::left_message, State::off_hook},
                              {Trigger::hung_up, State::off_hook},
                              {Trigger::placed_on_hold, State::on_hold}
                              };


    State currentState{State::off_hook};
    State exitState{State::on_hook};

    while(true){
        std::cout << "The phone is currently " << currentState << "\n";

        select_trigger:
        int i{0};
        std::cout << "Select a trigger:\n";
        for(auto item : rules[currentState]){
                std::cout << i++ << ". " << item.first << "\n";
        }
        size_t input=0;
        std::cin >> input;
        if(input <0 || (input +1) > rules[currentState].size())
        {
            std::cout << "Incorrect option. Please try again!\n";
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if(currentState == exitState)
            break;

    }
    std::cout << "We are done using the phone\n";
    return 0;
}
