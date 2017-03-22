using UnityEngine;
using System.Collections;

public class JangGUI : MonoBehaviour 
{		
	public int playerHealth;
	//public int alanHealth;
	private Rect playerHealthBox;
	private Rect alanHealthBox;
	
	void Awake()
	{
		playerHealthBox = new Rect(Screen.width - 200, 90, 200, 20);
		alanHealthBox = new Rect(Screen.width - 200, 105, 200, 20);
		Time.timeScale = 1;


	}
	
	void Start () 
	{
		Time.timeScale = 1;

		Cursor.visible = false;
	}

	void Update ()
	{
		//Screen.showCursor = false;
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			Application.LoadLevel("StartMenu");
		}
		
	}

	void OnGUI()	
	{	
		GameObject guiObje = GameObject.Find ("Alan"); 
		DuckAI guiScripte = guiObje.GetComponent<DuckAI> (); 

		GUI.Label(playerHealthBox, "Player's Health: " + playerHealth);
		GUI.Label(alanHealthBox, "Alan's Health: " + guiScripte.health);
		
		
		if(playerHealth <= 0 || guiScripte.health <= 0)
		{
			Time.timeScale = 0;
			Cursor.visible = true;

				
				
				GUI.BeginGroup (new Rect (Screen.width / 2 - 100, Screen.height / 2 - 100, 200, 200));
				
				GUI.Box (new Rect (0,0,200,200), "Game Over");
				
				if (GUI.Button (new Rect (53,50,100,30), "Restart Game")) 
				{
					
					Application.LoadLevel("StartMenu");
				}
				
				if (GUI.Button (new Rect (53,100,100,30), "Exit Game")) 
				{
					
					Application.Quit();
				}
				
				
				GUI.EndGroup ();

			
		}
	}
}


