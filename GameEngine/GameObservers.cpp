

#include "GameObservers.h"

// PhaseObserver -------------------------------------------------------------------------------------------------------

PhaseObserver::PhaseObserver() {
    current_player_name_ = "";
    current_phase_ = "";
    current_action_description_ = "";
    phase_over_ = false;
    phase_start_ = false;
}

PhaseObserver::PhaseObserver(const PhaseObserver &phase_observer) {
    current_player_name_ = phase_observer.current_player_name_;
    current_phase_ = phase_observer.current_phase_;
    current_action_description_ = phase_observer.current_action_description_;
    phase_over_ = phase_observer.phase_over_;
    phase_start_ = phase_observer.phase_start_;
}

PhaseObserver& PhaseObserver::operator=(const PhaseObserver &phase_observer) {
    if(this != &phase_observer) {
        current_player_name_ = phase_observer.current_player_name_;
        current_phase_ = phase_observer.current_phase_;
        current_action_description_ = phase_observer.current_action_description_;
        phase_over_ = phase_observer.phase_over_;
        phase_start_ = phase_observer.phase_start_;

    }

    return *this;
}

void PhaseObserver::Update(Player* current_player, int current_phase, string current_action_description, bool phase_start, bool phase_over) {
    if(!current_player) {
        cout << "Something went wrong! Unable to update phase observer" << endl;
        return;
    }

    current_player_name_ = *current_player->GetPlayerName();
    current_action_description_ = current_action_description;
    phase_over_ = phase_over;
    phase_start_ = phase_start;

    //only print header once at start of phase or if we've filled the screen and need to clear it again
    if(current_phase_.empty() || phase_start) {
        switch(current_phase) {
            case GamePhase::Startup :
                Utility::ClearScreen();
                current_phase_ = "Startup Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Reinforce :
                Utility::ClearScreen();
                current_phase_ = "Reinforce Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Attack :
                Utility::ClearScreen();
                current_phase_ = "Attack Phase";
                DisplayPhaseHeader();
                break;
            case GamePhase::Fortify :
                Utility::ClearScreen();
                current_phase_ = "Fortify Phase";
                DisplayPhaseHeader();
                break;
            default:
                Utility::ClearScreen();
                current_phase_ = "";
                break;
        }
    }

    DisplayPhaseData();
}

void PhaseObserver::DisplayPhaseData() {
    cout << current_action_description_ << endl;
    if(phase_over_) {
        //put thread to sleep to allow smoother visual transition
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        current_phase_ = "";
    }
}

void PhaseObserver::DisplayPhaseHeader() {
    cout << endl << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #" << endl << endl;
    cout << current_player_name_ + ": " + current_phase_ << endl << endl;
    cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # " << endl << endl;
}



// GameStatisticObserver -----------------------------------------------------------------------------------------------

void GameStatisticObserver::Update(string msg, const vector<Player*>& players) {
    Utility::ClearScreen();
    cout << msg << endl;
    DisplayStats(players);

    //put thread to sleep to allow smoother visual transition
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

void GameStatisticObserver::DisplayStats(const vector<Player*>& players){
    cout << "+++++++++++ Current Game Statistics +++++++++++" << endl
    << "Current Number of Card Swaps: "
    << CardExchangesCompleted(players)
    << endl << endl
    << "List of Active Players: " << endl << endl;

    DisplayActivePlayerStats(players);
}

int GameStatisticObserver::CardExchangesCompleted(const vector<Player*>& players){

    if(players.empty()) {
        return 0;
    }

    Player* current = players[0];
    if(!current) {
        return 0;
    }

    Hand* a_hand = current->GetPlayersCards();

    if(a_hand) {
        return Hand::exchanges_done;
    }

    return 0;
}

void GameStatisticObserver::DisplayActivePlayerStats(const vector<Player*>& players){

    if(players.empty()) {
        cout << "No players found in current game" << endl;
        return;
    }

    for(Player* player : players) {

        vector<Country*>* player_countries = player->GetPlayersCountries();
        if(!player_countries){
            cout << "player_countries" << endl;
            return;
        }

        vector<Country*>* map_countries = player->GetGameMap()->GetCountries();


        Hand* player_hand = player->GetPlayersCards();
        if(!map_countries || !player_hand) {
            return;
        }
        //Display the stats of players with at least 1 country
        if(!player_countries->empty() && !map_countries->empty()){
            cout << "Player: "
            << *player->GetPlayerName()
            << endl
            <<"Current Cards in hand: "
            <<player_hand->GetNumberOfCardsInHand()
            <<endl
            << "Countries owned: "
            << player_countries->size()
            << endl
            << "% Map Conquered: "
            << fixed << setprecision(0) <<((float)(player_countries->size()) / (float)(map_countries->size()))*100
            << "%"
            << endl << endl;
        }
    }
}