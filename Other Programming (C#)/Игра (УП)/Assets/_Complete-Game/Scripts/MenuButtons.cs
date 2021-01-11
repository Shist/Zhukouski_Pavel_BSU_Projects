using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// Menu buttons.
/// 
/// This file contains the codes for Buttons on Menu Screen and their actions.
/// 
/// </summary>

public class MenuButtons : MonoBehaviour {

	public Button PlayButton; 				// Play button from scene
	public int PlayLevel = 1;				// Game scene level number from build settings

	public Button SettingsButton;			// Settings button from scene
	public GameObject SettingsScreen;		// GameObject that contains Settings screen UI elements, so that we can hide and show it

	public Button CloseButton;				// Close button on Settings screen UI from scene, refer hierarchy

	public Toggle SoundButton = null;		// Sound toggle button from settings screen
	public Image SoundBackground = null; 	// Bakground Image from Sound toggle button, so that we can change it

	public Toggle MusicButton = null;		// Music toggle button from settings screen
	public Image MusicBackground = null; 	// Background Image from Music toggle button, so that we can change it

	public Sprite TickSprite = null;		// Tick Sprite
	public Sprite UntickSprite = null; 		// Untick sprite

	// Actions for the above buttons
	UnityAction playAction = null;
	UnityAction settingsAction = null;
	UnityAction closeAction = null;
	UnityAction<bool> soundAction = null;
	UnityAction<bool> musicAction = null;

	// Use this for initialization
	void Start () {
	
		// When play button is clicked, we load the level mentioned from inspector, here, its "1"
		playAction = () => { Application.LoadLevel(PlayLevel); };
		PlayButton.onClick.AddListener(playAction);

		// By default we disable the settings screen Ui, we'll show it when user clicks settings button
		SettingsScreen.SetActive(false);

		// When user clicks settings button, we call OnSettingsClicked() method and show settings UI
		settingsAction = () => { OnSettingsClicked(); };
		SettingsButton.onClick.AddListener(settingsAction);

		// Close the settings screen UI using OnClosedClicked() method defined below
		closeAction = () => { OnCloseClicked(); };
		CloseButton.onClick.AddListener(closeAction);

		// We set the default image of sound on/off button according to
		// current boolean values, sometimes the values are changed from another screen
		if(MenuScene.soundOn){
			SoundBackground.sprite = TickSprite;
			SoundButton.isOn = true;
		}else{
			SoundBackground.sprite = UntickSprite;
			SoundButton.isOn = false;
		}

		// Change the state of sound toggle according to OnSoundChange method below
		soundAction = (value) => OnSoundChange(value);
		SoundButton.onValueChanged.AddListener(soundAction);

		// We set the default image of music on/off button according to
		// current boolean values, sometimes the values are changed from another screen
		if(MenuScene.musicOn){
			MusicBackground.sprite = TickSprite;
			MusicButton.isOn = true;
		}else{
			MusicBackground.sprite = UntickSprite;
			MusicButton.isOn = false;
		}

		// Change the state of sound toggle according to OnMusicChange method below
		musicAction = (value) => OnMusicChange(value);
		MusicButton.onValueChanged.AddListener(musicAction);


	}

	// Method to show settings UI when settings button is clicked
	private void OnSettingsClicked(){

		// Disable play button and settings button
		PlayButton.image.enabled = false;
		SettingsButton.image.enabled = false;

		// Show settings UI, by default it is hidden
		SettingsScreen.SetActive(true);

	}

	// Method for close button on settings UI
	private void OnCloseClicked(){

		// Hide settings UI
		SettingsScreen.SetActive(false);

		// Enable play and settings button
		PlayButton.image.enabled = true;
		SettingsButton.image.enabled = true;
		
	}

	// Method for sound on/off button
	private void OnSoundChange(bool value)
	{
		if(value){
			SoundBackground.sprite = TickSprite; 	// if the state is true, use tick image 
			SoundButton.isOn = true; 				// toggle button is On when value is true
			MenuScene.soundOn = true;				// Our boolean is also on for sound, we'll use this boolean to play sound
		}else{
			SoundBackground.sprite = UntickSprite;	// if the state is false, use untick image
			SoundButton.isOn = false;				// toggle button is Off when value is false
			MenuScene.soundOn = false;				// Our boolean is also on for sound, we'll use this boolean to play sound
		}
	}

	// Method for music on/off button
	private void OnMusicChange(bool value)
	{
		if(value){
			MusicBackground.sprite = TickSprite;	// if the state is true, use tick image 
			MusicButton.isOn = true;				// toggle button is On when value is true
			MenuScene.musicOn = true;				// Our boolean is also on for music, we'll use this boolean to play music
		}else{		
			MusicBackground.sprite = UntickSprite;	// if the state is false, use untick image 
			MusicButton.isOn = false;				// toggle button is Off when value is false
			MenuScene.musicOn = false;				// Our boolean is also on for music, we'll use this boolean to play music
		}
	}

}









