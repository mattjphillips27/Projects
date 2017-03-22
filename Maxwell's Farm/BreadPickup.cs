using UnityEngine;
using System.Collections;

public class BreadPickup : MonoBehaviour {

	// Use this for initialization
	void Start () {

		 

	}
	
	// Update is called once per frame
	void Update () {
	
	}
	IEnumerator OnCollisionEnter(Collision collision)
	{
		GameObject duckObj = GameObject.Find ("Alan"); 
		DuckAI duckScript = duckObj.GetComponent<DuckAI> ();

		if (collision.gameObject.tag == "Bread") 
		{
			yield return new WaitForSeconds(5);
			duckScript.health += 5;
			Destroy (collision.gameObject);
		}
		if (collision.gameObject.tag == "Cookie") 
		{
			yield return new WaitForSeconds(5);
			Destroy (collision.gameObject);
		}
	}
}
