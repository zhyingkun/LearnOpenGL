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
			new Vector3(0.5f, 0.5f, 0.5f),
			new Vector3(0.5f, -0.5f, 0.5f),
			new Vector3(-0.5f, -0.5f, 0.5f),
			new Vector3(-0.5f, 0.5f, 0.5f),
			new Vector3(0.5f, 0.5f, -0.5f),
			new Vector3(0.5f, -0.5f, -0.5f),
			new Vector3(-0.5f, -0.5f, -0.5f),
			new Vector3(-0.5f, 0.5f, -0.5f),
			new Vector3(0.5f, 0.5f, -0.5f),
			new Vector3(-0.5f, 0.5f, -0.5f),
			new Vector3(-0.5f, -0.5f, -0.5f),
			new Vector3(0.5f, -0.5f, -0.5f)
		};
		myBox.uv = new Vector2[]{
			new Vector2(1.0f, 1.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(1.0f, 1.0f),
			new Vector2(1.0f, 0.0f),
			new Vector2(0.0f, 0.0f),
			new Vector2(0.0f, 1.0f),
			new Vector2(1.0f, 1.0f)
		};
		// myBox.triangles = new int[]{
		// 	// note that we start from 0!
		// 	0, 1, 3, // first triangle
		// 	1, 2, 3, // second triangle
		// 	0, 4, 5,
		// 	0, 5, 1,
		// 	2, 6, 3,
		// 	6, 7, 3,
		// 	4, 5, 6,
		// 	4, 6, 7,
		// 	0, 3, 9,
		// 	0, 9, 8,
		// 	1, 2, 11,
		// 	2, 11, 10
		// 	// 0, 1, 2
		// };
		myBox.triangles = new int[]{
			// note that we start from 0!
			0, 1, 3, // first triangle
			1, 2, 3, // second triangle
			0, 4, 5,
			0, 5, 1,
			2, 6, 3,
			6, 7, 3,
			5, 4, 6,
			6, 4, 7,
			0, 3, 9, // 8==>4  9==>7 10==>6 11==>5
			0, 9, 8,
			2, 1, 11,
			2, 11, 10
			// 0, 1, 2
		};
		MeshFilter meshFilter = this.gameObject.GetComponent<MeshFilter>();
		meshFilter.sharedMesh = myBox;
		// Mesh Box = meshFilter.sharedMesh;
		// Vector3[] vects = Box.vertices;
		// for (int i = 0; i < vects.Length; i++)
		// {
		// 	Debug.Log(vects[i]);
		// }
		// Vector2[] uv = Box.uv;
		// for (int i = 0; i < uv.Length; i++)
		// {
		// 	Debug.Log(uv[i]);
		// }
		// int[] index = Box.triangles;
		// for (int i = 0; i < index.Length; i++)
		// {
		// 	Debug.Log(index[i]);
		// }
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
