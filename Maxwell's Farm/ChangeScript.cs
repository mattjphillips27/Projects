using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ChangeScript : MonoBehaviour 
{
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
				txt.text = "Maxwell: What have you got there cow?";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Maxwell: OMG that is my wife!";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Maxwell: She's at it again! Wait...";
				count++;
			}
			else if(count == 4)
			{
				txt.text = "Maxwell: Is that...blood?";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "Maxwell: Cow what have you done?!";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "Cow: MOOOOOO";
				count++;
			}
			else if(count == 7)
			{
				txt.text = "Maxwell: That's it cow, time to end you";
				count++;
			}
			else if(count == 8)
			{
				txt.text = "Maxwell murders the damned cow";
				count++;
			}
			else if(count == 9)
			{
				num.objectivenumber++;
				Destroy(cutscene);
			}
		
		}
		
		
		
		
		
	}
}
