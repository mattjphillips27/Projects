using UnityEngine;
using System.Collections;

public class StartGUI : MonoBehaviour {

	public float hAlanHealth = 30.0f;
	public GameObject comper;
	
	void OnGUI()	
	{	
		Cursor.visible = true;
		
		
//		GUI.BeginGroup (new Rect (Screen.width / 2 - 100, Screen.height / 2 - 100, 250, 250));
//		Alan healthScript = comper.transform.GetComponent<Alan>();
//		
//		hAlanHealth = GUI.HorizontalSlider(new Rect(25, 25, 150, 30), hAlanHealth, 0.0f, 100.0f);
//		int iValue = (int)hAlanHealth;
//		healthScript.health = iValue;
//		
//		GUI.Label(new Rect(0, 35, 250, 100), "Move slider to change Alan's health");
//		
//		
//		
//		GUI.Box (new Rect (0,0,200,200), "Welcome to Maxwell's Farm");
//		
//		
//		
//		if (GUI.Button (new Rect (53,60,100,30), "Play Game")) {
//			
//			Application.LoadLevel("Level1");
//		}
//		if (GUI.Button (new Rect (53,100,100,30), "Exit Game")) {
//			
//			Application.Quit();
//		}
//		GUI.EndGroup ();
	}
}
