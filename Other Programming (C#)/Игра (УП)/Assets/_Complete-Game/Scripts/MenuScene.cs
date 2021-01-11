using UnityEngine;
using System.Collections;

/// <summary>
/// Menu scene.
/// 
/// Use this file to write codes for Menu Screen.
/// The global variables for sound and music are initialized here.
/// These variables are used to read the state of sound turn on/off to play sound accordingly.
/// 
/// </summary>

public class MenuScene : MonoBehaviour {

	// Global Sound and Music variables
	public static bool soundOn = true;
	public static bool musicOn = true;

	// Use this for initialization
	void Start () {

		// Set the time scale to normal
		// The timescale is later changed in GameScene to 0 to pause/over
		Time.timeScale = 1;

		// Use the code below to play sound and music
//		if(MenuScene.soundOn){
//			SoundVariable.Play();
//		}

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
