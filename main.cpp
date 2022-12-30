// This application is based on World Football Elo Ratings (https://www.eloratings.net/about)
// to calculate rating of two football teams after the game.

#include <iostream>
#include <cmath>

using namespace std;

void calculateElo (int &team1_rating, int team2_rating, int team1_goals, int team2_goals, float category)
{
    /*
    FORMULA to calculate new rating: Rn = Ro + K * G * (W - We)

    WHERE:
    Rn is the new rating, Ro is the old (pre-match) rating.
    K is the weight constant for the tournament played
    G is points for goal difference

    W is the result of the game (1 for a win, 0.5 for a draw, and 0 for a loss).

    We is the expected result (win expectancy) from the following formula:
    We = 1 / (1 + 10(dr/400)) where dr is difference in teams rating
    */

    float goals; // G in formula
    float goal_difference = team1_goals - team2_goals;
    float result; //W in formula

    //results value
    if(team1_goals > team2_goals) { result = 1; }
    else if(team1_goals == team2_goals) { result = 0.5; }
    else { result = 0; }

    //goals value
    if (team1_goals - team2_goals == 2 || team1_goals - team2_goals == -2) { goals = 1.5; }
    else if (team1_goals - team2_goals == 3 || team1_goals - team2_goals == -3) { goals = 1.75; }
    else if (team1_goals - team2_goals > 3 || team1_goals - team2_goals < -3) { goals = 1.75 + (goal_difference-3)/8; }
    else goals = 1;

    //We in formula
    float probability = 1.0 / (1 + 1.0 * pow(10, 1.0 * (team2_rating - team1_rating) / 400));

    //calculating new rating
    float new_rating = round(team1_rating + (category * goals) * (result - probability));

    //change of rating
    cout << "Change : ";
    if(new_rating-team1_rating > 0) { cout << "+"; } //adding + sign if rating change is positive
    cout << new_rating-team1_rating << endl;

    cout << "New rating: " << new_rating << endl;

    //saving new rating as first team rating
    team1_rating = new_rating;
}

int main()
{
    int rating1, rating2, goal1, goal2;
    float category;

    cout << " First team rating: ";
    cin >> rating1;

    cout << "Second team rating: ";
    cin >> rating2;

    cout << "  First team goals: ";
    cin >> goal1;

    cout << " Second team goals: ";
    cin >> goal2;

    cout << "\n\nMATCH CATEGORY:\n";
    cout << "60 for World Cup finals\n";
    cout << "50 for continental championship finals and major intercontinental tournaments\n";
    cout << "40 for World Cup and continental qualifiers and major tournaments\n";
    cout << "30 for all other tournaments\n";
    cout << "20 for friendly matches\n\n";

    while(category != 60 && category != 50 && category != 40 && category != 30 && category != 20)
    {
        cout << "    Match category: ";
        cin >> category;

        if(category != 60 && category != 50 && category != 40 && category != 30 && category != 20)
            cout << "    Wrong! Choose 60, 50, 40, 30 or 20!\n";
    }

    int old_rating1 = rating1; //saving old rating of first team

    system("CLS");

    cout << "TEAM 1: \n";
    calculateElo(rating1, rating2, goal1, goal2, category);

    cout << endl << "TEAM 2: \n";
    calculateElo(rating2, old_rating1, goal2, goal1, category);

    return 0;
}
