var Bullet : Transform;

var Spawn : Transform;
var Spawn1 : Transform;
var Spawn2 : Transform;
	function Update ()
	{ 
		if(Input.GetButtonDown("Fire1"))
		{ 
			Shot(); 
		}
		
	}
	function Shot()
	{ 
		var pel = Instantiate(Bullet, Spawn.position, Spawn.rotation); pel.GetComponent.<Rigidbody>().AddForce(transform.forward * 1000);
		var pelo = Instantiate(Bullet, Spawn1.position, Spawn1.rotation); pelo.GetComponent.<Rigidbody>().AddForce(transform.forward * 1000);
		var pele = Instantiate(Bullet, Spawn2.position, Spawn2.rotation); pele.GetComponent.<Rigidbody>().AddForce(transform.forward * 1000);
	}
	