using UnityEngine;
using System.Collections;

public class Objective : MonoBehaviour 
{
	public GameObject currentObjective;
	public GameObject nextObjective;
	public GameObject cutscene;
	public int i = 1;

	// Use this for initialization
	void Start () 
	{
		nextObjective.active = false;
	}

	// Update is called once per frame
	void OnTriggerEnter(Collider other) 
	{
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		
		
		if (other.gameObject.tag == "Player" ) 
		{
			if (i == 1 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				i++;
				currentObjective.active = false;
				nextObjective.active = true;
				Destroy(gameObject);
			}
			else if (i == 2 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				Destroy(gameObject);
			}
			else if (i == 3 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				Destroy(gameObject);
			}
			else if (i == 4 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				cutscene.active = true;
				Destroy(gameObject);
			}
			else if (i == 5 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				Destroy(gameObject);
			}
			else if (i == 6 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				cutscene.active = true;
				Destroy(gameObject);
			}
			else if (i == 7 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				cutscene.active = true;
				Destroy(gameObject);
			}
			else if (i == 8 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				cutscene.active = true;
				Cursor.visible = true;
				Time.timeScale = 0;
				Destroy(gameObject);
			}
			else if (i == 9 && num.objectivenumber == i)
			{
				num.objectivenumber++;
				currentObjective.active = false;
				nextObjective.active = true;
				Destroy(gameObject);
			}
		}			
	}
}
