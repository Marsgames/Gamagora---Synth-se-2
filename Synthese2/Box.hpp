//
//  Box.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Ray.hpp>
#include <Sphere.hpp>
#include <vector>
#include <Vector3.hpp>

enum EBoxType
{
    SphereType, BoundingBoxType, SuperBBoxType
};

struct BoxIntersection
{
    bool intersect;
    Sphere sphereContained;
    
    BoxIntersection() = delete ;
    BoxIntersection(const bool intersect, const Sphere& sphere):
    intersect{intersect},
    sphereContained{sphere}
    {};
};

class Box {
protected:
    Vector3 m_pMin, m_pMax;
//    EBoxType m_source; // Je ne sais plus à quoi ça sert
//    Sphere m_mySphere;
    
public:
    Box() = delete;
    
    Box(const Vector3& pMin, const Vector3& pMax):
    m_pMin{pMin},
    m_pMax{pMax}
    {};
    
    Box(const Box& box1, const Box& box2):
    m_pMin{box1.m_pMin < box2.m_pMin ? box1.m_pMin : box2.m_pMin},
    m_pMax{box1.m_pMax > box2.m_pMax ? box1.m_pMax : box2.m_pMax}
    {};
    
    Vector3 GetPMin() const;
    void SetPMin(const Vector3& pMin);
    Vector3 GetPMax() const;
    void SetPMax(const Vector3& pMax);
    
    bool operator<(const Box& other) const;
    
    static double IntersectBox(const Ray& ray, const Box& box);
};
