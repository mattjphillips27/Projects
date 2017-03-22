using UnityEngine;
using System.Collections;

public class EndGame : MonoBehaviour {


	public GameObject cutscene;
	
	// Use this for initialization
	void Start () 
	{
		//cutscene.active = false;
	}
	
	void OnTriggerEnter(Collider other) 
	{
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		if (num.Bomb== true)
		{
			if (other.gameObject.tag == "Player") 
			{
				Time.timeScale = 0;
				cutscene.active = true;
				Cursor.visible = true;
			}
		}
	
	}
}
