#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Playr = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayrChoice;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName = "";
};
struct stGameResults
{
    short GameRound = 0;
    short PlayrWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner FinalWinner;
    string WinnerName = "";
};

//Helper Function---------------------------
int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
string WinnerName(enWinner Winner) {

    string arrWinnerName[3] = { "Player","Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}
string ChoiceName(enGameChoice Choice) {

    string arrGameChoice[3] = { "Stone", "Paper","Scissors" };
    return arrGameChoice[Choice - 1];
}
void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner)
    {
    case Playr:
        system("color 2f"); //Green
        break;
    case Computer:
        system("color 4f"); //Red
        cout << "\a";
        break;
    default:
        system("color 6f"); //Yellow
        break;
    }
}

//Inpout Function---------------------------------------
short ReadHowManyRound() {

    short RoundNumber = 0;
    do
    {
        cout << "How Many Rounds 1 to 10 ?" << endl;
        cin >> RoundNumber;

    } while (RoundNumber < 1 || RoundNumber > 10);

    return RoundNumber;
}
enGameChoice ReadPlayrChoice() {

    short PlayrChoice = 0;
    do
    {
        cout << "\nYour Choice: [1]Stone, [2]Paper, [3]Scissors ?";
        cin >> PlayrChoice;

    } while (PlayrChoice < 1 || PlayrChoice > 3);

    return (enGameChoice)PlayrChoice;
}
enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}

//logic Function----------------------------------------
enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

    if (RoundInfo.PlayrChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayrChoice)
    {
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Playr;
}
enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes) {

    if (PlayerWinTimes > ComputerWinTimes) {
        return enWinner::Playr;
    }
    else if (ComputerWinTimes > PlayerWinTimes) {
        return enWinner::Computer;
    }
    else {
        return enWinner::Draw;
    }
}
stGameResults FillGameResults(short GameRound, short PlayerWinTimes,
    short ComputerWinTimes, short DrawTimes) {

    stGameResults GameResults;
    GameResults.GameRound = GameRound;
    GameResults.PlayrWonTimes = PlayerWinTimes;
    GameResults.ComputerWonTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.FinalWinner = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.FinalWinner);
    return GameResults;
}

//Display Function--------------------------------------
void PrintRoundResult(stRoundInfo RoundInfo) {

    cout << "_________Round [" << RoundInfo.RoundNumber << "]_________\n\n";
    cout << "Player Choice: " << ChoiceName(RoundInfo.PlayrChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: [" << RoundInfo.WinnerName << "]\n";
    cout << "___________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.RoundWinner);
}
string Tabs(short NumberOfTabs) {

    string T = "";
    for (int i = 0; i < NumberOfTabs; i++)
    {
        T += "\t";
        cout << T;
    }
    return T;
}
void ShowGameOverScreen() {
    cout << Tabs(2) << "_________________________\n\n";
    cout << Tabs(2) << " +++ G a m e O v e r +++ \n";
    cout << Tabs(2) << "_________________________\n\n";
}
void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "----------------[Game Results]----------------" << endl;
    cout << Tabs(2) << "Game Round: " << GameResults.GameRound << endl;
    cout << Tabs(2) << "Player Won Times: " << GameResults.PlayrWonTimes << endl;
    cout << Tabs(2) << "Computer Won Times: " << GameResults.ComputerWonTimes << endl;
    cout << Tabs(2) << "Draw Times: " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner: " << GameResults.FinalWinner << endl;
    cout << Tabs(2) << "----------------------------------------------" << endl;

    SetWinnerScreenColor(GameResults.FinalWinner);
}

//Main Function--------------------------------------------
stGameResults PlayGame(short HowManyRounds) {

    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
    {
        cout << "Round [" << GameRounds << "] begins:";
        RoundInfo.RoundNumber = GameRounds;
        RoundInfo.PlayrChoice = ReadPlayrChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Playr)
            PlayerWinTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}
void ResetScreen() {

    system("cls"); // Cleen Screen
    system("color 0F");// Black
}
void StartGame() {

    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRound());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(5) << "Do you want to play again ? Y/N" << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}