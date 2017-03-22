using UnityEngine;
using System.Collections;

public class SwitchtoCar : MonoBehaviour {
		public GameObject prefab;
		public GameObject obj;
		public GameObject player;
		// Use this for initialization

	void OnTriggerEnter(Collider other) 
	{

		if (other.tag == "Pitchfork" || other.tag == "Player")
		{
			obj = (GameObject)Instantiate (prefab, gameObject.transform.position, gameObject.transform.rotation); 
			Destroy (gameObject);
			Destroy (player);
		}

	}
}

