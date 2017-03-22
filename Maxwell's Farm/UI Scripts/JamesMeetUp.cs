using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class JamesMeetUp : MonoBehaviour {

	
	Text txt;
	int count;
	public GameObject cutscene;
	
	// Use this for initialization
	void Start () 
	{
		txt = GetComponent<Text>();
		count = 1;
		Time.timeScale = 0;
	}
	
	void OnDestroy() {
		Time.timeScale = 1;
	}
	
	// Update is called once per frame
	void Update () 
	{
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		if(Input.GetKeyDown("space"))
		{
			if(count == 1)
			{
				txt.text = "James: Hello to you too dad!";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Maxwell: You are a piece of shit you know that";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Maxwell: Jane is dead and this is how you act";
				count++;
			}
			else if(count == 4)
			{	
				txt.text = "James: Wait, Mom's dead?";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "James: What happened?";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "Maxwell: A cow killed her, I've already taken care of it";
				count++;
			}
			else if(count == 7)
			{
				txt.text = "Maxwell: We need to get kill these animals and get out of here";
				count++;
			}
			else if(count == 8)
			{
				txt.text = "Maxwell: I need my driving boots if we're leaving on the tractor";
				count++;
			}
			else if(count == 9)
			{
				
				Destroy(cutscene);
			}
		}
	}
}