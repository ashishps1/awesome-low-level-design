package cricinfo

import (
	"fmt"
	"time"
)

func Run() {
	// Create teams
	team1Players := []*Player{
		NewPlayer("P101", "Player 1", "Batsman"),
		NewPlayer("P102", "Player 2", "Bowler"),
		NewPlayer("P103", "Player 3", "All-rounder"),
	}
	team2Players := []*Player{
		NewPlayer("P201", "Player 4", "Batsman"),
		NewPlayer("P202", "Player 5", "Bowler"),
		NewPlayer("P203", "Player 6", "All-rounder"),
	}

	team1 := NewTeam("T1", "Team 1", team1Players)
	team2 := NewTeam("T2", "Team 2", team2Players)
	teams := []*Team{team1, team2}

	// Create match
	match := NewMatch("M001", "Match 1", "Venue 1", time.Now(), teams)

	// Create Cricinfo system
	cricinfoSystem := NewCricinfoSystem()

	// Add match
	cricinfoSystem.AddMatch(match)

	// Create scorecard
	scorecardID := cricinfoSystem.CreateScorecard(match)

	// Update scores
	cricinfoSystem.UpdateScore(scorecardID, "T1", 100)
	cricinfoSystem.UpdateScore(scorecardID, "T2", 75)

	// Create innings
	innings1 := NewInnings("I1", "T1", "T2")
	innings2 := NewInnings("I2", "T2", "T1")

	// Add overs
	over1 := NewOver(1)
	over1.AddBall(NewBall(1, "P202", "P101", "4"))
	over1.AddBall(NewBall(2, "P202", "P101", "6"))
	innings1.AddOver(over1)

	over2 := NewOver(2)
	over2.AddBall(NewBall(1, "P102", "P201", "1"))
	over2.AddBall(NewBall(2, "P102", "P201", "0"))
	innings1.AddOver(over2)

	// Add innings
	cricinfoSystem.AddInnings(scorecardID, innings1)
	cricinfoSystem.AddInnings(scorecardID, innings2)

	// Display scorecard
	scorecard := cricinfoSystem.GetScorecard(scorecardID)
	displayScorecard(scorecard)
}

func displayScorecard(scorecard *Scorecard) {
	fmt.Printf("Scorecard ID: %s\n", scorecard.ID)
	fmt.Printf("Match: %s\n", scorecard.Match.Title)

	fmt.Println("Team Scores:")
	for teamID, score := range scorecard.TeamScores {
		fmt.Printf("%s: %d\n", teamID, score)
	}

	fmt.Println("\nInnings:")
	for _, innings := range scorecard.Innings {
		fmt.Printf("Innings ID: %s\n", innings.ID)
		fmt.Printf("Batting Team: %s\n", innings.BattingTeamID)
		fmt.Printf("Bowling Team: %s\n", innings.BowlingTeamID)
		fmt.Println("Overs:")
		for _, over := range innings.Overs {
			fmt.Printf("Over %d\n", over.OverNumber)
			for _, ball := range over.Balls {
				fmt.Printf("Ball %d: %s to %s - %s\n",
					ball.BallNumber, ball.Bowler, ball.Batsman, ball.Result)
			}
		}
		fmt.Println()
	}
}
