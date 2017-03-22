using UnityEngine;
using System.Collections;

public class playSound : MonoBehaviour {
		
		public AudioClip awoogah;
		public int soundWait = 10;
		bool keepPlaying=true;
		
		void Start () {
			StartCoroutine(SoundOut());
		}
		
		IEnumerator SoundOut()
		{
			while (keepPlaying){
				GetComponent<AudioSource>().PlayOneShot(awoogah);  
				
			yield return new WaitForSeconds(Random.Range(15, 30));
			}
		}
	}