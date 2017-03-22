using UnityEngine;
using System.Collections;
public class KeysPickup : MonoBehaviour {

	public GameObject box;

	void OnTriggerEnter(Collider other)
	{
		if (other.gameObject.tag == "Alan") 
		{
			Destroy (box);
			Destroy (gameObject);
		}

	}

}
