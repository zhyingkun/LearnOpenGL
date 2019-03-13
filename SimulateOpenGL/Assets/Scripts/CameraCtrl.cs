using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraCtrl : MonoBehaviour
{

	public float MovementSpeed = 0.1f;
	public float MouseSensitivity = 0.1f;
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
	void processView()
	{
		float h = MouseSensitivity * Input.GetAxis("Mouse X");
		float v = -MouseSensitivity * Input.GetAxis("Mouse Y");
		this.transform.Rotate(v, h, 0);
	}
	void processMove()
	{
		Vector3 currentPosition = this.transform.position;
		Vector3 delta = new Vector3(0.0f, 0.0f, 0.0f);
		float velocity = MovementSpeed * Time.deltaTime;
		if (Input.GetKey(KeyCode.A))
		{
			delta -= velocity * this.transform.right;
		}
		if (Input.GetKey(KeyCode.D))
		{
			delta += velocity * this.transform.right;
		}
		if (Input.GetKey(KeyCode.W))
		{
			delta += velocity * this.transform.forward;
		}
		if (Input.GetKey(KeyCode.S))
		{
			delta -= velocity * this.transform.forward;
		}
		this.transform.position = currentPosition + delta;

	}
}
