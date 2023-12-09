using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;

public class LevelParser : EditorWindow
{
    [MenuItem("File/Open .level file")]
    private static void SelectFile()
    {
        string filePath = EditorUtility.OpenFilePanel("Open .level", "", "level");

        if (filePath.Length > 0)
        {
            OpenLevelFile(filePath);
        }
    }

    private static void OpenLevelFile(string filePath)
    {
        string[] lines;
        lines = File.ReadAllLines(filePath);

        string name = "";
        int type = 0;
        Vector3 pos = Vector3.zero;
        Vector3 rot = Vector3.zero;
        Vector3 scale = Vector3.one;
        bool isActive = false;

        bool hasPhysics = false;
        bool isStatic = false;
        bool isGravityActive = false;
        float mass = 0.0f;

        for (int i = 0; i < lines.Length; i++)
        {
            switch (i % 11)
            {
                case 0:
                {
                    name = lines[i];
                } break;

                case 1:
                {
                    string[] split = lines[i].Split(' ');
                    type = int.Parse(split[1]);
                } break;

                case 2:
                {
                    string[] split = lines[i].Split(' ');
                    pos.x = float.Parse(split[1]);
                    pos.y = float.Parse(split[2]);
                    pos.z = float.Parse(split[3]);
                } break;

                case 3:
                {
                    string[] split = lines[i].Split(' ');
                    rot.x = float.Parse(split[1]);
                    rot.y = float.Parse(split[2]);
                    rot.z = float.Parse(split[3]);
                        
                    rot.x *= Mathf.Rad2Deg;
                    rot.y *= Mathf.Rad2Deg;
                    rot.z *= Mathf.Rad2Deg;
                } break;

                case 4:
                {
                    string[] temp = lines[i].Split(' ');
                    scale.x = float.Parse(temp[1]);
                    scale.y = float.Parse(temp[2]);
                    scale.z = float.Parse(temp[3]);
                } break;

                case 5:
                {
                    string[] temp = lines[i].Split(' ');
                    isActive = int.Parse(temp[1]) != 0;
                    } break;

                case 6:
                {
                    string[] temp = lines[i].Split(' ');

                    hasPhysics = int.Parse(temp[1]) != 0;
                } break;

                case 8:
                {
                    string[] split = lines[i].Split(' ');

                    isStatic = int.Parse(split[1]) != 0;
                } break;

                case 9:
                {
                    string[] split = lines[i].Split(' ');

                    isGravityActive = int.Parse(split[1]) != 0;
                } break;

                case 10:
                {
                    string[] split = lines[i].Split(' ');
                    mass = float.Parse(split[1]);

                    if (type == 1)
                    {
                        GameObject newCube = GameObject.CreatePrimitive(PrimitiveType.Cube);
                        newCube.name = name;
                        newCube.SetActive(isActive);
                        newCube.transform.SetPositionAndRotation(pos, Quaternion.Euler(rot));
                        newCube.transform.localScale = scale;

                        if (hasPhysics)
                        {
                            newCube.AddComponent<Rigidbody>();

                            Rigidbody component = newCube.GetComponent<Rigidbody>();

                            component.mass = mass;
                            component.isKinematic = isStatic;
                            component.useGravity = isGravityActive;
                        }
                    }

                    else if (type == 2)
                    {
                        GameObject newPlane = GameObject.CreatePrimitive(PrimitiveType.Plane);

                        newPlane.name = name;
                        newPlane.SetActive(isActive);
                        newPlane.transform.SetPositionAndRotation(pos, Quaternion.Euler(rot));

                        newPlane.transform.localScale = scale;

                        if (hasPhysics)
                        {
                            newPlane.AddComponent<Rigidbody>();

                            Rigidbody component = newPlane.GetComponent<Rigidbody>();

                            component.mass = mass;
                            component.isKinematic = isStatic;
                            component.useGravity = isGravityActive;
                        }
                    }
                } break;

                default: break;
            }
        }
    }
}