#pragma strict

var Health = 100;
var attack:AudioClip;

function Update ()
{
	if(Health <= 0)
	{
		Dead();
	}
}

function ApplyDamage (TheDamage : int)
{
	Health -= TheDamage;
}

function Dead()
{
	Destroy (gameObject);
}

function OnControllerColliderHit(hit : ControllerColliderHit) 
{	
	if(hit.gameObject.tag == "Bullet")
	{
	Debug.Log("tiosdaBKSJD");
		ApplyDamage(50);
		GetComponent.<AudioSource>().PlayOneShot(attack);
	}
}