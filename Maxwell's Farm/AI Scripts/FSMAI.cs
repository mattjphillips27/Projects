using UnityEngine;
using System.Collections;

public enum AIState
{
	IDLE,
	WANDERING,
	CHASING,
	ATTACK
}

public class FSMAI : MonoBehaviour 
{
	public int health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform enemy;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minAttackDistance = 5.0f;
	public float healAmount = 0.05f;
	private GameObject [] wanderPoints;
	private AIState prevState;
	public AIState state = AIState.IDLE;
	private bool bored;
	
	void Start () 
	{
		state = AIState.WANDERING;
		agent = GetComponent<NavMeshAgent> ();
		
		enemy = GameObject.FindGameObjectWithTag ("Alan").transform;
		
		
		getWanderPoints(gameObject.tag);
		
				
		if (moveTo == null)
		{
			moveTo = getRandomMoveTo ();
		}
	}
		
	public void MakeDecision()
	{
		prevState = state;

		switch(state)
		{
			case AIState.IDLE:
				state = Idle ();
				break;

			case AIState.WANDERING:
				state = Wander();
				break;

			case AIState.CHASING:
				state = Chase();
				break;

			case AIState.ATTACK:
				state = Attack();
				break;  
		}
	}

	public AIState Idle()
	{
		return AIState.WANDERING;
	}

	public AIState Wander()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);

			if (Vector3.Distance(moveTo.position, transform.position) < 5)
			{
				moveTo = getRandomMoveTo ();
			}
		}
		
		if (enemy != null)
		{
			if (Vector3.Distance(transform.position, enemy.position) <= minChaseDistance)
			{
				return AIState.CHASING;
			}
		}
		
		return AIState.WANDERING;
	}

	public AIState Chase()
	{
		if (enemy != null)
		{
			moveTo = enemy;

			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}

			if (Vector3.Distance(moveTo.position, transform.position) <= minAttackDistance)
			{
				return AIState.ATTACK;
			}

			if (Vector3.Distance(moveTo.position, transform.position) > minChaseDistance)
			{
				moveTo = getRandomMoveTo ();
				return AIState.WANDERING;
			}

			return AIState.CHASING;
		}
		else
		{
			moveTo = getRandomMoveTo ();
			return AIState.WANDERING;
		}
	}

	public AIState Attack()
	{
		if (enemy != null)
		{
			if (health < minAttackHealth)
			{
				moveTo = getRandomMoveTo();
				return AIState.WANDERING;
			}

			moveTo = enemy;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}

			if (Vector3.Distance(transform.position, enemy.position) > minAttackDistance)
			{
				return AIState.CHASING;
			}

			if (state != prevState)
			{
				attackTimer.StartTimer();
			}

			if (attackTimer.running == false)
			{
				enemy.GetComponent<DuckAI>().TakeDamage(Random.Range (0, attackDamage));
				attackTimer.StartTimer();
			}

			return AIState.ATTACK;
		}
		else
		{
			moveTo = getRandomMoveTo ();

			return AIState.WANDERING;
		}
	}
	
	public void getWanderPoints(string name)
	{
	
		if(name == "cow")
		{
			wanderPoints = GameObject.FindGameObjectsWithTag("cowPoints");
		}
		else if(name == "sheep")
		{
			wanderPoints = GameObject.FindGameObjectsWithTag("sheepPoints");
		}
		else if(name == "goat")
		{
			wanderPoints = GameObject.FindGameObjectsWithTag("goatPoints");
		}
		else if(name == "chicken")
		{
			wanderPoints = GameObject.FindGameObjectsWithTag("chickenPoints");
		}
	}
	
	public Transform getRandomMoveTo()
	{
		Transform point = wanderPoints[Random.Range(0, wanderPoints.Length)].transform;
		return point;		
	}

	public void TakeDamage(int damage)
	{
		health -= damage;

		if (health <= 0)
		{
			
			
			if (gameObject.tag == "cow")
			{	
				GameObject spawnerObj = GameObject.FindGameObjectWithTag("cowSpawner");
				EnemySpawner spawner = spawnerObj.GetComponent<EnemySpawner>();
				
				spawner.cowCount = spawner.cowCount - 1;
			}
			if (gameObject.tag == "sheep")
			{
				GameObject spawnerObj = GameObject.FindGameObjectWithTag("sheepSpawner");
				EnemySpawner spawner = spawnerObj.GetComponent<EnemySpawner>();

				spawner.sheepCount = spawner.sheepCount - 1;
			}
			if (gameObject.tag == "goat")
			{
				GameObject spawnerObj = GameObject.FindGameObjectWithTag("goatSpawner");
				EnemySpawner spawner = spawnerObj.GetComponent<EnemySpawner>();
				
				spawner.goatCount = spawner.goatCount - 1;
			}
			if (gameObject.tag == "chicken")
			{
				GameObject spawnerObj = GameObject.FindGameObjectWithTag("chickenSpawner");
				EnemySpawner spawner = spawnerObj.GetComponent<EnemySpawner>();
				
				spawner.chickenCount = spawner.chickenCount - 1;
			}
			
			
			Destroy (gameObject);
		}
	}

	void Update()
	{
		health += (int)(healAmount * Time.deltaTime);
		
		MakeDecision();
	}
}