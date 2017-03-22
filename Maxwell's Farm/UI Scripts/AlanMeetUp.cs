using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class AlanMeetUp : MonoBehaviour {

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
				txt.text = "Maxwell: Hey Alan";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Alan: QUACK";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Maxwell: She's dead Alan, I...";
				count++;
			}
			else if(count == 4)
			{
				txt.text = "Alan: QUACK";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "Maxwell: We need to get out of here.";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "Maxwell: Where did I leave my car keys?";
				count++;
			}
			else if(count == 7)
			{
				
				Destroy(cutscene);
			}
		}
	}
}