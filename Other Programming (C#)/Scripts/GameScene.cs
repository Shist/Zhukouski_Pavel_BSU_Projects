using UnityEngine;
using System.Collections;

/// <summary>
/// Game scene.
/// 
/// Use this file to write codes for Game Screen.
/// 
/// </summary>

public class GameScene : MonoBehaviour {

	// Boolean variables for game states
	public static bool gamePaused = false;
	public static bool gameOver = false;
	public static bool overShown = false;

	public static int scoreNum = 0;

	public static GameButtons gbs;

	// Use this for initialization
	void Start () {
	
		// Initialize when game is started
		gamePaused = false;
		gameOver = false;
		overShown = false;

		scoreNum = 0;

		Time.timeScale = 1; // To ensure, its not set to "0" at the start
	
	}
	
	// Update is called once per frame
	void Update () {
	
		// We'll use two booleans, so that it is not repeated.
		// If not used two booleans, the code might run every frame when gameOver variable is true 
		if(gameOver && !overShown){
			overShown = true;
			gbs.OnGameOver(); 
			// gbs is GameButtons file. It has been initialed in Start() function of GameButtons.cs
			// There is a method OnGameOver(), it is called when gameOver variable is true.
			// Just use gameOver = true; when you want to over the game
		}


		// You can also call gbs.UpdateScore() to update score.

	}
	
}







