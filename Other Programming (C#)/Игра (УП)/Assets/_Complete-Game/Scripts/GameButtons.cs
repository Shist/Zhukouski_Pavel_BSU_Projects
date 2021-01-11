using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// Game buttons.
/// 
/// This file contains the codes for Buttons on Game Screen and their actions.
/// 
/// </summary>

public class GameButtons : MonoBehaviour {

	public Button PauseButton;			// Pause button from scene

	public Button ResumeButton;			// Resume button from Paused Screen UI in the scene, refer hierarchy

	public Button HomeButton;			// Home button from Paused Screen UI
	public int HomeLevel = 0;			// Home screen level num from build settings, here, its "0"

	public Button ReplayButton;			// Replay button from Over Screen UI

	public Button HomeButtonOver;		// Home button from Over Screen UI

	public Button ScoreUpdateButton;	// Score Update button from scene
	public Button GameOverButton;		// Game Over button from scene

	public Text scoreText;				// Text to display score value, from scene
	public Text bestText;				// Text to display best value, from scene

	public GameObject PausedScreen;		// The gameObject that contains all the paused screen elements in the scene
	public GameObject OverScreen;		// The gameObject that contains all the over screen elements in the scene
		
	public Text scoreTextOver;			// Score text from Over Screen UI
	public Text bestTextOver;			// Best text from Over Screen UI

	// Actions for the above buttons
	UnityAction pauseAction = null;
	UnityAction resumeAction = null;
	UnityAction homeAction = null;
	UnityAction replayAction = null;
	UnityAction scoreUpdateAction = null;
	UnityAction gameOverAction = null;


	// Use this for initialization
	void Start () {

		// By default we disable the Paused/Over screen Ui, we'll show it when user clicks settings button
		PausedScreen.SetActive(false);
		OverScreen.SetActive(false);

		// Get the previously store best score value and display on screen
		int bestNum = PlayerPrefs.GetInt("best", 0);
		bestText.text = "Best: " + bestNum;

		// When pause button is clicked, we show Pause Screen UI using method OnGamePaused;
		pauseAction = () => { OnGamePaused(); };
		PauseButton.onClick.AddListener(pauseAction);

		// When score update button is clicked, we update score using method OnUpdateScore();
		scoreUpdateAction = () => { OnUpdateScore(); };
		ScoreUpdateButton.onClick.AddListener(scoreUpdateAction);

		// When game over button is clicked, we finish game and show Over Screen UI using method OnGameOver();
		gameOverAction = () => { OnGameOver(); };
		GameOverButton.onClick.AddListener(gameOverAction);

		// When resume button is clicked, we hide Paused Screen UI and resume game using method OnGameResumed();
		resumeAction = () => { OnGameResumed(); };
		ResumeButton.onClick.AddListener(resumeAction);

		// When replay button is clicked, we simply re-start Game level
		replayAction = () => { Application.LoadLevel(Application.loadedLevel); };
		ReplayButton.onClick.AddListener(replayAction);

		// When Home button is clicked, we load Menu Screen using method gotoHome();
		homeAction = () => { gotoHome(); };
		HomeButton.onClick.AddListener(homeAction);
		HomeButtonOver.onClick.AddListener(homeAction); // Same action is used since they both do same task 

		GameScene.gbs = this;
	}
	
	// Method to update score
	private void OnUpdateScore(){
		GameScene.scoreNum += 1;							// Increase current score value
		scoreText.text = "Score: " + GameScene.scoreNum;	// Show the updated score value
	}

	// Method for when Pause button is clicked
	private void OnGamePaused(){
		Time.timeScale = 0;					// Stop game time
		PauseButton.image.enabled = false;	// Hide pause button, since its already paused
		PausedScreen.SetActive(true);		// Show Paused Screen UI
	}

	// Method for when Resume button is clicked
	private void OnGameResumed(){
		Time.timeScale = 1; 				// Resume game time
		PauseButton.image.enabled = true; 	// Enable pause button
		PausedScreen.SetActive(false);		// Hide Paused Screen UI 
	}

	// Method to run when game is over and to show game over screen UI
	public void OnGameOver(){
		Time.timeScale = 0; // Game is over so we stop the time

		// Read previously store best value
		// If current score is higher than previously stored value, we update the stored best value
		int bestNum = PlayerPrefs.GetInt("best", 0);
		if(GameScene.scoreNum > bestNum){
			bestNum = GameScene.scoreNum;
			PlayerPrefs.SetInt("best", GameScene.scoreNum);
		}

		// Show current and best score text is Over Screen UI
		scoreTextOver.text = "Score\n" + GameScene.scoreNum;
		bestTextOver.text = "Best\n" + bestNum;

		// Disable Pause button and enable Game Over Screen UI
		PauseButton.image.enabled = false;
		GameOverButton.image.enabled = false;
		OverScreen.SetActive(true);
	}

	// Method to run when Home button is clicked
	private void gotoHome(){
		GameScene.gamePaused = false; 		// The variable paused is false if this is cliked
		Application.LoadLevel(HomeLevel); 	// Load the home screen level
		Time.timeScale = 1;					// Time scale should be 1
	}


}








