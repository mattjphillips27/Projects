using UnityEngine;
using System.Collections;

public enum BreedingAIState
{
	IDLE,HIDING,CHASING,HORNY
}

public enum BreedingAnimal
{
	Cow,Chicken,Sheep,Goat
}

public class BreedingAI : MonoBehaviour 
{
	NavMeshAgent agent;
	public float minChaseDistance = 100.0f;
	public float minMountDistance = 5.0f;
	public Transform [] wanderPoints;
	private BreedingAIState prevState;
	public BreedingAIState state = BreedingAIState.IDLE;
	
	public BreedingAnimal animal;
	
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Timer attackTimer;
	public float healAmount = 0.05f;
	
	public Transform moveTo;
	public Transform partner;
	
	private GameObject babypartner;
	public GameObject babyCow;
	public GameObject babyChicken;
	public GameObject babySheep;
	public GameObject babyGoat;
	
	
	
	public GameObject explosion;
	public GameObject obj;
	private bool fuck = true;
	public Transform po;
	string animalName;


	// Use this for initialization
	void Start () 
	{
		state = BreedingAIState.HIDING;
		agent = GetComponent<NavMeshAgent> ();
		partner = FindClosestPartner().transform;
		
		if (animal == BreedingAnimal.Cow)
		{
		 	animalName = "cow";
			babypartner = babyCow;
		}
		else if (animal == BreedingAnimal.Chicken)
		{
			animalName = "chicken";
			babypartner = babyChicken;
		}
		else if (animal == BreedingAnimal.Sheep)
		{
			animalName = "sheep";
			babypartner = babySheep;
		}
		else if (animal == BreedingAnimal.Goat)
		{
			animalName = "goat";
			babypartner = babyGoat;
		}
		
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
	
	
	GameObject FindClosestPartner() 
	{
		GameObject[] gos;
		gos = GameObject.FindGameObjectsWithTag(animalName);
		GameObject closest = null;
		float distance = Mathf.Infinity;
		Vector3 position = transform.position;
		foreach (GameObject go in gos) 
		{
			Vector3 diff = go.transform.position - position;
			float curDistance = diff.sqrMagnitude;
			if (curDistance < distance) 
			{
				closest = go;
				distance = curDistance;
			}
		}
		
		print(closest.name);
		return closest;
	}
	
	public void MakeDecision()
	{
		prevState = state;
		
		switch(state)
		{
		case BreedingAIState.IDLE:
			state = Idle ();
			break;
			
		case BreedingAIState.HIDING:
			state = Hide();
			break;
			
		case BreedingAIState.CHASING:
			state = Chase();
			break;
			
		case BreedingAIState.HORNY:
			state = Horny();
			break;
		}
	}
	
	public BreedingAIState Idle()
	{
		return BreedingAIState.HIDING;
	}
	
	public BreedingAIState Hide()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);
			
			if (Vector3.Distance(moveTo.position, transform.position) < 5)
			{
				moveTo = getRandomMoveTo ();
				StartCoroutine(Wait(1.0f));
				fuck = true;
			}
		}
		
		if (partner != null)
		{
			if (Vector3.Distance(transform.position, partner.position) <= minChaseDistance)
			{
				return BreedingAIState.CHASING;
			}
		}
		
		return BreedingAIState.HIDING;
	}
	
	IEnumerator Wait(float waitTime) 
	{
		yield return new WaitForSeconds(waitTime);
		partner = FindClosestPartner().transform;
	}
	
	public BreedingAIState Chase()
	{
		if (partner != null)
		{
			moveTo = partner;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) <= minMountDistance)
			{
				return BreedingAIState.HORNY;
			}
			
			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return BreedingAIState.HIDING;
			}
			
			return BreedingAIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return BreedingAIState.HIDING;
		}
	}
	
	public BreedingAIState Horny()
	{
		Debug.Log("I am Fucking");
		
		
		if(fuck)
		{
			obj = (GameObject)Instantiate(babypartner, gameObject.transform.position, gameObject.transform.rotation);
			obj.transform.parent = po;
			obj = (GameObject)Instantiate(explosion, gameObject.transform.position, gameObject.transform.rotation);
			fuck = false;
		}
		
		partner = null;
		moveTo = getRandomMoveTo ();
		return BreedingAIState.HIDING;
	}
	
	public Transform getRandomMoveTo()
	{
		Transform point = wanderPoints[Random.Range(0, wanderPoints.Length-1)];
		//Debug.Log ("Moving to: " + point.position);
		return point;
	}
	
	public void TakeDamage(int damage)
	{
		health -= damage;
		
		if (health <= 0)
		{
			Destroy (gameObject);
		}
	}
	
	void Update()
	{
		//health += (int)(healAmount * Time.deltaTime);
		MakeDecision();
	}
}
