using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class AlanHealth : MonoBehaviour {

	Text health;
	string healthString = "30";
	public GameObject RestartButton;
	public GameObject ExitButton;
	
	
	
	// Use this for initialization
	void Start () {
		health = GetComponent<Text>();
		Cursor.visible = false;
		Time.timeScale = 1;
		
		 
		
	}
	
	// Update is called once per frame
	void Update () {
		GameObject guiObje = GameObject.Find ("Alan"); 
		DuckAI guiScripte = guiObje.GetComponent<DuckAI> ();
		
		healthString = guiScripte.health.ToString();
		health.text = healthString;
		
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			Application.LoadLevel("StartMenu");
		}
		
		
		if(guiScripte.health <= 0)
		{
			Time.timeScale = 0;
			Cursor.visible = true;
			
			RestartButton.active = true;
			ExitButton.active = true;
			
		}
		
	}
}
