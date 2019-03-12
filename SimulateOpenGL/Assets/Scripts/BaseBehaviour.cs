using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseBehaviour : MonoBehaviour
{
	/// <summary>
	/// Awake is called when the script instance is being loaded.
	/// </summary>
	void Awake()
	{
		Mesh myBox = new Mesh();
		myBox.name = "MyBox";
		myBox.vertices = new Vector3[]{
			new Vector3(-0.5f, -0.5f,  0.5f),
			new Vector3( 0.5f, -0.5f,  0.5f),
			new Vector3( 0.5f,  0.5f,  0.5f),
			new Vector3(-0.5f,  0.5f,  0.5f),
			new Vector3(-0.5f,  0.5f, -0.5f),
			new Vector3( 0.5f,  0.5f, -0.5f),
			new Vector3( 0.5f, -0.5f, -0.5f),
			new Vector3(-0.5f, -0.5f, -0.5f),
			new Vector3(-0.5f, -0.5f,  0.5f),
			new Vector3(-0.5f,  0.5f,  0.5f),
			new Vector3(-0.5f,  0.5f, -0.5f),
			new Vector3(-0.5f, -0.5f, -0.5f),
			new Vector3( 0.5f, -0.5f, -0.5f),
			new Vector3( 0.5f,  0.5f, -0.5f),
			new Vector3( 0.5f,  0.5f,  0.5f),
			new Vector3( 0.5f, -0.5f,  0.5f),
			new Vector3( 0.5f,  0.5f,  0.5f),
			new Vector3( 0.5f,  0.5f, -0.5f),
			new Vector3(-0.5f,  0.5f, -0.5f),
			new Vector3(-0.5f,  0.5f,  0.5f),
			new Vector3(-0.5f, -0.5f,  0.5f),
			new Vector3(-0.5f, -0.5f, -0.5f),
			new Vector3( 0.5f, -0.5f, -0.5f),
			new Vector3( 0.5f, -0.5f,  0.5f),
		};
		myBox.uv = new Vector2[]{
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
		};
		myBox.triangles = new int[]{
			 0,  1,  2,  0,  2,  3, // front
			 4,  5,  6,  4,  6,  7, // back
			 8,  9, 10,  8, 10, 11, // left
			12, 13, 14, 12, 14, 15, // right
			16, 17, 18, 16, 18, 19, // up
			20, 21, 22, 20, 22, 23, // down
		};
		MeshFilter meshFilter = this.gameObject.GetComponent<MeshFilter>();
		meshFilter.sharedMesh = myBox;
		// Mesh Box = meshFilter.sharedMesh;
		// Vector3[] vects = Box.vertices;
		// string vertexStr = "";
		// for (int i = 0; i < vects.Length; i++)
		// {
		// 	// Debug.Log(vects[i]);
		// 	vertexStr += vects[i] + " ";
		// }
		// Vector2[] uv = Box.uv;
		// string uvStr = "";
		// for (int i = 0; i < uv.Length; i++)
		// {
		// 	// Debug.Log(uv[i]);
		// 	uvStr += uv[i] + " ";
		// }
		// int[] index = Box.triangles;
		// string indexStr = "";
		// for (int i = 0; i < index.Length; i++)
		// {
		// 	// Debug.Log(index[i]);
		// 	indexStr += index[i].ToString() + " ";
		// }
		// Debug.Log(vertexStr);
		// Debug.Log(uvStr);
		// Debug.Log(indexStr);
	}
	// Use this for initialization
	void Start()
	{

	}

	// Update is called once per frame
	void Update()
	{

	}
}
