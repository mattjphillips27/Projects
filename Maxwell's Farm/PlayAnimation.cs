using UnityEngine;
using System.Collections;

public class PlayAnimation : MonoBehaviour {

		
	// Update is called once per frame
	void Update () {

		if (Input.GetButtonDown ("Fire1")) 
		{
			GetComponent<Animation>().Play ();	
		}
	}
}
