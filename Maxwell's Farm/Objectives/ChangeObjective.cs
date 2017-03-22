using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ChangeObjective : MonoBehaviour 
{

	Text objective;
	

	// Use this for initialization
	void Start () 
	{
		objective = GetComponent<Text>();
		
		
	}
	
	// Update is called once per frame
	void Update () 
	{
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		
		if(num.objectivenumber == 1)
		{
			objective.text = "Make a pot of tea ";
		}
		else if(num.objectivenumber == 2)
		{
			objective.text = "Find Tractor & Machinery magazine ";
		}
		else if(num.objectivenumber == 3)
		{
			objective.text = "Check to see if your Wife Jane has it ";
		}
		else if(num.objectivenumber == 4)
		{
			objective.text = "Go inside the house ";
		}
		else if(num.objectivenumber == 5)
		{
			objective.text = "Get the Keys to the Tractor ";
		}
		else if(num.objectivenumber == 6)
		{
			objective.text = "Throw Bread to get keys ";
		}
		else if(num.objectivenumber == 7)
		{
			objective.text = "Check out the crop field ";
		}
		else if(num.objectivenumber == 8)
		{
			objective.text = "Check out the scarecrow ";
		}
		else if(num.objectivenumber == 9)
		{
			objective.text = "Go set the bomb ";
		}
		else if(num.objectivenumber == 10)
		{
			objective.text = "Get in the Tractor and drive away ";
		}
		
		
		
	}
}
