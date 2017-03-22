using UnityEngine;
using System.Collections;

public class Timer : MonoBehaviour
{
	public float time;
	public bool running;
	
	public void StartTimer()
	{
		running = true;
		StartCoroutine (countdown());
	}

	IEnumerator countdown()
	{
		while (true)
		{
			for (float curTime = time; curTime > 0; curTime -= Time.deltaTime)
				yield return null;
			
			break;
		}
		
		running = false;
	}
}
