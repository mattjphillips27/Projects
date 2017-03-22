using UnityEngine;
using System.Collections;

public class pickup : MonoBehaviour {

	void OnTriggerEnter(Collider other)
	{
		GameObject guiObje = GameObject.Find ("GUI"); 
		JangGUI guiScripte = guiObje.GetComponent<JangGUI> (); 
		
		if (other.tag == "Player") 
		{	
			guiScripte.playerHealth = 100;

			Destroy(gameObject);
			
		}

		if (other.tag == "Pitchfork") 
		{	
			guiScripte.playerHealth = 100;
			
			Destroy(gameObject);
			
		}
}
}