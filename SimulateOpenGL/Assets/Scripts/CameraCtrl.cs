using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraCtrl : MonoBehaviour
{

	public float speed = 0.1f;
	// Use this for initialization
	void Start()
	{

	}

	// Update is called once per frame
	void Update()
	{
		this.processView();
		this.processMove();
	}
	void processView(){
		
	}
	void processMove()
	{
		Vector3 currentPosition = this.transform.position;
		Vector3 delta = new Vector3(0.0f, 0.0f, 0.0f);
		if (Input.GetKey(KeyCode.A))
		{
			delta.x = -1 * speed;
		}
		if (Input.GetKey(KeyCode.D))
		{
			delta.x = speed;
		}
		if (Input.GetKey(KeyCode.W))
		{
			delta.z = speed;
		}
		if (Input.GetKey(KeyCode.S))
		{
			delta.z = -1 * speed;
		}
		this.transform.position = currentPosition + delta;

	}
}
