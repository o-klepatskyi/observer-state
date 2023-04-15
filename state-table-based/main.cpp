// source: http://www.vishalchovatiya.com/state-design-pattern-in-modern-cpp/
#include <iostream>
#include <map>
#include <vector>
using namespace std;

enum class State {
    OffHook, Connecting, Connected, OnHold, OnHook
};

inline ostream& operator<<(ostream& os, State& s) {
    switch (s) {
    case State::OffHook: os << "off the hook"; break;
    case State::Connecting: os << "connecting"; break;
    case State::Connected: os << "connected"; break;
    case State::OnHold: os << "on hold"; break;
    case State::OnHook: os << "on the hook"; break;
    }
    return os;
}

enum class Trigger {
    CallDialed, HungUp, CallConnected, PlacedOnHold, TakenOffHold, LeftMessage, StopUsingPhone
};

inline ostream& operator<<(ostream& os, Trigger& t) {
    switch (t) {
    case Trigger::CallDialed: os << "call dialed"; break;
    case Trigger::HungUp: os << "hung up"; break;
    case Trigger::CallConnected: os << "call connected"; break;
    case Trigger::PlacedOnHold: os << "placed on hold"; break;
    case Trigger::TakenOffHold: os << "taken off hold"; break;
    case Trigger::LeftMessage: os << "left message"; break;
    case Trigger::StopUsingPhone: os << "putting phone on hook"; break;
    }
    return os;
}

int main() {
    map<State, vector<pair<Trigger, State>>>    transition_table;

    transition_table[State::OffHook] = {
        { Trigger::CallDialed, State::Connecting },
        { Trigger::StopUsingPhone, State::OnHook }
    };

    transition_table[State::Connecting] = {
        { Trigger::HungUp, State::OffHook },
        { Trigger::CallConnected, State::Connected }
    };

    transition_table[State::Connected] = {
        { Trigger::LeftMessage, State::OffHook },
        { Trigger::HungUp, State::OffHook },
        { Trigger::PlacedOnHold, State::OnHold }
    };

    transition_table[State::OnHold] = {
        { Trigger::TakenOffHold, State::Connected },
        { Trigger::HungUp, State::OffHook }
    };

    State currentState{ State::OffHook };
    State exitState{ State::OnHook };

    for (;;) {
        cout << "The phone is currently " << currentState << endl;
        cout << "Select a trigger:\n";

        uint32_t i = 0;
        for (auto item : transition_table[currentState])
            cout << i++ << ". " << item.first << "\n";

        uint32_t input;
        cin >> input;
        if (input >= transition_table[currentState].size() || input < 0) {
            cout << "Wrong operation. Try again.\n";
            continue;
        }
        currentState = transition_table[currentState][input].second;
        if (currentState == exitState) break;
    }

    cout << "We are done using the phone" << endl;

    return EXIT_SUCCESS;
}