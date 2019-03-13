using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseBehaviour : MonoBehaviour
{
	public Material awesomeFace;
	private float awesomeAlpha;
	private float colorAlpha;
	/// <summary>
	/// Awake is called when the script instance is being loaded.
	/// </summary>
	void Awake()
	{
		awesomeAlpha = 0.5f;
		colorAlpha = 0.2f;
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
		myBox.colors = new Color[]{
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
			new Color(1.0f, 0.0f, 0.0f),
			new Color(0.0f, 1.0f, 0.0f),
			new Color(0.0f, 0.0f, 1.0f),
			new Color(1.0f, 1.0f, 1.0f),
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

		Vector3[] cubePositions = new Vector3[]{
			new Vector3(0.0f, 0.0f, 0.0f),
			new Vector3(2.0f, 5.0f, -15.0f),
			new Vector3(-1.5f, -2.2f, -2.5f),
			new Vector3(-3.8f, -2.0f, -12.3f),
			new Vector3(2.4f, -0.4f, -3.5f),
			new Vector3(-1.7f, 3.0f, -7.5f),
			new Vector3(1.3f, -2.0f, -2.5f),
			new Vector3(1.5f, 2.0f, -2.5f),
			new Vector3(1.5f, 0.2f, -1.5f),
			new Vector3(-1.3f, 1.0f, -1.5f),
		};
		for (int i = 0; i < cubePositions.Length; i++)
		{
			GameObject tmpBox = new GameObject("My Box " + i);
			Transform tmpTrans = tmpBox.GetComponent<Transform>();
			tmpTrans.position = cubePositions[i];
			MeshFilter tmpMesh = tmpBox.AddComponent<MeshFilter>();
			tmpMesh.sharedMesh = myBox;
			MeshRenderer tmpRenderer = tmpBox.AddComponent<MeshRenderer>();
			tmpRenderer.sharedMaterial = awesomeFace;
		}
	}
	// Use this for initialization
	void Start()
	{

	}
	// Update is called once per frame
	void Update()
	{
		this.awesomeFace.SetFloat("_AwesomeAlpha", this.awesomeAlpha);
		this.awesomeFace.SetFloat("_ColorAlpha", this.colorAlpha);
	}
	/// <summary>
	/// OnGUI is called for rendering and handling GUI events.
	/// This function can be called multiple times per frame (one call per event).
	/// </summary>
	void OnGUI()
	{
		Event m_Event = Event.current;
		if (m_Event.type == EventType.KeyDown)
		{
			switch (m_Event.keyCode)
			{
				case KeyCode.UpArrow:
					this.awesomeAlpha += 0.1f;
					if (this.awesomeAlpha > 1.0f)
					{
						this.awesomeAlpha = 1.0f;
					}
					break;
				case KeyCode.DownArrow:
					this.awesomeAlpha -= 0.1f;
					if (this.awesomeAlpha < 0.0f)
					{
						this.awesomeAlpha = 0.0f;
					}
					break;
				case KeyCode.RightArrow:
					this.colorAlpha += 0.1f;
					if (this.colorAlpha > 1.0f)
					{
						this.colorAlpha = 1.0f;
					}
					break;
				case KeyCode.LeftArrow:
					this.colorAlpha -= 0.1f;
					if (this.colorAlpha < 0.0f)
					{
						this.colorAlpha = 0.0f;
					}
					break;
				default:
					break;
			}
		}
	}
}
