using UnityEngine;
using System.Collections;

public class StoryPickup : MonoBehaviour {

	
	// Use this for initialization
	void Start () 
	{
	
	}
	
	// Update is called once per frame
	void Update () 
	{
		
	}
	
	void OnCollisionEnter(Collision collision)
	{		
		GameObject manager = GameObject.Find ("_Manager"); 
		ObjectiveNumber num = manager.GetComponent<ObjectiveNumber> (); 
		
		print(collision.gameObject.tag);
		
		if (collision.gameObject.tag == "DrivingBoots") 
		{
			num.DrivingBoots = true;
			Destroy (collision.gameObject);
		}
		
	}
}
