using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Space : MonoBehaviour {

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
				Destroy(cutscene);
			}
		}
	}
}