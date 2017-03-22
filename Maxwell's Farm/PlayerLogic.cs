using UnityEngine;
using System.Collections;

public class PlayerLogic : MonoBehaviour 
{
	public int Damage;
	public float Distance;
	public float MaxDistance;
		
	// Update is called once per frame
	void Update () 
	{
		if (Input.GetButtonDown("Fire1"))
		{
			RaycastHit hit;
			Vector3 fwd = transform.TransformDirection(Vector3.forward);
			if (Physics.Raycast (transform.position, fwd, out hit))
			{
				Distance = hit.distance;
				if (Distance < MaxDistance)
				{
				
					if (hit.transform.gameObject.tag == "cow" || hit.transform.gameObject.tag == "goat" || hit.transform.gameObject.tag == "chicken" || hit.transform.gameObject.tag == "sheep")
					{				
						FSMAI enemyScript = hit.transform.GetComponent<FSMAI>();
						enemyScript.TakeDamage(Damage);
					}
					else if (hit.transform.gameObject.tag == "babyCow")
					{
						babyCowAI babycowScript = hit.transform.GetComponent<babyCowAI>();
						babycowScript.TakeDamage(Damage);
					}
					else if (hit.transform.gameObject.tag == "Bull")
					{
						BullAI BullScript = hit.transform.GetComponent<BullAI>();
						BullScript.TakeDamage(Damage);
					}
					else if (hit.transform.gameObject.tag == "Ram")
					{
						RamAI RamScript = hit.transform.GetComponent<RamAI>();
						RamScript.TakeDamage(Damage);
					}
					else if (hit.transform.gameObject.tag == "Cockrill")
					{
						RamAI RamScript = hit.transform.GetComponent<RamAI>();
						RamScript.TakeDamage(Damage);
					}
				}
			}
		}
	}
}
