using UnityEngine;
using System.Collections;

public class PlayerAnimation : MonoBehaviour {

	public GameObject Shotgun;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () 
	{
	
		if(Shotgun.active == false)
		{
	
			if (Input.GetButtonDown ("Fire1")) 
			{
				GetComponent<Animation>().Play("Lumbering");	
			}
		}
		
		if (Input.GetButtonDown ("Vertical")) 
		{
			GetComponent<Animation>().Play("Walk");	
		}
		else if (Input.GetButtonUp ("Vertical")) 
		{
			GetComponent<Animation>().Play("Idle");	
		}
	}
}
