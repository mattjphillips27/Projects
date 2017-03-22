using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class EnemySpawner : MonoBehaviour {

	public GameObject cowPrefab;
	public GameObject sheepPrefab;
	public GameObject goatPrefab;
	public GameObject chickenPrefab;
	
	private GameObject obj;
	
	public int enemyCount;
	
	public int cowCount;
	public int sheepCount;
	public int goatCount;
	public int chickenCount;
	bool feck;
	
	

	// Use this for initialization
	IEnumerator Start () 
	{
		cowCount = 0;
		sheepCount = 0;
		goatCount = 0;
		chickenCount = 0;
		
		if (gameObject.tag == "cowSpawner")
		{
			while (cowCount != enemyCount)
			{
				obj = Instantiate(cowPrefab, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				obj.transform.parent = transform;
				cowCount++;
				yield return new WaitForSeconds(Random.Range(5, 13));
			}
		}
		
		if (gameObject.tag == "sheepSpawner")
		{
			while (sheepCount != enemyCount)
			{
				obj = Instantiate(sheepPrefab, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				obj.transform.parent = transform;
				sheepCount++;
				yield return new WaitForSeconds(Random.Range(5, 13));
			}
		}
		
		if (gameObject.tag == "goatSpawner")
		{
			while (goatCount != enemyCount)
			{
				obj = Instantiate(goatPrefab, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				obj.transform.parent = transform;
				goatCount++;
				yield return new WaitForSeconds(Random.Range(5, 13));
			}
		}
		
		if (gameObject.tag == "chickenSpawner")
		{
			while (chickenCount != enemyCount)
			{
				obj = Instantiate(chickenPrefab, gameObject.transform.position, gameObject.transform.rotation) as GameObject;
				obj.transform.parent = transform;
				chickenCount++;
				yield return new WaitForSeconds(Random.Range(5, 13));
			}
		}
	}
}
