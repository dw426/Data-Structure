#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class GameManager {
private:
    int playerScore;
    int computerScore;
    bool cheatModeEnabled;
    std::string secretKey;

public:
    GameManager() : playerScore(0), computerScore(0), cheatModeEnabled(false) {
        srand(time(nullptr));
        generateSecretKey();
    }

    void generateSecretKey() {
        secretKey = "debug_" + std::to_string(rand() % 10000);
    }

    bool validateSecretKey(const std::string& input) {
        return input == secretKey;
    }

    int playRound() {
        int playerChoice = rand() % 3;  // 0: Rock, 1: Paper, 2: Scissors
        int computerChoice = rand() % 3;

        if (cheatModeEnabled) {
            computerChoice = (playerChoice + 1) % 3;  // Guaranteed win for player
        }

        // 승자 결정 로직
        if (playerChoice == computerChoice) return 0;  // 무승부
        if ((playerChoice + 1) % 3 == computerChoice) return -1;  // 컴퓨터 승리
        return 1;  // 플레이어 승리
    }

    void enableCheatMode(const std::string& key) {
        if (validateSecretKey(key)) {
            cheatModeEnabled = true;
            std::cout << "치트 모드 활성화!" << std::endl;
        }
    }

    void displayScores() {
        std::cout << "플레이어 점수: " << playerScore 
                  << " 컴퓨터 점수: " << computerScore << std::endl;
    }
};

int main() {
    GameManager game;
    
    for (int i = 0; i < 5; ++i) {
        int result = game.playRound();
        game.displayScores();
    }

    return 0;
}