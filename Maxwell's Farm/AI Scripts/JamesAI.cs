using UnityEngine;
using System.Collections;

public enum JamesAIStates
{
	IDLE,
	WANDERING,
	CHASING,
	ATTACK
}

public class JamesAI : MonoBehaviour 
{
	public static JamesAI sJamesAI;
	public float health = 100;
	public int minAttackHealth = 20;
	public int attackDamage;
	public Transform moveTo;
	NavMeshAgent agent;
	public Transform enemy;
	public Timer attackTimer;
	public float minChaseDistance = 100.0f;
	public float minAttackDistance = 5.0f;
	public float healAmount = 0.05f;
	public Transform [] wanderPoints;
	private JamesAIStates prevState;
	public JamesAIStates state = JamesAIStates.IDLE;
	
	public GameObject Feck;
	private Transform player;
	
	void Start () 
	{
		state = JamesAIStates.WANDERING;
		agent = GetComponent<NavMeshAgent> ();
		
		GameObject obj = GameObject.FindGameObjectWithTag("AlanHealth");
		Alan healthBar = obj.transform.GetComponent<Alan>();
		
		health = healthBar.health;
		
		
	}
	
	public void MakeDecision()
	{
		prevState = state;
		
		switch(state)
		{
		case JamesAIStates.IDLE:
			state = Idle ();
			break;
			
		case JamesAIStates.WANDERING:
			state = Wander();
			break;
			
		case JamesAIStates.CHASING:
			state = Chase();
			break;
			
		case JamesAIStates.ATTACK:
			state = Attack();
			break;  
		}
	}
	
	public JamesAIStates Idle()
	{
		return JamesAIStates.WANDERING;
	}
	
	public JamesAIStates Wander()
	{
		//wander
		if (moveTo != null)
		{
			agent.SetDestination (moveTo.position);
			
		}
		
		if (enemy != null)
		{
			if (Vector3.Distance(transform.position, enemy.position) <= minChaseDistance)
			{
				
				return JamesAIStates.CHASING;
			}
		}
		
		return JamesAIStates.WANDERING;
	}
	
	public JamesAIStates Chase()
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
				return JamesAIStates.ATTACK;
			}
			
			return JamesAIStates.CHASING;
		}
		return JamesAIStates.WANDERING;
	}
	
	
	
	public JamesAIStates Attack()
	{
		if (enemy != null)
		{
			moveTo = enemy;
			
			if (moveTo != null)
			{
				agent.SetDestination (moveTo.position);
			}
			
			if (Vector3.Distance(transform.position, enemy.position) > minAttackDistance)
			{
				GetComponent<Animation>().Play("Walk");
				return JamesAIStates.CHASING;
			}
			
			if (state != prevState)
			{
				attackTimer.StartTimer();
			}
			
			if (attackTimer.running == false)
			{
				enemy.GetComponent<FSMAI>().TakeDamage(Random.Range (0, attackDamage));
				attackTimer.StartTimer();
			}
			
			return JamesAIStates.ATTACK;
		}
		return JamesAIStates.CHASING;
	}
	
	
	
	public void TakeDamage(int damage)
	{
		health -= damage;
	}
	
	void Update()
	{
		if (GameObject.FindWithTag ("Cookie")) 
		{
			JamesAnimation num = Feck.GetComponent<JamesAnimation>(); 
			
			num.PlayWalk();
			
			agent.stoppingDistance = 1;
			moveTo = GameObject.FindWithTag ("Cookie").transform;
		}
		else if (GameObject.FindWithTag ("Player")) {
			JamesAnimation num = Feck.GetComponent<JamesAnimation>(); 
			
			num.PlayWalk();
			agent.stoppingDistance = 5;
			moveTo = GameObject.FindWithTag ("Player").transform;
		}
		
		if (Vector3.Distance(transform.position, moveTo.position) < 5)
		{
			JamesAnimation num = Feck.GetComponent<JamesAnimation>(); 
			
			num.PlayIdle();
		}
		
		
		
		
		
		
		health += (int)(healAmount * Time.deltaTime);
		
		MakeDecision();
	}
}