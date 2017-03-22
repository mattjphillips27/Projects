using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class JamesBomb : MonoBehaviour {
	
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
				txt.text = "James: Wait what?! I don't want to die!";
				count++;
			}
			else if(count == 2)
			{
				txt.text = "Maxwell: James shut up! Just do this. Alan needs to survive";
				count++;
			}
			else if(count == 3)
			{
				txt.text = "Maxwell: He's more important right now";
				count++;
			}
			else if(count == 4)
			{	
				txt.text = "Maxwell: Who'd have thought I'd be leaving this dumb dumb to arm a bomb";
				count++;
			}
			else if(count == 5)
			{
				txt.text = "James: Dad! I can not believe this right now";
				count++;
			}
			else if(count == 6)
			{
				txt.text = "Maxwell: Alan! We're getting in the tractor, that should get us far away";
				count++;
			}
			else if(count == 7)
			{
				txt.text = "Maxwell: James, you were adopted. Goodbye!";
				count++;
			}
			else if(count == 8)
			{
				txt.text = "Alan: QUACK!";
				count++;
			}
			else if(count == 9)
			{
				
				
				Destroy(cutscene);
			}
		}
	}
}